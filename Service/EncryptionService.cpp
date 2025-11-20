#include "../EncryptionService.h"

#include "../Data/UI/ErrorText.h"
#include "../Data/UI/UiText.h"

EncryptionService::EncryptionService(IEncrypt &encryptor, IFileHandler &fileHandler, ILogger &logger)
    : _encryptor(encryptor), _fileHandler(fileHandler), _logger(logger)
{}

bool EncryptionService::EncryptFile(userInput &input) {

    _logger.log(LogLevel::INFO, std::string(EncryptionOutput::logEncryptStart));


    auto plaintext = _fileHandler.readFromFile(input.filename);
    std::vector<unsigned char> iv, ciphertext, tag;

    const auto [salt, key] = hashAndSalt(input.password);
    if (salt.empty() || key.empty()) {
        _logger.log(LogLevel::ERROR, "Failed to hash password");
        return false;
    }


    const bool ok = _encryptor.encrypt(plaintext, key, ciphertext, iv, tag);


    if (!ok) {
        _logger.log(LogLevel::ERROR, std::string(EncryptDecryptError::logEncryptionFailure));
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

    _fileHandler.writeToFile(input.filename, out);
    return true;
}
