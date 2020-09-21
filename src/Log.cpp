#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <Log.h>

std::ostream &Log::stream()
{
    return std::cout;
}

std::string Log::header(const LogLevel &level)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&time), "%Y-%d-%m %X") << "]" << " ";

    ss << "[";

    switch (level) {
        case LogLevel::Error:
            ss << "ERROR";
        break;
        case LogLevel::Info:
            ss << "INFO";
        break;
        case LogLevel::Debug:
            ss << "DEBUG";
        break;
        case LogLevel::Warning:
            ss << "WARNING";
        break;
    }

    ss << "] ";

    return ss.str();
}