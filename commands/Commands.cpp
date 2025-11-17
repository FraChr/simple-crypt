#include "Commands.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../FileHandling/FileHandler.h"
#include "../POD/File.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include "../Data/UI/ErrorText.h"
#include "../Data/UI/UiText.h"
#include "../Logger/Logger.h"
#include "../Render/RenderCmd.h"

Commands::Commands(IFileHandler &fileHandlerInstance, ILogger &loggerInstance)
    : _fileHandler(fileHandlerInstance), _logger(loggerInstance) {
    commands[CRYPT] = [this](const userInput &userInput) { encrypt(userInput); };
    commands[DECRYPT] = [this](const userInput &userInput) { decrypt(userInput); };
    commands[COMPRESS] = [this](const userInput &userInput) {compress(userInput);};
}

/*
 *   TODO
 *      Go through file and count occurrence of word or char;
 *      save to map e.g (word -> occurrence);
 *      use huffman tree on map;
 *      use bit codes from huffman tree to remap the words with the bit codes;
 *      save a "dictionary" of the code -> word for decompression;
 */
void Commands::compress(const userInput &file) {
    RenderCmd::WriteOut("testing compress method of commands\n");
    auto occurrences = CountCharOccurrences(file.filename);
    int n = 0;
    for (const auto &[key, value] : occurrences) {
        std::cout << n << " Key " << key << " occurrence " << value << std::endl;
        n++;
    }
}

std::unordered_map<unsigned char, int> Commands::CountCharOccurrences(const std::string &filename) {
    const auto filedata = _fileHandler.readFromFile(filename);

    std::unordered_map<unsigned char, int> occurrences;
    for (const auto &data : filedata) {
        if (data != '\r') occurrences[data]++;
    }
    return occurrences;

}


void Commands::encrypt(const userInput &userInput) {
    const EVP_CIPHER *cipher = EVP_aes_256_gcm();
    const int iv_len = EVP_CIPHER_iv_length(cipher);
    const int tag_len = 16;

    _logger.log(LogLevel::INFO, std::string(EncryptionOutput::logEncryptStart));

    RenderCmd::WriteOut(EncryptionOutput::encryptCurrent);


    auto fileContents = _fileHandler.readFromFile(userInput.filename);
    auto plaintext = fileContents.data();
    int plaintext_len = static_cast<int>(fileContents.size());
    /*int plaintext_len = fileContents.size();*/

    std::vector<unsigned char> keyVec = hash(userInput.password);
    const unsigned char *key = keyVec.data();

    std::vector<unsigned char> ciphertext(fileContents.size() + 16);
    int ciphertext_len = 0;

    std::vector<unsigned char> iv(iv_len);

    std::vector<unsigned char> tag(tag_len);


    bool res = gcm_encrypt(
        plaintext,
        plaintext_len,
        key,
        iv.data(),
        ciphertext.data(),
        ciphertext_len,
        tag.data()
        );

    if (!res) {
        RenderCmd::WriteError(EncryptDecryptError::encryptionFailure);
        _logger.log(LogLevel::ERROR, std::string(EncryptDecryptError::logEncryptionFailure));
        return;
    }

    std::vector<unsigned char> out;
    out.insert(out.end(), iv.begin(), iv.end());
    out.insert(out.end(), ciphertext.data(), ciphertext.data() + ciphertext_len);
    out.insert(out.end(), tag.begin(), tag.end());

    _fileHandler.writeToFile(userInput.filename, out);

    RenderCmd::WriteOut(EncryptionOutput::encryptSuccess);
}

void Commands::decrypt(const userInput &userInput) {
    const EVP_CIPHER *cipher = EVP_aes_256_gcm();
    const int iv_len = EVP_CIPHER_iv_length(cipher);
    const int tag_len = 16;


    _logger.log(LogLevel::INFO, std::string(DecryptionOutput::logDecryptStart));

    RenderCmd::WriteOut(DecryptionOutput::decryptCurrent);

    auto fileContents = _fileHandler.readFromFile(userInput.filename);

    if (fileContents.size() < iv_len + tag_len) {
        RenderCmd::WriteError(EncryptDecryptError::notValidOrCorrupt);
        return;
    }

    std::vector iv(fileContents.begin(), fileContents.begin() + iv_len);

    std::vector tag(fileContents.end() - tag_len, fileContents.end());

    int ciphertext_len = fileContents.size() - iv_len - tag_len;
    std::vector ciphertext(
        fileContents.begin() + iv_len,
        fileContents.begin() + iv_len + ciphertext_len
        );

    std::vector<unsigned char> key = hash(userInput.password);
    /*const unsigned char *key = keyVec.data();*/


    std::vector<unsigned char> plaintext(ciphertext_len);
    int plaintext_len = 0;

    auto res = gcm_decrypt(
               ciphertext.data(),
                        ciphertext_len,
                        key.data(),
                        iv.data(),
                        tag.data(),
                        plaintext.data(),
                        plaintext_len
                        );

    if (!res) {
        RenderCmd::WriteError(EncryptDecryptError::logDecryptionFailure);

        return;
    }

    const std::vector out(
        plaintext.data(),
        plaintext.data() + plaintext_len);

    _fileHandler.writeToFile(userInput.filename, out);


    RenderCmd::WriteOut(DecryptionOutput::decryptSuccess);
}

