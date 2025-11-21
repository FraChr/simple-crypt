#include "AesGcmCipher.h"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include "../../Data/UI/ErrorText.h"
#include "../../Data/UI/UiText.h"
#include "../../Logger/Logger.h"

/*TODO encrypt in intervals of a fixed size bit size e.g 4kb*/
bool AesGcmCipher::encrypt(
    const std::vector<unsigned char> &plaintext,
    const std::vector<unsigned char> &key,
    std::vector<unsigned char> &iv,
    std::vector<unsigned char> &ciphertext,
    std::vector<unsigned char> &tag) const {

    int len, final_len = 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return false;
    }

    const EVP_CIPHER *cipher = EVP_aes_256_gcm();
    const int iv_len = EVP_CIPHER_iv_length(cipher);
    iv.resize(iv_len);
    ciphertext.resize(plaintext.size());
    tag.resize(16);

    if (RAND_bytes(iv.data(), iv_len) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_EncryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }


    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    /*ciphertext_len = len;*/

    if (EVP_EncryptFinal(ctx, ciphertext.data() + len, &final_len) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext.resize(len + final_len);

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag.data()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

/*TODO decrypt in intervals of a fixed size bit size e.g 4kb*/

bool AesGcmCipher::decrypt(
    const std::vector<unsigned char> &ciphertext,
    const std::vector<unsigned char> &key,
    std::vector<unsigned char> &iv,
    std::vector<unsigned char> &tag,
    std::vector<unsigned char> &plaintext) const {

    int len = 0, final_len = 0;

    const EVP_CIPHER *cipher = EVP_aes_256_gcm();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        /*HandleError();*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag.data()) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptFinal(ctx, plaintext.data() + len, &final_len) != 1) {
        /*HandleError(ctx);*/
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext.resize(len + final_len);

    EVP_CIPHER_CTX_free(ctx);
    return true;
}
