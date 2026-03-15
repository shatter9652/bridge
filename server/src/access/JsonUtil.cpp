// LCEServer — JsonUtil implementation
// Minimal JSON parser for our simple array-of-objects format
#include "JsonUtil.h"
#include "../core/Logger.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

namespace LCEServer
{
namespace JsonUtil
{
    std::string Trim(const std::string& s)
    {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        return s.substr(a, s.find_last_not_of(" \t\r\n") - a + 1);
    }

    std::string ToLower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    std::string Escape(const std::string& s)
    {
        std::string out;
        out.reserve(s.size() + 8);
        for (char c : s)
        {
            switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:   out += c; break;
            }
        }
        return out;
    }

    std::string GetUtcTimestamp()
    {
        SYSTEMTIME utc;
        GetSystemTime(&utc);
        char buf[64];
        sprintf_s(buf, sizeof(buf),
            "%04u-%02u-%02uT%02u:%02u:%02uZ",
            (unsigned)utc.wYear, (unsigned)utc.wMonth,
            (unsigned)utc.wDay, (unsigned)utc.wHour,
            (unsigned)utc.wMinute, (unsigned)utc.wSecond);
        return buf;
    }

    // --- Minimal JSON parser ---
    // Handles: [ { "key": "value", ... }, ... ]
    // Only supports string values (sufficient for our access files)

    // Skip whitespace
    static size_t SkipWs(const std::string& s, size_t pos)
    {
        while (pos < s.size() && (s[pos]==' '||s[pos]=='\t'||
               s[pos]=='\r'||s[pos]=='\n'))
            pos++;
        return pos;
    }

    // Parse a JSON string (expects pos at opening quote)
    static bool ParseString(const std::string& s, size_t& pos,
                            std::string& out)
    {
        if (pos >= s.size() || s[pos] != '"') return false;
        pos++; // skip opening quote
        out.clear();
        while (pos < s.size())
        {
            char c = s[pos++];
            if (c == '"') return true;
            if (c == '\\' && pos < s.size())
            {
                char esc = s[pos++];
                switch (esc) {
                case '"':  out += '"'; break;
                case '\\': out += '\\'; break;
                case 'n':  out += '\n'; break;
                case 'r':  out += '\r'; break;
                case 't':  out += '\t'; break;
                case '/':  out += '/'; break;
                default:   out += esc; break;
                }
            }
            else
            {
                out += c;
            }
        }
        return false; // unterminated string
    }

    // Parse a JSON object (expects pos at '{')
    static bool ParseObject(const std::string& s, size_t& pos,
                            JsonObject& out)
    {
        if (pos >= s.size() || s[pos] != '{') return false;
        pos++; // skip '{'
        out.clear();

        while (true)
        {
            pos = SkipWs(s, pos);
            if (pos >= s.size()) return false;
            if (s[pos] == '}') { pos++; return true; }

            // Parse key
            std::string key;
            if (!ParseString(s, pos, key)) return false;

            pos = SkipWs(s, pos);
            if (pos >= s.size() || s[pos] != ':') return false;
            pos++; // skip ':'
            pos = SkipWs(s, pos);

            // Parse value — we handle strings and skip others
            std::string value;
            if (pos < s.size() && s[pos] == '"')
            {
                if (!ParseString(s, pos, value)) return false;
            }
            else
            {
                // Non-string value: read until , or }
                size_t start = pos;
                while (pos < s.size() && s[pos]!=',' && s[pos]!='}')
                    pos++;
                value = Trim(s.substr(start, pos - start));
            }

            out[key] = value;

            pos = SkipWs(s, pos);
            if (pos < s.size() && s[pos] == ',')
                pos++; // skip comma
        }
    }

    bool LoadJsonArray(const std::string& path,
                       std::vector<JsonObject>& out)
    {
        out.clear();

        // Read file
        std::ifstream f(path, std::ios::binary);
        if (!f.is_open())
        {
            // Create empty file
            std::ofstream create(path);
            if (create.is_open())
            {
                create << "[]\n";
                create.close();
            }
            return true; // empty list is valid
        }

        std::ostringstream ss;
        ss << f.rdbuf();
        std::string text = ss.str();
        f.close();

        if (text.empty()) text = "[]";

        // Strip UTF-8 BOM
        if (text.size() >= 3 &&
            (uint8_t)text[0] == 0xEF &&
            (uint8_t)text[1] == 0xBB &&
            (uint8_t)text[2] == 0xBF)
            text = text.substr(3);

        // Find array start
        size_t pos = SkipWs(text, 0);
        if (pos >= text.size() || text[pos] != '[')
        {
            Logger::Error("JsonUtil", "Expected '[' in %s",
                          path.c_str());
            return false;
        }
        pos++; // skip '['

        while (true)
        {
            pos = SkipWs(text, pos);
            if (pos >= text.size()) break;
            if (text[pos] == ']') break;

            JsonObject obj;
            if (!ParseObject(text, pos, obj))
            {
                Logger::Error("JsonUtil",
                    "Failed to parse object in %s", path.c_str());
                return false;
            }
            out.push_back(obj);

            pos = SkipWs(text, pos);
            if (pos < text.size() && text[pos] == ',')
                pos++;
        }
        return true;
    }

    bool SaveJsonArray(const std::string& path,
                       const std::vector<JsonObject>& items,
                       const std::vector<std::string>& keyOrder)
    {
        std::ostringstream ss;
        if (items.empty())
        {
            ss << "[]\n";
        }
        else
        {
            ss << "[\n";
            for (size_t i = 0; i < items.size(); i++)
            {
                ss << "  {\n";
                const auto& obj = items[i];
                bool first = true;

                // Write keys in specified order
                for (const auto& key : keyOrder)
                {
                    auto it = obj.find(key);
                    if (it == obj.end()) continue;
                    if (!first) ss << ",\n";
                    ss << "    \"" << Escape(key) << "\": \""
                       << Escape(it->second) << "\"";
                    first = false;
                }
                ss << "\n  }";
                if (i + 1 < items.size()) ss << ",";
                ss << "\n";
            }
            ss << "]\n";
        }

        // Write atomically
        std::string tmp = path + ".tmp";
        {
            std::ofstream f(tmp, std::ios::binary);
            if (!f.is_open()) return false;
            f << ss.str();
            f.close();
            if (f.fail()) return false;
        }
        std::remove(path.c_str());
        return std::rename(tmp.c_str(), path.c_str()) == 0;
    }

} // namespace JsonUtil
} // namespace LCEServer
