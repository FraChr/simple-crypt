#pragma once
#include <map>
#include <string>

#include "CommandTypes.h"

class Commands {
    public:
        std::map<CommandType, CommandFunc> commands;

        Commands();
    private:
        std::string hash(std::string password);
        bool validPassword(const FileInfo& file);
        void hashAndStorePassword(FileInfo& file);
        void crypt(FileInfo& file);
};