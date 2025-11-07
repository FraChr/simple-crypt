#pragma once
#include <map>
#include <string>

#include "CommandTypes.h"
#include "../Interfaces/ICommands.h"
#include "../Interfaces/IFileHandler.h"

class Commands : public ICommands {
    public:
        std::map<CommandType, CommandFunc> commands;

        explicit Commands(IFileHandler& fileHandlerInstance);

        void executeCommand(CommandType type, FileInfo& file) override {
            if (commands.contains(type)) commands[type](file);
        }
    private:
        std::vector<unsigned char> hash(const std::string& password);
        bool validPassword(const std::string& password);
        void hashAndStorePassword(const FileInfo& file);
        void encrypt(const FileInfo& file);
        void decrypt(const FileInfo& file);

        bool gcm_encrypt(const unsigned char *plaintext,
            int plaintext_len,
            const unsigned char *key,
            unsigned char *iv,
            unsigned char *ciphertext,
            int &ciphertext_len, unsigned char *tag
        );

        bool gcm_decrypt(const unsigned char *ciphertext,
            int ciphertext_len,
            const unsigned char *key,
            const unsigned char *iv,
            unsigned char *tag,
            unsigned char *plaintext,
            int &plaintext_len
            );

        void HandleError();

        IFileHandler& _fileHandler;
        std::string _passwordFile = ".secrets";
};
