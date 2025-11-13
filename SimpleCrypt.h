#pragma once
#include "ArgumentHandler/ArgsHandler.h"

class SimpleCrypt {
    public:
        SimpleCrypt(ArgsHandler& argsHandler, const int argc, char *argv[]);

        void Run() const;
    private:
        ArgsHandler& _argsHandler;
        int _argc;
        char **_argv;
};
