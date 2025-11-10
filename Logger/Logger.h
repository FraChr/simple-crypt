#pragma once
#include <ctime>
#include <string>

#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"


class IFileHandler;

class Logger : public ILogger {
    public:
        Logger(IFileHandler& filehandler);
        void log(LogLevel level, const std::string &message) override;
    private:
        static std::string getCurrentFormatedTime();
        void createDirectory() const;

        static std::string levelToString(const LogLevel &level);
        std::string _logfileName = "Log.txt";
        std::string _logDirectory = "LogData";
        IFileHandler& _fileHandler;

};
