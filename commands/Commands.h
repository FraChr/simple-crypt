#pragma once
#include <map>
#include <string>
#include <openssl/evp.h>
#include <openssl/types.h>

#include "CommandTypes.h"
#include "../Interfaces/ICommands.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"

struct keyAndSalt;

class Commands : public ICommands {
public:
    std::map<CommandType, CommandFunc> commands;

    Commands(IFileHandler &fileHandlerInstance, ILogger &loggerInstance);

    void executeCommand(const CommandType type, userInput &file) override {
        if (commands.contains(type)) commands[type](file);
    }

    bool kdf_passwd(std::string password, std::vector<unsigned char> salt, unsigned int iteration, std::vector<unsigned char> &key);
private:
    std::vector<unsigned char> hash(const std::string &password);

    void compress(const userInput &file);

    std::unordered_map<unsigned char, int> CountCharOccurrences(const std::string &filename);

    bool hashPassword(const unsigned char *data, size_t data_len, unsigned char *out_digest, unsigned int *out_len) const;

    void encrypt(const userInput &userInput);

    void decrypt(const userInput &userInput);

    bool gcm_encrypt(const unsigned char *plaintext,
                     int plaintext_len,
                     const unsigned char *key,
                     unsigned char *iv,
                     unsigned char *ciphertext,
                     int &ciphertext_len,
                     unsigned char *tag
    ) const;

    bool gcm_decrypt(const unsigned char *ciphertext,
                     int ciphertext_len,
                     const unsigned char *key,
                     const unsigned char *iv,
                     unsigned char *tag,
                     unsigned char *plaintext,
                     int &plaintext_len
    ) const;

    void hashAndSalt(const std::string &password, userInput user_input);
    bool VerifyPwd(const std::vector<unsigned char> &saltFromDoc);

    void HandleError() const;
    void HandleError(EVP_CIPHER_CTX *ctx) const;
    void HandleError(EVP_MD_CTX *mctx) const;
    void HandleError(EVP_KDF *kdf, EVP_KDF_CTX *kctx, OSSL_LIB_CTX *lib_ctx) const;

    IFileHandler &_fileHandler;
    ILogger &_logger;

};
