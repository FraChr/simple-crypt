#pragma once

#include "IEncrypt.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"
#include "../POD/File.h"

class AesGcmEncryptor : public IEncrypt{
public:
    bool encrypt(
            const std::vector<unsigned char> &plaintext,
            const std::vector<unsigned char> &key,
            std::vector<unsigned char> &iv,
            std::vector<unsigned char> &ciphertext,
            std::vector<unsigned char> &tag
            ) const override;
};
