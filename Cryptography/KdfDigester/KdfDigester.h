#pragma once
#include <string>
#include <vector>
#include <openssl/types.h>

#include "IKdfDigester.h"
#include "../CryptographyBase.h"
#include "../CryptoStatus.h"

class KdfDigester : public IKdfDigester, CryptographyBase {
public:
    KdfDigester(const unsigned int &iterations = 2048);

    CryptoStatus DeriveKey(
        const std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
    ) override;

private:
    void Clean(EVP_KDF *kdf, EVP_KDF_CTX *kctx, OSSL_LIB_CTX *lib_ctx);
    unsigned int _iterations;
};
