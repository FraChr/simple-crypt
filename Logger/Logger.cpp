#include "Logger.h"

#include <filesystem>
#include "../Data/UI/UiText.h"
#include "../FileHandling/FileHandler.h"
#include "../Render/RenderCmd.h"

Logger::Logger(IFileHandler &filehandler) : _fileHandler(filehandler) {
}

void Logger::log(const LogLevel level, const std::string &message) {
    if (!std::filesystem::exists(_logDirectory)) {
        createDirectory();
    }

    auto timestamp = getCurrentFormatedTime();
    std::ostringstream logEntery;
    logEntery << '[' << timestamp << ']' << levelToString(level) << ": " << message << '\n';

    /*RenderCmd::WriteOut(logEntery.str());*/

    _fileHandler.writeToFile(_logfileName, logEntery.str());
}

std::string Logger::getCurrentFormatedTime() {
    const time_t now = time(nullptr);
    const tm *timeInfo = localtime(&now);
    char timestamp[20];

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeInfo);
    return {timestamp};
}

void Logger::createDirectory() const {
    if (std::filesystem::exists(_logDirectory)) {
        RenderCmd::WriteOut(LoggerOutput::logDirectoryExist);
        return;
    }

    std::filesystem::create_directory(_logDirectory);
    RenderCmd::WriteOut(LoggerOutput::logDirectoryCreated);
    /*if(std::filesystem::create_directory(_logDirectory)) {
        RenderCmd::WriteOut(LoggerOutput::logDirectoryCreated);
    }
    else {
        RenderCmd::WriteOut(LoggerOutput::logDirectoryExist);
    }*/
}

std::string Logger::levelToString(const LogLevel &level) {
    switch (level) {
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::INFO:
            return "INFO";
        default: return "UNKNOWN";
    }
}