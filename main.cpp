#include <iostream>
#include <ostream>
#include "ArgsHandler.h"
#include "commands/Commands.h"
#include "FileHandling/FileHandler.h"

int main(const int argc, char *argv[]) {
    try {
        FileHandler fileHandler;
        Commands cmd(fileHandler);
        ArgsHandler argsHandler(cmd);
        argsHandler.Handle(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
