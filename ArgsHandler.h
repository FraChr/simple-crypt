#pragma once
#include <map>

#include "commands/CommandTypes.h"


class ArgsHandler {
    public:
        void Handle(const int &argc, char *argv[]);
    private:
        /*std::map<char, std::function<void(const char*)>> CreateHandlers(CommandType& ct, FileInfo& file);*/
        const char* options = "chvdf:p:d:";
        enum class Option : int{
            C = 'c',
            V = 'v',
            H = 'h',
            P = 'p',
            F = 'f',
            D = 'd',
            MissingArgumentError = ':',
            UnknownOptionError = '?',
        };
        std::map<Option, std::function<void(const char*)>> CreateHandlers(CommandType& ct, FileInfo& file);
};
