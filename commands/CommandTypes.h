#pragma once

#include <functional>

struct FileInfo;

using CommandFunc = std::function<void(FileInfo &)>;

enum CommandType {
    NONE,
    CRYPT,
    DECRYPT,
    HASH
};