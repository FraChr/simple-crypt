#pragma once

#include <openssl/types.h>

#include "IDecrypt.h"
#include "IEncrypt.h"
#include "../CryptographyBase.h"
#include "../CryptoStatus.h"
#include "../../Interfaces/IFileHandler.h"

class AesGcmCipher : public IEncrypt, public IDecrypt, public CryptographyBase {
public:
    CryptoStatus encrypt(
        const std::vector<unsigned char> &plaintext,
        const std::vector<unsigned char> &key,
        std::vector<unsigned char> &iv,
        std::vector<unsigned char> &ciphertext,
        std::vector<unsigned char> &tag
    ) const override;

    CryptoStatus decrypt(
        const std::vector<unsigned char> &ciphertext,
        const std::vector<unsigned char> &key,
        std::vector<unsigned char> &iv,
        std::vector<unsigned char> &tag,
        std::vector<unsigned char> &plaintext
    ) const override;

private:
    void Clean(EVP_CIPHER_CTX *ctx) const;
    int _tagSize = 16;
};
