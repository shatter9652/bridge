// LCEServer — Logger matching ServerLogger.h design
#pragma once

#include "Types.h"

namespace LCEServer
{
    enum class LogLevel
    {
        Debug = 0,
        Info  = 1,
        Warn  = 2,
        Error = 3
    };

    class Logger
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void SetLevel(LogLevel level);
        static LogLevel GetLevel();

        static void Debug(const char* category, const char* fmt, ...);
        static void Info(const char* category, const char* fmt, ...);
        static void Warn(const char* category, const char* fmt, ...);
        static void Error(const char* category, const char* fmt, ...);

    private:
        static void Log(LogLevel level, const char* category, const char* fmt, va_list args);
        static const char* LevelToString(LogLevel level);
        static const char* LevelToColor(LogLevel level);
        static void RotateLatestLog();

        static LogLevel s_level;
        static std::mutex s_mutex;
        static FILE* s_logFile;
    };
}
