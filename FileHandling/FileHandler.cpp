#include "FileHandler.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>



void FileHandler::writeToFile(const std::string& filename, const std::vector<unsigned char> &value) {
    std::ofstream file(filename, std::ofstream::binary);
    if (!file.is_open()) {
        std::cerr << "Can't open file\n";
        return;
    }

    const std::vector <char> buffer(value.begin(), value.end());
    file.write(buffer.data(), buffer.size());
}

bool FileHandler::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}


int loadingScreen(std::size_t totalSize, int progress, int lastPrecent);

std::vector<unsigned char> FileHandler::readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Can't open file\n";
        return std::vector<unsigned char>();
    }

    std::vector<unsigned char> buffer{
    std::istreambuf_iterator(file),
    std::istreambuf_iterator<char>()
    };

    return buffer;
}


