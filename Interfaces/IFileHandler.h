#pragma once
#include <string>

class IFileHandler {
    public:
        virtual ~IFileHandler() = default;
        virtual void writeToFile(const std::string& filename, const std::string& value) = 0;
        virtual bool fileExists(const std::string& filename) = 0;
        virtual std::string readFromFile(const std::string& filename) = 0;
};
