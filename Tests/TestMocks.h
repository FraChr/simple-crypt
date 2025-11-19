#pragma once
#include <iostream>
#include <string>
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"

class MockFileHandler final : public IFileHandler {
public:
    std::string writtenFile;
    std::string writtenData;

    void writeToFile(const std::string &file, const std::string &data) override {
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

class MockLogger final : public ILogger {
    public:
    void log(LogLevel level, const std::string &message) {
        std::cout << "Error Level: " << message << '\n';
    }
};
