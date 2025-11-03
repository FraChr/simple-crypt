#pragma once
#include <string>

struct FileInfo {
    const std::string fileName = ".secrets";
    std::string password;
    std::string passwordHashed;
};
