#pragma once
enum class LogLevel {
    ERROR,
    WARNING,
    INFO,
};

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(LogLevel level, const std::string &message) = 0;
};