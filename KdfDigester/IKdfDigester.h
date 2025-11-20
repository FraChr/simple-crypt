#pragma once
#include <string>
#include <vector>

class IKdfDigester {
public:
    virtual ~IKdfDigester() = default;
    virtual bool DeriveKey(
       std::string &password,
       std::vector<unsigned char> &salt,
       std::vector<unsigned char> &key
       ) = 0;

    /*virtual bool VerifyDigest(
        std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
        ) = 0;*/
};
