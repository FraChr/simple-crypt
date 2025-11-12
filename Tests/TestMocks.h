#pragma once
#include <string>

#include "../Interfaces/IFileHandler.h"

class MockFileHandler : public IFileHandler {
public:
    std::string writtenFile;
    std::string writtenData;

    void writeToFile(const std::string &file, const std::string &data) {
        writtenFile = file;
        writtenData = data;
    }

    void writeToFile(const std::string &filename, const std::vector<unsigned char> &value) override {
        writtenFile = filename;
        writtenData = std::string(value.begin(), value.end());
    }
    bool fileExists(const std::string &filename) override {
        return true;
    }
    std::vector<unsigned char> readFromFile(const std::string &filename) override {
        return{};
    };
};
