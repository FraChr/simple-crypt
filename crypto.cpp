#include "crypto.h"
#include <iostream>

#include "ArgsParser.h"
#include "Data/UiText.h"


void crypto::run(const std::vector<std::string> &args) {
    std::cout << outputValues::menuOptions << std::endl;


    ArgsParser::HandleArguments(args);


}
