#pragma once

#include <functional>

struct userInput;

using CommandFunc = std::function<void(userInput &)>;

enum CommandType {
    NONE,
    CRYPT,
    DECRYPT,
    HASH,
    COMPRESS,
};