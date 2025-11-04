#pragma once
#include <string>

class FileHandler {
    public:
        explicit FileHandler(const std::string &fileName);
        /*void readFile();*/
        void writeToFile(const std::string &value);
        bool fileExists() const;
        std::string readFromFile();




    private:

        std::string _fileName;
};
