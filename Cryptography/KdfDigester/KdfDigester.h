#pragma once
#include <string>
#include <vector>

#include "IKdfDigester.h"

class KdfDigester : public IKdfDigester {
public:
    KdfDigester(const unsigned int &iterations = 2048);
    bool DeriveKey(
        const std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
        ) override;


private:
    unsigned int _iterations;
};
