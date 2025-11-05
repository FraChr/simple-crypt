#include "Commands.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

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
    const auto hashedPass = hash(password);
    const std::string original = _fileHandler.readFromFile(_passwordFile);
    if (hashedPass == original) {
        return true;
    }
    return false;
}



void Commands::hashAndStorePassword(const FileInfo& file) {
    std::cout << "password entered is " << file.password << std::endl;
    const std::string hexHash = hash(file.password);
    _fileHandler.writeToFile(_passwordFile, hexHash);
}

void Commands::crypt(const FileInfo& file) {



    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        std::cout << "crypting file..." << std::endl;
        auto fileContents = _fileHandler.readFromFile(file.fileName);
        /*_fileHandler.writeToFile("RANDOMTESTFILE.txt", fileContents);*/
        const unsigned char * plaintext = reinterpret_cast<const unsigned char *>(fileContents.c_str());

        auto plaintext_len = fileContents.size();
        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = reinterpret_cast<const unsigned char *>(keyFromFile.c_str());
        /*auto key_len = sizeof(key);*/

        unsigned char iv[] = "1234567887654321";
        int iv_len = sizeof(iv);

        std::vector<unsigned char> ciphertext(fileContents.size() + 16);
        int ciphertext_len = ciphertext.size();
        /*unsigned char *ciphertext = fileContents.size() + 16;*/

        auto res = gcm_encrypt(plaintext, plaintext_len, key, iv, ciphertext.data(), ciphertext_len);

        std::cout << "result of gcm_encrypt: " << res << std::endl;

        if (!res) {
            std::cerr << "Encryption failed\n";
            return;
        }

        _fileHandler.writeToFile(file.fileName + ".enc",
            std::string(reinterpret_cast<char*>(ciphertext.data()), ciphertext_len));

        std::cout << "File encrypted successfully.\n";
    }else {
        std::cerr << "file dont exist or wrong key\n";
    }

    /*file.passwordHashed = hexHash.str();*/

    /*FileHandler tofile(file.fileName);

     tofile.writeToFile(hexHash.str());*/
}

void Commands::decrypt(const FileInfo &file) {
    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        std::cout << "decrypting file...\n";

        auto fileContents = _fileHandler.readFromFile(file.fileName);
        auto cyphertext = reinterpret_cast<const unsigned char *>(fileContents.c_str());
        auto cyphertext_len = fileContents.size();
        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = reinterpret_cast<const unsigned char *>(keyFromFile.c_str());
        unsigned char iv[] = "1234567887654321";
        std::vector<unsigned char> plaintext(fileContents.size() + 16);
        int plaintext_len = plaintext.size();

        auto res = gcm_decrypt(cyphertext, cyphertext_len, key, iv, plaintext.data(), plaintext_len);

        std::cout << "result of gcm_decrypt: " << res << std::endl;
        std::cout << "decrypted plaintext = " << std::string(reinterpret_cast<char*>(plaintext.data()), plaintext_len) << std::endl;

        if (!res) {
            std::cerr << "Decryption failed\n";
            return;
        }

        /*_fileHandler.writeToFile(file.fileName + ".enc",
            std::string(reinterpret_cast<char*>(ciphertext.data()), ciphertext_len));*/
        _fileHandler.writeToFile(file.fileName + ".dec",
            std::string(reinterpret_cast<char*>(plaintext.data()), plaintext_len));

        std::cout << "File decrypted successfully.\n";
    } else {
        std::cerr << "file dont exist or wrong key\n";
    }

}

// currently not working as expected still learning

/*bool Commands::gcm_encrypt(const unsigned char *plaintext,
                       int plaintext_len,
                       const unsigned char *key,
                       const unsigned char *iv,
                       unsigned char *ciphertext,
                       int &ciphertext_len)
{
    int len;
    int final_len;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {

        return false;
    }
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    if (EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, plaintext, plaintext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += final_len;

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool Commands::gcm_decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key,
    const unsigned char *iv, unsigned char *plaintext, int &plaintext_len)
{
    int len;
    int final_len;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return false;
    }
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    if (EVP_DecryptUpdate(ctx, plaintext, &plaintext_len, ciphertext, ciphertext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    plaintext_len += len;
    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len += final_len;

    EVP_CIPHER_CTX_free(ctx);
    return true;
}*/


void Commands::handleErrors() {
    unsigned long errCode;

    std::cout << "An error occurred\n";
    while (errCode = ERR_get_error()) {
        const char *err = ERR_error_string(errCode, nullptr);
        std::cout << "Error: " << err << '\n';
    }
    abort();
}


std::string Commands::hash(const std::string& password) {
    unsigned char hashLength [SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hashLength);

    std::ostringstream hexHash;
    for (const auto i : hashLength) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return hexHash.str();
}


