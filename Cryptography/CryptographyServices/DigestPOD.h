#pragma once
#include <vector>

struct DigestResult {
    std::vector<unsigned char> key;
    std::vector<unsigned char> salt;
};
