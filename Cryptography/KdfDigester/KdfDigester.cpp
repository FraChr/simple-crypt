#include "KdfDigester.h"

#include <openssl/core_names.h>
#include <openssl/crypto.h>
#include <openssl/kdf.h>
#include <openssl/params.h>

KdfDigester::KdfDigester(const unsigned int &iterations)
    : _iterations(iterations) {
}

CryptoStatus KdfDigester::DeriveKey(
    const std::string &password,
    std::vector<unsigned char> &salt,
    std::vector<unsigned char> &key) {
    EVP_KDF *kdf = nullptr;
    EVP_KDF_CTX *kctx = nullptr;
    OSSL_PARAM params[5], *p = params;
    OSSL_LIB_CTX *lib_ctx = nullptr;

    lib_ctx = OSSL_LIB_CTX_new();
    if (!lib_ctx) {
        Clean(kdf, kctx, lib_ctx);
        return {.result = false, .errorMessage = HandleError()};
    }
    kdf = EVP_KDF_fetch(lib_ctx, "PBKDF2", nullptr);
    if (!kdf) {
        Clean(kdf, kctx, lib_ctx);
        return {.result = false, .errorMessage = HandleError()};
    }
    kctx = EVP_KDF_CTX_new(kdf);
    if (!kctx) {
        Clean(kdf, kctx, lib_ctx);
        return {.result = false, .errorMessage = HandleError()};
    }

    std::string hashAlgorithm = "SHA256";
    std::string passwordCopy = password;

    /* Set Password */
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_PASSWORD, passwordCopy.data(), password.size());
    /* Set Salt */
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT, salt.data(), salt.size());
    /* Set iteration count (default 2048) */
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_ITER, &_iterations);
    /* Set the underlying hash functionused to derive the key */
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST, hashAlgorithm.data(), 0);

    *p = OSSL_PARAM_construct_end();

    /* Derive the key */
    if (EVP_KDF_derive(kctx, key.data(), key.size(), params) != 1) {
        Clean(kdf, kctx, lib_ctx);
        return {.result = false, .errorMessage = HandleError()};
    }

    Clean(kdf, kctx, lib_ctx);
    return {.result = true};
}

void KdfDigester::Clean(EVP_KDF *kdf, EVP_KDF_CTX *kctx, OSSL_LIB_CTX *lib_ctx) {
    if (kdf) EVP_KDF_free(kdf);
    if (kctx) EVP_KDF_CTX_free(kctx);
    if (lib_ctx) OSSL_LIB_CTX_free(lib_ctx);
}
