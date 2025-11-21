#pragma once

#include "../../POD/File.h"

class IEncrypt {
    public:
        virtual ~IEncrypt() = default;
        virtual bool encrypt(
            const std::vector<unsigned char> &plaintext,
            const std::vector<unsigned char> &key,
            std::vector<unsigned char> &iv,
            std::vector<unsigned char> &ciphertext,
            std::vector<unsigned char> &tag
            ) const = 0;
};
