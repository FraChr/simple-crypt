#include "ArgsHandler.h"

#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <ostream>
#include "Data/UiText.h"

static void testingPassage(const char *value) {
    std::cout << "arg from crypt from cmd argument to command ---> " << value;
}

void crypt() {
    /*std::cout << "hashing string using SHA256" << " " << optarg << std::endl;*/
    /*std::cout << "hashing string using SHA256" << " " << std::endl;*/
    testingPassage(optarg);
}


void ArgsHandler::Handle(const int &argc, char *argv[]) {

    std::map<char, std::function<void()>> handlers;
    /*handlers['c'] = [&](){std::cout << "hashing string using SHA256" << " " << optarg << std::endl;};*/
    handlers['c'] = {&crypt};
    handlers['d'] = [](){std::cout << outputValues::draw << std::endl; };
    handlers['h'] = [](){std::cout << outputValues::help;};


    int opt = 0;
    while ((opt = getopt(argc, argv, "c:dh")) != -1) {
        if (handlers.contains(opt)) handlers[opt]();
        else {
            std::cerr << "unknown option " << opt;
        }






        /*switch (opt) {
            case 'b':
                std::cout << "testing3" << optarg << std::endl;
                break;
        }*/
    }
}
