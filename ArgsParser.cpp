#include "ArgsParser.h"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <getopt.h>
void print_help();

void ArgsParser::HandleArguments(const std::vector<std::string> &args) {

    /*if (args.empty()) {
        throw std::runtime_error("Too few arguments");
    }

    for (const auto &arg : args) {
        if (arg == "arg1") std::cout << "arg1 = " << arg << "YAYYYYY!!" << std::endl;
        else throw std::runtime_error("Unknown argument: " + arg);
    }*/
}

void print_help() {
    std::cout << "HELP!!" << std::endl;
}