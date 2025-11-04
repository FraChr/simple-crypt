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


void pr(const char *value) {
    const std::string val = value;
    if ( val == "portal") {
        std::cout << outputValues::draw << std::endl;
    }
    else {
        std::cout << "error\n";
    }
}

void ArgsHandler::Handle(const int &argc, char *argv[]) {
    std::string commandName;
    CommandType commandType{};
    FileInfo file;

    auto handlers = CreateHandlers(commandType, file);


    int opt = 0;
    while ((opt = getopt(argc, argv, options)) != -1) {
        auto op = static_cast<ArgsHandler::Option>(opt);
        if (handlers.contains(op))
            handlers[op](optarg);
        else {
            std::cerr << "unknown option " << opt;
        }
    }

    Commands com;

    const auto iterator = com.commands.find(commandType);
    if (commandType != CommandType::NONE) {
        iterator->second(file);
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
    handlers[Option::D] = [](const char*) {std::cout << outputValues::draw;};

    handlers[Option::MissingArgumentError] = [](const char*) {std::cout << "needs a value\n"; };
    handlers[Option::UnknownOptionError] = [](const char*) {std::cout << "unknown command\n"; };

    return handlers;
}





