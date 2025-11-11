#include "ArgsHandler.h"
#include <functional>
#include <getopt.h>
#include <map>
#include "../Data/UI/ErrorText.h"
#include "../Data/UI/UiText.h"
#include "../POD/File.h"
#include "../commands/Commands.h"
#include "../Render/RenderCmd.h"

ArgsHandler::ArgsHandler(ICommands& cmdInstance) : commands(cmdInstance) {}

void ArgsHandler::Handle(const int &argc, char *argv[]) {
    std::string commandName;
    CommandType commandType{};
    FileInfo file;

    auto handlers = CreateHandlers(commandType, file);

    int opt = 0;
    while ((opt = getopt(argc, argv, options)) != -1) {
        auto op = static_cast<Option>(opt);
        if (handlers.contains(op))
            handlers[op](optarg);
        else {
            throw std::exception();
        }
    }

    if (commandType != NONE) {
        commands.executeCommand(commandType, file);
    }

        // for debuging remove for production
        /*for (; optind < argc; optind++) {
            RenderCmd::WriteOut("extra args: ");
        }*/
}

std::map<ArgsHandler::Option, std::function<void(const char*)>> ArgsHandler::CreateHandlers(CommandType& ct, FileInfo& file) {
    std::map<Option, std::function<void(const char*)>> handlers;
    handlers[Option::ENCRYPT] = [&ct](const char*) {ct = CommandType::CRYPT;};
    handlers[Option::HELP] = [&](const char*){RenderCmd::WriteOut(Support::help);};
    handlers[Option::PASSWORD] = [&file](const char* arg) {file.password = optarg;};
    handlers[Option::FILE] = [&file](const char* arg) {file.fileName = optarg;};
    handlers[Option::DECRYPT] = [&ct](const char*) {ct = CommandType::DECRYPT;};
    handlers[Option::DRAW] = [](const char*) {RenderCmd::WriteOut(Art::drawCake);};

    handlers[Option::MissingArgumentError] = [](const char*) {
        RenderCmd::WriteError(CommandError::commandMissingArg);
        RenderCmd::WriteOut(Support::help);
    };
    handlers[Option::UnknownOptionError] = [](const char*) {
        RenderCmd::WriteError(CommandError::unknownCommand);
        RenderCmd::WriteOut(Support::help);
    };

    return handlers;
}





