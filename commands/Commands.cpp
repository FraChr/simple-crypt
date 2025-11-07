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
#include <openssl/rand.h>

#include "../Data/UI/ErrorText.h"
#include "../Data/UI/UiText.h"
#include "../Render/RenderCmd.h"
#include <openssl/bio.h>
#include <openssl/bioerr.h>


Commands::Commands(IFileHandler& fileHandlerInstance) : _fileHandler(fileHandlerInstance) {
    commands[HASH] = [this](const FileInfo& file){hashAndStorePassword(file);};
    commands[CRYPT] = [this](const FileInfo& file){encrypt(file);};
    commands[DECRYPT] = [this](const FileInfo& file){decrypt(file);};
}

bool Commands::validPassword(const std::string& password) {
    const std::vector<unsigned char> hashedPass = hash(password);
    const std::vector<unsigned char> original = _fileHandler.readFromFile(_passwordFile);
    if (hashedPass == original) {
        return true;
    }
    return false;
}



void Commands::hashAndStorePassword(const FileInfo& file) {
    const std::vector<unsigned char> hexHash = hash(file.password);
    _fileHandler.writeToFile(_passwordFile, hexHash);
}



void Commands::encrypt(const FileInfo& file) {
    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        RenderCmd::WriteOut(EncryptionOutput::encryptCurrent);

        auto fileContents = _fileHandler.readFromFile(file.fileName);
        auto plaintext = fileContents.data();
        int plaintext_len = static_cast<int>(fileContents.size());

        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = keyFromFile.data();

        std::vector<unsigned char> ciphertext(fileContents.size() + 16);
        /*int ciphertext_len = ciphertext.size();*/
        int ciphertext_len = 0;
        unsigned char iv[16];
        unsigned char tag[16];




        bool res = gcm_encrypt(plaintext, plaintext_len, key, iv, ciphertext.data(), ciphertext_len, tag);

        if (!res) {
            RenderCmd::WriteError(EncryptDecryptError::encryptionFailure);
            return;
        }

        std::vector<unsigned char> out;
        out.insert(out.end(), iv, (iv) + 16);
        out.insert(out.end(), (ciphertext.data()), (ciphertext.data()) + ciphertext_len);
        out.insert(out.end(), (tag), (tag) + 16);
        _fileHandler.writeToFile(file.fileName, out);

        RenderCmd::WriteOut(EncryptionOutput::encryptSuccess);
    }else {
        RenderCmd::WriteError("file dont exist or wrong key\n");
    }
}

void Commands::decrypt(const FileInfo &file) {
    const bool validateKey = validPassword(file.password);
    if (_fileHandler.fileExists(file.fileName) && validateKey) {
        RenderCmd::WriteOut(EncryptionOutput::decryptCurrent);

        auto fileContents = _fileHandler.readFromFile(file.fileName);

        if (fileContents.size() < 32) {
            RenderCmd::WriteError(EncryptDecryptError::notValidOrCorrupt);
            return;
        }

        unsigned char iv[16]{};
        std::memcpy(iv, fileContents.data(), 16);

        unsigned char tag[16]{};
        std::memcpy(tag, fileContents.data() + fileContents.size() - 16, 16);

        int ciphertext_len = static_cast<int>(fileContents.size() - 32);
        auto ciphertext = (fileContents.data() + 16);

        auto keyFromFile = _fileHandler.readFromFile(_passwordFile);
        auto key = keyFromFile.data();




        std::vector<unsigned char> plaintext(ciphertext_len + 16);
        int plaintext_len = 0;

        auto res = gcm_decrypt(ciphertext, ciphertext_len, key, iv, tag, plaintext.data(), plaintext_len);

        if (!res) {
            RenderCmd::WriteError(EncryptDecryptError::decryptionFailure);

            return;
        }

        const std::vector out (
            plaintext.data(),
            plaintext.data() + plaintext_len);

        _fileHandler.writeToFile(file.fileName, out);


        RenderCmd::WriteOut(EncryptionOutput::decryptSuccess);
    } else {
        std::cerr << "file dont exist or wrong key\n";
        RenderCmd::WriteError(FileError::FileNotFoundOrExist);
    }

}

bool Commands::gcm_encrypt(const unsigned char *plaintext,
                       int plaintext_len,
                       const unsigned char *key,
                       unsigned char *iv,
                       unsigned char *ciphertext,
                       int &ciphertext_len, unsigned char *tag)
{
    int len, final_len = 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    const EVP_CIPHER* cipher = EVP_aes_256_gcm();
    const int iv_len = EVP_CIPHER_iv_length(cipher);

    if (RAND_bytes(iv, iv_len) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal(ctx, ciphertext + len, &final_len) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += final_len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag) != 1) {
        HandleError();
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
    int len = 0, final_len = 0;

    const EVP_CIPHER *cipher = EVP_aes_256_gcm();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        HandleError();
        return false;
    }

    if (EVP_DecryptInit_ex(ctx, cipher, nullptr, key, iv) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptFinal(ctx, plaintext + len, &final_len) != 1) {
        HandleError();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len + final_len;

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

void Commands::HandleError() {
    RenderCmd::WriteError(ERR_error_string(ERR_get_error(), nullptr));
}


std::vector<unsigned char> Commands::hash(const std::string& password) {
    unsigned char hashLength [SHA256_DIGEST_LENGTH];
    std::vector<unsigned char> passwordBytes(password.begin(), password.end());
    SHA256(passwordBytes.data(), passwordBytes.size(), hashLength);

    std::ostringstream hexHash;
    for (const auto i : hashLength) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    const std::string hashStr = hexHash.str();
    return {hashStr.begin(), hashStr.end()};
}