/*
 *  TODO encrypt in intervals of a fixed size bit size e.g 4kb
 */
bool Commands::gcm_encrypt(const unsigned char *plaintext,
                           const int plaintext_len,
                           const unsigned char *key,
                           unsigned char *iv,
                           unsigned char *ciphertext,
                           int &ciphertext_len, unsigned char *tag) {
    _logger.log(LogLevel::INFO, std::string(EncryptionOutput::logEncryptedCurrent));
    int len, final_len = 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        HandleError();
        return false;
    }

    const EVP_CIPHER *cipher = EVP_aes_256_gcm();
    const int iv_len = EVP_CIPHER_iv_length(cipher);

    if (RAND_bytes(iv, iv_len) != 1) {
        HandleError(ctx);
        return false;
    }

    if (EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv) != 1) {
        HandleError(ctx);
        return false;
    }

    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1) {
        HandleError(ctx);
        return false;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal(ctx, ciphertext + len, &final_len) != 1) {
        HandleError(ctx);
        return false;
    }
    ciphertext_len += final_len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag) != 1) {
        HandleError(ctx);
        return false;
    }
    _logger.log(LogLevel::INFO, std::string(EncryptionOutput::logEncryptDone));
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

/*
 *   TODO decrypt in intervals of a fixed size bit size e.g 4kb
 */

bool Commands::gcm_decrypt(const unsigned char *ciphertext,
                           const int ciphertext_len,
                           const unsigned char *key,
                           const unsigned char *iv,
                           unsigned char *tag,
                           unsigned char *plaintext,
                           int &plaintext_len) {
    _logger.log(LogLevel::INFO, std::string(DecryptionOutput::logDecryptCurrent));
    int len = 0, final_len = 0;

    const EVP_CIPHER *cipher = EVP_aes_256_gcm();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        HandleError();
        return false;
    }

    if (EVP_DecryptInit_ex(ctx, cipher, nullptr, key, iv) != 1) {
        HandleError(ctx);
        return false;
    }

    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1) {
        HandleError(ctx);
        return false;
    }
    plaintext_len = len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag) != 1) {
        HandleError(ctx);
        return false;
    }

    if (EVP_DecryptFinal(ctx, plaintext + len, &final_len) != 1) {
        HandleError(ctx);
        return false;
    }
    plaintext_len = len + final_len;

    _logger.log(LogLevel::INFO, std::string(DecryptionOutput::logDecryptDone));
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

void Commands::HandleError() const {
    char errBuffer[256];
    ERR_error_string(ERR_get_error(), errBuffer);
    _logger.log(LogLevel::ERROR, errBuffer);
}

void Commands::HandleError(EVP_CIPHER_CTX *ctx) const {
    HandleError();
    if (ctx) EVP_CIPHER_CTX_free(ctx);
}

void Commands::HandleError(EVP_MD_CTX *mctx) const {
    HandleError();
    if (mctx) EVP_MD_CTX_free(mctx);
}

bool Commands::hashPassword(const unsigned char *data,
                            const size_t data_len,
                            unsigned char *out_digest,
                            unsigned int *out_len) {
    const EVP_MD *md = nullptr;
    md = EVP_sha256();
    /*md = EVP_sha3_256();*/
    if (!md) {
        HandleError();
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        HandleError(mdctx);
        return false;
    }

    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        HandleError(mdctx);
        return false;
    }
    if (EVP_DigestUpdate(mdctx, data, data_len) != 1) {
        HandleError(mdctx);
        return false;
    }
    if (EVP_DigestFinal_ex(mdctx, out_digest, out_len) != 1) {
        HandleError(mdctx);
        return false;
    }
    EVP_MD_CTX_free(mdctx);
    return true;
}


std::vector<unsigned char> Commands::hash(const std::string &password) {
    unsigned char hashBytes[SHA256_DIGEST_LENGTH];
    unsigned int hashLen = 0;

    std::vector<unsigned char> passwordBytes(password.begin(), password.end());

    hashPassword(passwordBytes.data(), passwordBytes.size(), hashBytes, &hashLen);

    return {hashBytes, hashBytes + SHA256_DIGEST_LENGTH};
}