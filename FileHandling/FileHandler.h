#pragma once
#include <string>

#include "../Interfaces/IFileHandler.h"

class FileHandler : public IFileHandler {
    public:
        /*void readFile();*/
        void writeToFile(const std::string& filename, const std::string &value) override;
        bool fileExists(const std::string& filename) override;
        std::string readFromFile(const std::string& filename) override;
};
