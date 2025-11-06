#include "FileHandler.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>


void FileHandler::writeToFile(const std::string& filename, const std::vector<char> &value) {
    std::ofstream file(filename, std::ofstream::binary);
    if (!file.is_open()) {
        std::cerr << "Can't open file\n";
        return;
    }

    file.write(value.data(), value.size());
}

bool FileHandler::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

std::vector<char> FileHandler::readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Can't open file\n";
        return std::vector<char>();
    }

    std::vector<char> buffer{
    std::istreambuf_iterator<char>(file),
    std::istreambuf_iterator<char>()
    };
    return buffer;
}


