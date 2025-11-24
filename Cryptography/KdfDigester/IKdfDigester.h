#pragma once
#include <string>
#include <vector>

#include "../CryptoStatus.h"

class IKdfDigester {
public:
    virtual ~IKdfDigester() = default;

    virtual CryptoStatus DeriveKey(
        const std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
    ) = 0;

    /*virtual bool VerifyDigest(
        std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
        ) = 0;*/
};
