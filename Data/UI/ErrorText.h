#pragma once
#include <string>

struct ErrorText {
    static constexpr std::string FileExist = "File exists";
    static constexpr std::string FileNotFound = "File not found";
    static constexpr std::string FileNameNotFound = "Name not found";
};