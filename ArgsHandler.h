#pragma once
#include <map>

#include "commands/CommandTypes.h"
#include "Interfaces/ICommands.h"


class ArgsHandler {
    public:
        ArgsHandler(ICommands& cmdInstance);
        void Handle(const int &argc, char *argv[]);
    private:
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
        ICommands& commands;
};
