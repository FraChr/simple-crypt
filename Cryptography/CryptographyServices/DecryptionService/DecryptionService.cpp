#include "DecryptionService.h"
#include "../../../Data/UI/ErrorText.h"
#include "../../../Data/UI/UiText.h"
#include "../../../Render/RenderCmd.h"


DecryptionService::DecryptionService(IDecrypt &decryptor, DigesterService &digesterService, IFileHandler &file,
                                     ILogger &logger) : _decryptor(decryptor), _fileHandler(file), _logger(logger),
                                                        _digesterService(digesterService) {
}

bool DecryptionService::DecryptFile(const std::string &filename, const std::string &password) {
    _logger.log(LogLevel::INFO, std::string(DecryptionOutput::logDecryptStart));

    auto fileContents = _fileHandler.readFromFile(filename);

    const int salt_len = fileContents[0];
    const int iv_len = fileContents[1];
    const int tag_len = fileContents[2];

    int offset = 3;

    if (fileContents.size() < salt_len + iv_len + tag_len) {
        _logger.log(LogLevel::ERROR, EncryptDecryptError::notValidOrCorrupt.data());
        return false;
    }

    std::vector salt(fileContents.begin() + offset, fileContents.begin() + offset + salt_len);
    offset += salt_len;

    std::vector iv(fileContents.begin() + offset, fileContents.begin() + offset + iv_len);
    offset += iv_len;


    std::vector tag(fileContents.end() - tag_len, fileContents.end());

    int ciphertext_len = fileContents.size() - offset - tag_len;
    const std::vector<unsigned char> ciphertext(
        fileContents.begin() + offset,
        fileContents.begin() + offset + ciphertext_len
    );

    std::vector<unsigned char> key(32);
    const auto verifyKey = _digesterService.VerifyDigest(password, salt, key);

    if (!verifyKey) {
        _logger.log(LogLevel::ERROR, "Failed to verify key");
        return false;
    }

    std::vector<unsigned char> plaintext(ciphertext_len);

    const auto ok = _decryptor.decrypt(ciphertext, key, iv, tag, plaintext);

    if (!ok) {
        RenderCmd::WriteError(EncryptDecryptError::decryptionFailure);
        _logger.log(LogLevel::ERROR, EncryptDecryptError::logDecryptionFailure.data());

        return false;
    }

    _fileHandler.writeToFile(filename, plaintext);

    RenderCmd::WriteOut(DecryptionOutput::decryptSuccess);
    _logger.log(LogLevel::INFO, std::string(DecryptionOutput::logDecryptDone));
    return true;
}
