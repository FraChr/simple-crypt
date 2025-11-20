#pragma once
#include "../AesGcmEncryptor/IEncrypt.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"

class EncryptionService {
public:
    EncryptionService(IEncrypt &encryptor, IFileHandler &fileHandler, ILogger &logger);
    bool EncryptFile(userInput &input);

private:
    IEncrypt &_encryptor;
    IFileHandler &_fileHandler;
    ILogger &_logger;
};
