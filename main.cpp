#include "ArgsHandler.h"
#include "commands/Commands.h"
#include "FileHandling/FileHandler.h"

int main(const int argc, char *argv[]) {
    FileHandler fileHandler;
    Commands cmd(fileHandler);
    ArgsHandler argsHandler(cmd);
    argsHandler.Handle(argc, argv);
    return 0;
}
