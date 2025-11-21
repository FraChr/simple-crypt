#pragma once
#include "../HashingService/DigesterService.h"
#include "../../AesGcmEncryptor/IEncrypt.h"
#include "../../../Interfaces/IFileHandler.h"
#include "../../../Interfaces/ILogger.h"

class EncryptionService {
public:
    EncryptionService(IEncrypt &encryptor, DigesterService &digesterService, IFileHandler &fileHandler,
                      ILogger &logger);

    bool EncryptFile(const std::string &filename, const std::string &password);

private:
    IEncrypt &_encryptor;
    IFileHandler &_fileHandler;
    ILogger &_logger;
    DigesterService &_digesterService;
};