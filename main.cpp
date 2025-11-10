#include <assert.h>
#include <iostream>
#include <ostream>
#include "ArgumentHandler/ArgsHandler.h"
#include "commands/Commands.h"
#include "FileHandling/FileHandler.h"

#include <filesystem>

#include "Data/UI/UiText.h"
#include "Logger/Logger.h"
#include "Render/RenderCmd.h"

int main(const int argc, char *argv[]) {
    try {
        FileHandler fileHandler;
        Logger logger(fileHandler);
        Commands cmd(fileHandler, logger);
        ArgsHandler argsHandler(cmd);
        argsHandler.Handle(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    /*FileHandler fileHandler;
    Logger logger(fileHandler);
    logger.log(Logger::ERROR, "SOMETHING WENT WRONG");*/
}