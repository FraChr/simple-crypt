#include "KdfDigester.h"

#include <openssl/core_names.h>
#include <openssl/crypto.h>
#include <openssl/kdf.h>
#include <openssl/params.h>
#include <openssl/types.h>

KdfDigester::KdfDigester(const unsigned int &iterations)
    : _iterations(iterations) {}

bool KdfDigester::DeriveKey(
    std::string &password,
    std::vector<unsigned char> &salt,
    std::vector<unsigned char> &key) {

    EVP_KDF *kdf = nullptr;
    EVP_KDF_CTX *kctx = nullptr;
    OSSL_PARAM params[5], *p = params;
    OSSL_LIB_CTX *lib_ctx = nullptr;

    /*_logger.log(LogLevel::INFO, "kdf_passwd method");*/

    lib_ctx = OSSL_LIB_CTX_new();
    if (!lib_ctx) {
        /*HandleError();*/
        OSSL_LIB_CTX_free(lib_ctx);
        return false;
    }
    kdf = EVP_KDF_fetch(lib_ctx, "PBKDF2", nullptr);
    if (!kdf) {
        /*HandleError(kdf, kctx, lib_ctx);*/
        OSSL_LIB_CTX_free(lib_ctx);
        EVP_KDF_free(kdf);

        return false;
    }
    kctx = EVP_KDF_CTX_new(kdf);
    if (!kctx) {
        /*HandleError(kdf, kctx, lib_ctx);*/
        OSSL_LIB_CTX_free(lib_ctx);
        EVP_KDF_free(kdf);
        EVP_KDF_CTX_free(kctx);
        return false;
    }

    std::string hashAlgorithm = "SHA256";

    /* Set Password */
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_PASSWORD, password.data(), password.size());
    /* Set Salt */
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT, salt.data(), salt.size());
    /* Set iteration count (default 2048) */
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_ITER, &_iterations);
    /* Set the underlying hash functionused to derive the key */
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST, hashAlgorithm.data(), 0);

    *p = OSSL_PARAM_construct_end();

    /* Derive the key */
    if (EVP_KDF_derive(kctx, key.data(), key.size(), params) != 1) {
        /*HandleError(kdf, kctx, lib_ctx);*/
        OSSL_LIB_CTX_free(lib_ctx);
        EVP_KDF_free(kdf);
        EVP_KDF_CTX_free(kctx);
        return false;
    }


    EVP_KDF_CTX_free(kctx);
    EVP_KDF_free(kdf);
    OSSL_LIB_CTX_free(lib_ctx);
    return true;
}
