#include "ArgsHandler.h"

#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <ostream>

#include "Data/UI/ErrorText.h"
#include "Data/UI/UiText.h"
#include "POD/File.h"
#include "commands/Commands.h"

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
            std::cerr << "unknown option " << opt;
        }
    }

    if (commandType != NONE) {
        commands.executeCommand(commandType, file);
    }

        // for debuging remove for production
        for (; optind < argc; optind++) {
            std::cout << "extra args: " << argv[optind] << '\n';
        }
}

std::map<ArgsHandler::Option, std::function<void(const char*)>> ArgsHandler::CreateHandlers(CommandType& ct, FileInfo& file) {
    std::map<Option, std::function<void(const char*)>> handlers;
    handlers[Option::C] = [&ct](const char*) {ct = CommandType::CRYPT;};
    handlers[Option::V] = [&ct](const char*) {ct = CommandType::HASH;};
    handlers[Option::H] = [&](const char*){std::cout <<  outputValues::help;};
    handlers[Option::P] = [&file](const char* arg) {file.password = optarg;};
    handlers[Option::F] = [&file](const char* arg) {file.fileName = optarg;};
    handlers[Option::D] = [&ct](const char*) {ct = CommandType::DECRYPT;};
    /*handlers[Option::D] = [](const char*) {std::cout << outputValues::draw;};*/

    handlers[Option::MissingArgumentError] = [](const char*) {std::cerr << "needs a value\n"; };
    handlers[Option::UnknownOptionError] = [](const char*) {std::cerr << "unknown command\n"; };

    return handlers;
}





