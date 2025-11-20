#pragma once
#include "DigesterService.h"
#include "../AesGcmEncryptor/IDecrypt.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"
#include "../POD/File.h"

class DecryptService {
    public:
        DecryptService(IDecrypt &decryptor, DigesterService &digesterService, IFileHandler &file, ILogger &logger);
        bool DecryptFile(userInput &input);

private:
    IDecrypt &_decryptor;
    IFileHandler &_fileHandler;
    ILogger &_logger;
    DigesterService &_digesterService;
};
