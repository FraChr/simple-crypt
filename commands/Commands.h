#pragma once
#include <map>
#include <string>

#include "CommandTypes.h"

class Commands {
    public:
        static std::map<std::string, CommandFunc> commands;
    private:
        std::string hash(const FileInfo& file);
};