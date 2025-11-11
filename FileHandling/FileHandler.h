#pragma once
#include <string>
#include <vector>
#include "../Interfaces/IFileHandler.h"

class FileHandler : public IFileHandler {
    public:
        void writeToFile(const std::string& filename, const std::vector<unsigned char> &value) override;
        void writeToFile(const std::string& filename, const std::string &value) override;
        bool fileExists(const std::string& filename) override;
        std::vector<unsigned char> readFromFile(const std::string& filename) override;
    private:
        template <typename T> bool fileIsOpenCheck(const T &file);
        void progressPercent(std::streamsize totalProcessed, std::streamsize totalFileSize, std::string prompt);

};
