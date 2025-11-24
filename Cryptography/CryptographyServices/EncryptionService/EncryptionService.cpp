#include "EncryptionService.h"


#include "../../../Data/UI/ErrorText.h"
#include "../../../Data/UI/UiText.h"
#include "../../../Render/RenderCmd.h"

EncryptionService::EncryptionService(IEncrypt &encryptor,
                                     DigesterService &digesterService,
                                     IFileHandler &fileHandler,
                                     ILogger &logger)
    : _encryptor(encryptor), _fileHandler(fileHandler), _logger(logger), _digesterService(digesterService) {
}

bool EncryptionService::EncryptFile(const std::string &filename, const std::string &password) {
    _logger.log(LogLevel::INFO, std::string(EncryptionOutput::logEncryptStart));

    const auto plaintext = _fileHandler.readFromFile(filename);
    std::vector<unsigned char> iv, ciphertext, tag;

    const auto result = _digesterService.Digest(password);

    const auto &key = result.key;
    const auto &salt = result.salt;

    if (salt.empty() || key.empty()) {
        _logger.log(LogLevel::ERROR, "Failed to hash password");
        return false;
    }


    const auto ok = _encryptor.encrypt(plaintext, key, iv, ciphertext, tag);


    if (!ok.result) {
        RenderCmd::WriteError(EncryptDecryptError::encryptionFailure);
        _logger.log(LogLevel::ERROR, std::string(EncryptDecryptError::logEncryptionFailure));
        _logger.log(LogLevel::ERROR, ok.errorMessage);
        return false;
    }

    std::vector<unsigned char> out;
    out.push_back(salt.size());
    out.push_back(iv.size());
    out.push_back(tag.size());

    out.insert(out.end(), salt.begin(), salt.end());
    out.insert(out.end(), iv.begin(), iv.end());
    out.insert(out.end(), ciphertext.begin(), ciphertext.end());
    out.insert(out.end(), tag.begin(), tag.end());

    _fileHandler.writeToFile(filename, out);
    RenderCmd::WriteOut(EncryptionOutput::encryptSuccess);
    return true;
}