#include <iostream>
#include <ostream>
#include "ArgumentHandler/ArgsHandler.h"
#include "commands/Commands.h"
#include "FileHandling/FileHandler.h"
#include <filesystem>
#include "Logger/Logger.h"

int main(const int argc, char *argv[]) {
    try {
        FileHandler fileHandler;
        Logger logger(fileHandler);
        Commands cmd(fileHandler, logger);
        ArgsHandler argsHandler(cmd);
        argsHandler.Handle(argc, argv);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }


}