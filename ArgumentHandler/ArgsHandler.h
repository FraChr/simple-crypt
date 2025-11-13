#pragma once
#include <map>
#include "../commands/CommandTypes.h"
#include "../Interfaces/ICommands.h"


class ArgsHandler {
public:
    explicit ArgsHandler(ICommands &cmdInstance);

    void Handle(const int &argc, char *argv[]);

private:
    const char *options = ":qchdf:p:d:v";

    enum class Option : int {
        ENCRYPT = 'c',
        HELP = 'h',
        PASSWORD = 'p',
        FILE = 'f',
        DECRYPT = 'd',
        DRAW = 'q',
        COMPRESS = 'v',

        MissingArgumentError = ':',
        UnknownOptionError = '?',
    };

    std::map<Option, std::function<void(const char *)> > CreateHandlers(CommandType &ct, userInput &file);

    ICommands &commands;
};
