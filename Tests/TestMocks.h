#pragma once
#include <iostream>
#include <string>

#include "../Cryptography/CryptographyServices/EncryptionService/EncryptionService.h"
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"
#include "../POD/UserInput.h"

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
        return {};
    };
};

class MockLogger final : public ILogger {
public:
    const std::string RESET = "\033[0m";
    const std::string CYAN = "\033[96m";

    void log(LogLevel level, const std::string &message) {
        std::cout << CYAN << "\nMock Logger: " << message << RESET << '\n';
    }
};

struct MockUserInput : userInput {
    std::string filename = "testData.txt";
    std::string password = "test";
};
