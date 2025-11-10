#pragma once
#include <string>
#include <vector>

#include "../Interfaces/IFileHandler.h"

class FileHandler : public IFileHandler {
    public:
        void writeToFile(const std::string& filename, const std::vector<unsigned char> &value) override;
        void writeToFile(const std::string& filename, const std::string &value) override;
        bool fileExists(const std::string& filename) override;
        /*template <typename T> void fileIsOpenCheck(const T &file);*/
        template <typename T> bool fileIsOpenCheck(const T &file);
        std::vector<unsigned char> readFromFile(const std::string& filename) override;
};
