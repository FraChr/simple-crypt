#include "FileHandler.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "../Data/UI/ErrorText.h"
#include "../Render/RenderCmd.h"

void FileHandler::writeToFile(const std::string &filename, const std::vector<unsigned char> &value) {
    std::ofstream file(filename, std::ofstream::binary);
    if(fileIsOpenCheck(file)) return;
    /*if (!file.is_open()) {
        RenderCmd::WriteError(FileError::FileNotOpen);
        return;
    }*/

    auto totalFileSize = static_cast<std::streamsize>(value.size());
    char fileChunk[4096];
    std::streamsize totalWritten = 0;
    unsigned int percentWritten = 0;
    while (totalWritten < totalFileSize) {

        std::streamsize remaining = totalFileSize - totalWritten;
        std::streamsize chunkSize = std::min(remaining, static_cast<std::streamsize>(sizeof(fileChunk)));
        std::copy_n(value.begin() + totalWritten, chunkSize, fileChunk);
        file.write(fileChunk, chunkSize);
        totalWritten += chunkSize;

        percentWritten = (totalWritten * 100) / totalFileSize;
        std::string msg = "\rWriting: " + std::to_string(percentWritten) + '%';
        RenderCmd::WriteOut(msg);
    }


    /*const std::vector <char> buffer(value.begin(), value.end());

    file.write(buffer.data(), buffer.size());*/
}
/*template <typename T> void FileHandler::fileIsOpenCheck(const T &file) {
    if (!file.is_open()) {
        RenderCmd::WriteError(FileError::FileNotOpen);
    }
}*/
template <typename T> bool FileHandler::fileIsOpenCheck(const T &file) {
    if (!file.is_open()) {
        RenderCmd::WriteError(FileError::FileNotOpen);
        return true;
    }
    return false;
}

void FileHandler::writeToFile(const std::string &filename, const std::string &value) {
    std::ofstream file(filename,std::ofstream::app);
    if (!file.is_open()) {
        RenderCmd::WriteError(FileError::FileNotOpen);
        return;
    }
    file.write(value.c_str(), value.length());
}

bool FileHandler::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}




std::vector<unsigned char> FileHandler::readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if(fileIsOpenCheck(file)) return{};
    /*if (!file.is_open()) {
        RenderCmd::WriteError(FileError::FileNotOpen);
        return {};
    }*/

    auto start = std::chrono::high_resolution_clock::now();

    // Non buffered read time on 10gb .txt file 409.665 seconds
    // pre mem allocated vector with Buffered read time on 10gb .txt file 158.031 seconds
    // Buffered read time on 10gb .txt file
    // Difference = 251.634 seconds

    file.seekg(0, std::ios::end);
    size_t totalFileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> totalFile(totalFileSize);
    /*std::vector<unsigned char> totalFile;*/

    char fileChunk[4096];

    std::streamsize totalRead = 0;
    unsigned int percentRead = 0;

    while (totalRead < totalFileSize) {
        file.read(fileChunk, sizeof(fileChunk));

        std::streamsize currentRead = file.gcount();

        /*std::copy(fileChunk, fileChunk + currentRead,totalFile.begin() + totalRead);*/
        std::copy_n(fileChunk, currentRead, totalFile.begin() + totalRead);

        totalRead += currentRead;

        percentRead = (totalRead * 100) / totalFileSize;
        std::string msg = "\rReading: " + std::to_string(percentRead) + '%';
        RenderCmd::WriteOut(msg);

    }



    /*std::vector<unsigned char> buffer{
    std::istreambuf_iterator(file),
    std::istreambuf_iterator<char>()
    };*/
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "\nelapsed time: " << elapsed_seconds.count() << " seconds\n";
    return totalFile;


    /*return buffer;*/

}
