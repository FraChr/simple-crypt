#include "Commands.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../FileHandling/FileHandler.h"
#include "../POD/File.h"
#include <openssl/evp.h>
#include <openssl/sha.h>



/*
void hashAndStorePassword(FileInfo& file);
void crypt(FileInfo& file);
std::string hash(std::string password);
*/


Commands::Commands() {
    commands[HASH] = [this](FileInfo& file){hashAndStorePassword(file);};
    commands[CRYPT] = [this](FileInfo& file){crypt(file);};
}

bool Commands::validPassword(const FileInfo &file) {
    std::string passwordFile = ".secrets";
    FileHandler f(passwordFile);
    auto hashedPass = hash(file.password);
    std::string original = f.readFromFile();
    if (hashedPass == original) {
        return true;
    }
    return false;
}

/*std::map<CommandType, CommandFunc> commands = {
    {HASH, hashAndStorePassword},
    {CRYPT, crypt}
};*/

void Commands::hashAndStorePassword(FileInfo& file) {
    file.fileName = ".secrets";
    std::cout << "password entered is " << file.password << std::endl;
    const std::string hexHash = hash(file.password);
    FileHandler tofile(file.fileName);
    tofile.writeToFile(hexHash);
}

void Commands::crypt(FileInfo& file) {
    FileHandler f(file.fileName);
    bool validateKey = validPassword(file);
    if (f.fileExists() && validateKey) {
        std::cout << "crypting file..." << std::endl;   
    }else {
        std::cerr << "file not exist\n";
    }

    /*file.passwordHashed = hexHash.str();*/

    /*FileHandler tofile(file.fileName);

     tofile.writeToFile(hexHash.str());*/
}



std::string Commands::hash(std::string password) {
    unsigned char hashLength [SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hashLength);

    std::ostringstream hexHash;
    for (const auto i : hashLength) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return hexHash.str();
}


