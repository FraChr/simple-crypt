#pragma once
#include <string>
#include <vector>

#include "../Interfaces/IFileHandler.h"

class FileHandler : public IFileHandler {
    public:
        /*void readFile();*/
        void writeToFile(const std::string& filename, const std::vector<unsigned char> &value) override;
        bool fileExists(const std::string& filename) override;
        std::vector<unsigned char> readFromFile(const std::string& filename) override;
};
