#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <debug.h>

#if (ENG_DEBUG)

#define LOG_ERROR(M) Log::stream() << Log::header(LogLevel::Error) << M << std::endl;
#define LOG_INFO(M) Log::stream() << Log::header(LogLevel::Info) << M << std::endl;
#ifdef ENABLE_DEBUG_MACRO
#define LOG_DEBUG(M) Log::stream() << Log::header(LogLevel::Debug) << M << std::endl;
#else
#define LOG_DEBUG(M)
#endif
#define LOG_WARNING(M) Log::stream() << Log::header(LogLevel::Warning) << M << std::endl;

#else

#define LOG_ERROR(M)
#define LOG_INFO(M) 
#define LOG_DEBUG(M)
#define LOG_WARNING(M)

#endif

enum class LogLevel
{
    Debug,
    Info,
    Error,
    Warning
};

class Log
{
public:
    static std::ostream &stream();
    static std::string header(const LogLevel &level);
};

#endif