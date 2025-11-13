#pragma once

#include "SimpleCrypt.h"
#include "ArgumentHandler/ArgsHandler.h"
#include "commands/Commands.h"
#include "FileHandling/FileHandler.h"
#include "Logger/Logger.h"

class Builder {
    public:
        Builder(int argc, char *argv[]);

        SimpleCrypt Build();
    private:
        FileHandler _fileHandler;
        Logger _logger;
        Commands _cmd;
        ArgsHandler _argsHandler;
        int _argc;
        char **_argv;
};
