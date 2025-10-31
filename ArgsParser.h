#pragma once

#include <string>
#include <vector>


class ArgsParser {
    public:
        /*ArgsParser(std::vector<std::string> &args);*/
        static void HandleArguments(const std::vector<std::string> &args);
};