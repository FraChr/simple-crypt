#pragma once
#include <string>
#include <vector>

class IFileHandler {
public:
    virtual ~IFileHandler() = default;

    virtual void writeToFile(const std::string &filename, const std::vector<unsigned char> &value) = 0;

    virtual void writeToFile(const std::string &filename, const std::string &value) = 0;

    virtual bool fileExists(const std::string &filename) = 0;

    virtual std::vector<unsigned char> readFromFile(const std::string &filename) = 0;
};