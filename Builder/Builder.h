#pragma once

#include "../SimpleCrypt.h"
#include "../Cryptography/AesGcmEncryptor/AesGcmCipher.h"
#include "../ArgumentHandler/ArgsHandler.h"
#include "../commands/Commands.h"
#include "../FileHandling/FileHandler.h"
#include "../Cryptography/KdfDigester/KdfDigester.h"
#include "../Logger/Logger.h"
#include "../Cryptography/CryptographyServices/DecryptionService/DecryptionService.h"
#include "../Cryptography/CryptographyServices/HashingService/DigesterService.h"
#include "../Cryptography/CryptographyServices/EncryptionService/EncryptionService.h"

class Builder {
public:
    Builder(int argc, char *argv[]);

    SimpleCrypt Build();

private:
    FileHandler _fileHandler;
    Logger _logger;

    KdfDigester _kdfDigester;
    AesGcmCipher _aesGcmCipher;
    DigesterService _digesterService;
    EncryptionService _encryptionService;
    DecryptionService _decryptionService;

    Commands _cmd;
    ArgsHandler _argsHandler;
    int _argc;
    char **_argv;
};
