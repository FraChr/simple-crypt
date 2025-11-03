#include "Commands.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../FileHandling/FileHandler.h"
#include "../POD/File.h"
#include <openssl/evp.h>
#include <openssl/sha.h>



void hashAndStorePassword(const FileInfo& file);
void crypt(FileInfo& file);
std::string hash(const FileInfo& file);


std::map<std::string, CommandFunc> Commands::commands = {
    {"crypt", crypt},
    {"hash", hashAndStorePassword}
};

void hashAndStorePassword(const FileInfo& file) {
    const std::string hexHash = hash(file);
    FileHandler tofile(file.fileName);
    tofile.writeToFile(hexHash);
}

void crypt(FileInfo& file) {
    /*file.passwordHashed = hexHash.str();*/

    /*FileHandler tofile(file.fileName);

     tofile.writeToFile(hexHash.str());*/
}

std::string hash(const FileInfo& file) {
    unsigned char hashLength [SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(file.password.c_str()), file.password.size(), hashLength);

    std::ostringstream hexHash;
    for (const auto i : hashLength) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return hexHash.str();
}