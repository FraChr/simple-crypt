#pragma once
#include <map>
#include <string>
#include <openssl/evp.h>
#include <openssl/types.h>

#include "CommandTypes.h"
#include "../Cryptography/AesGcmEncryptor/IDecrypt.h"
#include "../Cryptography/AesGcmEncryptor/IEncrypt.h"
#include "../Interfaces/ICommands.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"
#include "../Cryptography/CryptographyServices/DecryptionService/DecryptionService.h"
#include "../Cryptography/CryptographyServices/EncryptionService/EncryptionService.h"

struct keyAndSalt;

class Commands final : public ICommands {
public:
    std::map<CommandType, CommandFunc> commands;

    Commands(
        IFileHandler &fileHandlerInstance,
        ILogger &loggerInstance,
        EncryptionService &encryptionService,
        DecryptionService &decryptionService);

    void executeCommand(const CommandType type, userInput &file) override {
        if (commands.contains(type)) commands[type](file);
    }

private:
    void compress(const userInput &file);

    std::unordered_map<unsigned char, int> CountCharOccurrences(const std::string &filename);

    void encrypt(const userInput &userInput);

    void decrypt(const userInput &userInput);


    void HandleError() const;

    void HandleError(EVP_CIPHER_CTX *ctx) const;

    void HandleError(EVP_MD_CTX *mctx) const;

    void HandleError(EVP_KDF *kdf, EVP_KDF_CTX *kctx, OSSL_LIB_CTX *lib_ctx) const;

    IFileHandler &_fileHandler;
    ILogger &_logger;
    EncryptionService &_encryptionService;
    DecryptionService &_decryptionService;
};
