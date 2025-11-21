#pragma once
#include <vector>

class IDecrypt {
public:
    virtual ~IDecrypt() = default;

    virtual bool decrypt(
        const std::vector<unsigned char> &ciphertext,
        const std::vector<unsigned char> &key,
        std::vector<unsigned char> &iv,
        std::vector<unsigned char> &tag,
        std::vector<unsigned char> &plaintext
    ) const = 0;
};