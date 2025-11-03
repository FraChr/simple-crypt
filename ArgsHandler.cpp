#include "ArgsHandler.h"

#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <ostream>

#include "Data/UI/ErrorText.h"
#include "Data/UI/UiText.h"
#include "FileHandling/FileHandler.h"
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
    FileInfo file;

    std::map<char, std::function<void()>> handlers;
    // c for crypting needs to take password
    handlers['c'] = [&commandName] {commandName = optarg;};
    handlers['v'] = [&commandName] {commandName = optarg;};
    handlers['h'] = [&]{std::cout <<  outputValues::help;};
    /*handlers['f'] = [&file] {file.fileName = optarg;};*/
    handlers['p'] = [&file] {file.password = optarg;};

    handlers[':'] = [] {std::cout << "needs a value\n"; };
    handlers['?'] = [] {std::cout << "unknown command\n"; };

    /*handlers['d'] = []{std::cout << outputValues::draw << std::endl; };*/
    /*handlers['d'] = []{pr(optarg);};*/


    int opt = 0;
    while ((opt = getopt(argc, argv, "c:f:p:d:hv:")) != -1) {
        if (handlers.contains(opt)) handlers[opt]();
        else {
            std::cerr << "unknown option " << opt;
        }
    }

    if (!commandName.empty()) {
        if (Commands::commands.contains(commandName)) {
            Commands::commands[commandName](file);
        } else {
            std::cerr << "Unknown command: " << commandName;
        }
    }

        // for debuging remove for production
        for (; optind < argc; optind++) {
            std::cout << "extra args: " << argv[optind] << '\n';
        }
}