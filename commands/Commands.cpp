#include "Commands.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../FileHandling/FileHandler.h"
#include "../POD/File.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>


Commands::Commands(IFileHandler& fileHandlerInstance) : _fileHandler(fileHandlerInstance) {
    commands[HASH] = [this](const FileInfo& file){hashAndStorePassword(file);};
    commands[CRYPT] = [this](const FileInfo& file){crypt(file);};
    commands[DECRYPT] = [this](const FileInfo& file){decrypt(file);};
}

bool Commands::validPassword(const std::string& password) {
    const std::vector<char> hashedPass = hash(password);
    const std::vector<char> original = _fileHandler.readFromFile(_passwordFile);
    if (hashedPass == original) {
        return true;
    }
    return false;
}



void Commands::hashAndStorePassword(const FileInfo& file) {
    std::cout << "password entered is " << file.password << std::endl;
    const std::vector<char> hexHash = hash(file.password);
    _fileHandler.writeToFile(_passwordFile, hexHash);
}

void Commands::crypt(const FileInfo& file) {
    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        std::cout << "crypting file..." << std::endl;

        auto fileContents = _fileHandler.readFromFile(file.fileName);

        const unsigned char * plaintext = reinterpret_cast<const unsigned char *>(fileContents.data());


        auto plaintext_len = fileContents.size();
        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = reinterpret_cast<const unsigned char *>(keyFromFile.data());


        unsigned char iv[] = "1234567887654321";
        unsigned char tag[16];

        std::vector<unsigned char> ciphertext(fileContents.size() + 16);
        int ciphertext_len = ciphertext.size();

        auto res = gcm_encrypt(plaintext, plaintext_len, key, iv, ciphertext.data(), ciphertext_len, tag);

        if (!res) {
            std::cerr << "Encryption failed\n";
            return;
        }

        std::vector<char> out;
        out.insert(out.end(), reinterpret_cast<char*>(iv), reinterpret_cast<char*>(iv) + 16);
        out.insert(out.end(), reinterpret_cast<char*>(ciphertext.data()), reinterpret_cast<char*>(ciphertext.data()) + ciphertext_len);
        out.insert(out.end(), reinterpret_cast<char*>(tag), reinterpret_cast<char*>(tag) + 16);

        _fileHandler.writeToFile(file.fileName, out);

        std::cout << "File encrypted successfully.\n";
    }else {
        std::cerr << "file dont exist or wrong key\n";
    }
}

void Commands::decrypt(const FileInfo &file) {
    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        std::cout << "decrypting file...\n";

        auto fileContents = _fileHandler.readFromFile(file.fileName);

        if (fileContents.size() < 32) {
            std::cerr << "corrupt!\n";
            return;
        }

        unsigned char iv[16]{};
        std::memcpy(iv, fileContents.data(), 16);

        unsigned char tag[16]{};
        std::memcpy(tag, fileContents.data() + fileContents.size() - 16, 16);

        auto ciphertext_len = fileContents.size() - 32;
        auto ciphertext = reinterpret_cast<const unsigned char*>(fileContents.data() + 16);

        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = reinterpret_cast<const unsigned char *>(keyFromFile.data());


        std::vector<unsigned char> plaintext(ciphertext_len + 16);
        int plaintext_len = 0;

        auto res = gcm_decrypt(ciphertext, ciphertext_len, key, iv, tag, plaintext.data(), plaintext_len);

        if (!res) {
            std::cerr << "Decryption failed\n";
            return;
        }

        const std::vector out (
            reinterpret_cast<char*>(plaintext.data()),
            reinterpret_cast<char*>(plaintext.data() + plaintext_len));

        _fileHandler.writeToFile(file.fileName, out);


        std::cout << "File decrypted successfully.\n";
    } else {
        std::cerr << "file dont exist or wrong key\n";
    }

}

bool Commands::gcm_encrypt(const unsigned char *plaintext,
                       int plaintext_len,
                       const unsigned char *key,
                       const unsigned char *iv,
                       unsigned char *ciphertext,
                       int &ciphertext_len, unsigned char *tag)
{
    int len;
    int final_len = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {

        return false;
    }
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal(ctx, ciphertext + len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += final_len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool Commands::gcm_decrypt(const unsigned char *ciphertext,
    int ciphertext_len,
    const unsigned char *key,
    const unsigned char *iv,
    unsigned char *tag,
    unsigned char *plaintext,
    int &plaintext_len)
{
    int len = 0;
    int final_len = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {

        return false;
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptFinal(ctx, plaintext + len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len + final_len;

    EVP_CIPHER_CTX_free(ctx);
    return true;
}



std::vector<char> Commands::hash(const std::string& password) {
    unsigned char hashLength [SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hashLength);

    std::ostringstream hexHash;
    for (const auto i : hashLength) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    const std::string hashStr = hexHash.str();
    return std::vector<char>(hashStr.begin(), hashStr.end());
}


