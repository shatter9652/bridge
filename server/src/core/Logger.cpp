// LCEServer — Logger implementation
#include "Logger.h"
#include <cstdarg>
#include <ctime>
#include <cstdio>
#include <filesystem>
#include <zlib.h>

namespace LCEServer
{
    LogLevel Logger::s_level = LogLevel::Info;
    std::mutex Logger::s_mutex;
    FILE* Logger::s_logFile = nullptr;

    void Logger::Initialize()
    {
        std::lock_guard<std::mutex> lock(s_mutex);

        if (s_logFile)
            return;

        RotateLatestLog();

        std::error_code ec;
        std::filesystem::create_directories("logs", ec);
        s_logFile = std::fopen("logs/latest.log", "wb");
        if (!s_logFile)
        {
            std::printf("\033[33m[Logger/WARN]: Failed to open logs/latest.log\033[0m\n");
        }
    }

    void Logger::Shutdown()
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        if (s_logFile)
        {
            std::fflush(s_logFile);
            std::fclose(s_logFile);
            s_logFile = nullptr;
        }
    }

    void Logger::RotateLatestLog()
    {
        std::error_code ec;
        std::filesystem::create_directories("logs", ec);

        const std::filesystem::path latestPath("logs/latest.log");
        if (!std::filesystem::exists(latestPath, ec))
            return;

        if (std::filesystem::file_size(latestPath, ec) == 0)
        {
            std::filesystem::remove(latestPath, ec);
            return;
        }

        std::time_t t = std::time(nullptr);
        struct tm tm_buf;
        localtime_s(&tm_buf, &t);

        char archiveName[64];
        std::snprintf(archiveName, sizeof(archiveName),
            "logs/%04d-%02d-%02d-%02d-%02d-%02d.log.gz",
            tm_buf.tm_year + 1900,
            tm_buf.tm_mon + 1,
            tm_buf.tm_mday,
            tm_buf.tm_hour,
            tm_buf.tm_min,
            tm_buf.tm_sec);

        FILE* in = std::fopen(latestPath.string().c_str(), "rb");
        if (!in)
            return;

        gzFile out = gzopen(archiveName, "wb9");
        if (!out)
        {
            std::fclose(in);
            return;
        }

        char buffer[16384];
        bool ok = true;
        while (true)
        {
            size_t readCount = std::fread(buffer, 1, sizeof(buffer), in);
            if (readCount > 0)
            {
                int wrote = gzwrite(out, buffer, static_cast<unsigned int>(readCount));
                if (wrote == 0)
                {
                    ok = false;
                    break;
                }
            }

            if (readCount < sizeof(buffer))
            {
                if (std::ferror(in)) ok = false;
                break;
            }
        }

        std::fclose(in);
        gzclose(out);

        if (ok)
            std::filesystem::remove(latestPath, ec);
    }

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

        if (s_logFile)
        {
            std::fprintf(s_logFile, "[%s] [%s/%s]: %s\n",
                timeStr, category, LevelToString(level), msgBuf);
            std::fflush(s_logFile);
        }
    }

    void Logger::Debug(const char* cat, const char* fmt, ...) { va_list a; va_start(a, fmt); Log(LogLevel::Debug, cat, fmt, a); va_end(a); }
    void Logger::Info(const char* cat, const char* fmt, ...)  { va_list a; va_start(a, fmt); Log(LogLevel::Info, cat, fmt, a); va_end(a); }
    void Logger::Warn(const char* cat, const char* fmt, ...)  { va_list a; va_start(a, fmt); Log(LogLevel::Warn, cat, fmt, a); va_end(a); }
    void Logger::Error(const char* cat, const char* fmt, ...) { va_list a; va_start(a, fmt); Log(LogLevel::Error, cat, fmt, a); va_end(a); }
}
