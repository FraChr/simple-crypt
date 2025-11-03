#include "FileHandler.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../Data/UI/ErrorText.h"

FileHandler::FileHandler(const std::string &fileName) : _fileName(fileName)
{
}

void FileHandler::writeToFile(const std::string &value) {
    std::ofstream outfile(_fileName);
    outfile << value;

}

bool FileHandler::fileExists() const {
    return std::filesystem::exists(_fileName);
}


