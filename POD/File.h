#pragma once
#include <string>
#include <vector>
struct userInput {
    std::string filename;
    std::string password;
    /*std::vector<unsigned char> key;*/
    std::vector<unsigned char> key;
    std::vector<unsigned char> salt;
};

/*struct keyAndSalt {
    /*static std::vector<unsigned char> key;
    static std::vector<unsigned char> salt;#1#

    std::vector<unsigned char> key;
    std::vector<unsigned char> salt;
};*/