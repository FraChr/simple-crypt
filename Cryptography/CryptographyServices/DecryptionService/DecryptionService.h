#pragma once
#include "../HashingService/DigesterService.h"
#include "../../AesGcmEncryptor/IDecrypt.h"
#include "../../../Interfaces/IFileHandler.h"
#include "../../../Interfaces/ILogger.h"
#include "../../../POD/UserInput.h"

class DecryptionService {
public:
    DecryptionService(IDecrypt &decryptor, DigesterService &digesterService, IFileHandler &file, ILogger &logger);

    bool DecryptFile(const std::string &filename, const std::string &password);

private:
    IDecrypt &_decryptor;
    IFileHandler &_fileHandler;
    ILogger &_logger;
    DigesterService &_digesterService;
};
