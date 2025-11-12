#pragma once
#include "../commands/CommandTypes.h"

class ICommands {
public:
    virtual ~ICommands() = default;

    virtual void executeCommand(CommandType type, FileInfo &file) = 0;
};