#include "FileHandler.h"

#include <filesystem>
#include <fstream>
#include <iostream>


void FileHandler::writeToFile(const std::string& filename, const std::string &value) {
    std::ofstream outfile(filename);
    outfile << value;
}

bool FileHandler::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

std::string FileHandler::readFromFile(const std::string& filename) {
    if (!fileExists(filename))
        std::cerr << "File does not exist\n";

    std::string result;
    std::ifstream file(filename);
    std::ostringstream oss;
    oss << file.rdbuf();
    result = oss.str();
    /*while (std::getline(file, result)) {
        result +=
    }*/
    /*std::getline(file, result);*/
    return result;
}


