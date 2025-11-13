#include "SimpleCrypt.h"

#include "Builder.h"

SimpleCrypt::SimpleCrypt(ArgsHandler& argsHandler, const int argc, char *argv[])
        : _argsHandler(argsHandler), _argc(argc), _argv(argv) {};

void SimpleCrypt::Run() const {
    _argsHandler.Handle(_argc, _argv);
}
