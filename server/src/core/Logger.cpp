// LCEServer — Logger implementation
#include "Logger.h"
#include <cstdarg>
#include <ctime>
#include <cstdio>

namespace LCEServer
{
    LogLevel Logger::s_level = LogLevel::Info;
    std::mutex Logger::s_mutex;

    void Logger::SetLevel(LogLevel level) { s_level = level; }
    LogLevel Logger::GetLevel() { return s_level; }

    const char* Logger::LevelToString(LogLevel level)
    {
        switch (level) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Warn:  return "WARN";
            case LogLevel::Error: return "ERROR";
        }
        return "?";
    }

    const char* Logger::LevelToColor(LogLevel level)
    {
        switch (level) {
            case LogLevel::Debug: return "\033[90m";  // gray
            case LogLevel::Info:  return "\033[37m";   // white
            case LogLevel::Warn:  return "\033[33m";   // yellow
            case LogLevel::Error: return "\033[31m";   // red
        }
        return "\033[0m";
    }

    void Logger::Log(LogLevel level, const char* category, const char* fmt, va_list args)
    {
        if (level < s_level) return;

        // Timestamp
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        struct tm tm_buf;
        localtime_s(&tm_buf, &t);

        char timeStr[16];
        std::snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d",
            tm_buf.tm_hour, tm_buf.tm_min, tm_buf.tm_sec);

        // Format message
        char msgBuf[2048];
        std::vsnprintf(msgBuf, sizeof(msgBuf), fmt, args);

        std::lock_guard<std::mutex> lock(s_mutex);
        std::printf("%s[%s] [%s/%s]: %s\033[0m\n",
            LevelToColor(level), timeStr, category, LevelToString(level), msgBuf);
    }

    void Logger::Debug(const char* cat, const char* fmt, ...) { va_list a; va_start(a, fmt); Log(LogLevel::Debug, cat, fmt, a); va_end(a); }
    void Logger::Info(const char* cat, const char* fmt, ...)  { va_list a; va_start(a, fmt); Log(LogLevel::Info, cat, fmt, a); va_end(a); }
    void Logger::Warn(const char* cat, const char* fmt, ...)  { va_list a; va_start(a, fmt); Log(LogLevel::Warn, cat, fmt, a); va_end(a); }
    void Logger::Error(const char* cat, const char* fmt, ...) { va_list a; va_start(a, fmt); Log(LogLevel::Error, cat, fmt, a); va_end(a); }
}
