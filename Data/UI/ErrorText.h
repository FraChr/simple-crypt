#pragma once
#include <string>

struct FileError {
    static constexpr std::string_view FileExist = "File exists";
    static constexpr std::string_view FileNotFoundOrExist = "File not found or dont exist";
    static constexpr std::string_view FileNameNotFound = "Name not found";
};

struct EncryptDecrypError {
    static constexpr std::string_view encryptionFailure = "Encryption failed\n";
    static constexpr std::string_view decryptionFailure = "Decryption failed\n";
    static constexpr std::string_view notValidOrCorrupt = "Not a walid file or file is Corrupt\n";
};

struct CommandError {
    static constexpr std::string_view CommandNotFound = "Command not found\n";
    static constexpr std::string_view commandMissingArg = "Command Missing argument\n";
    static constexpr std::string_view unknownCommand = "Unknown Command.\nAvailable commands:\n";


};