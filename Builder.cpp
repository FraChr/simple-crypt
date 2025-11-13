#include "Builder.h"
#include "SimpleCrypt.h"

Builder::Builder(const int argc, char *argv[])
        :_fileHandler(), _logger(_fileHandler), _cmd(_fileHandler, _logger), _argsHandler(_cmd),
        _argc(argc), _argv(argv) {};

SimpleCrypt Builder::Build() {
    return {_argsHandler, _argc, _argv};
}