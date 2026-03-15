// LCEServer — Minimal JSON utilities for access control files
// Handles our simple JSON arrays of string-keyed objects.
// No external dependency (no nlohmann/json).
#pragma once

#include "../core/Types.h"
#include <map>

namespace LCEServer
{
namespace JsonUtil
{
    using JsonObject = std::map<std::string, std::string>;

    std::string Trim(const std::string& s);
    std::string ToLower(std::string s);
    std::string Escape(const std::string& s);
    std::string GetUtcTimestamp();

    // Load a JSON array of objects from file.
    // Returns empty vector if file doesn't exist
    // (creates the file with "[]").
    bool LoadJsonArray(const std::string& path,
                       std::vector<JsonObject>& out);

    // Save a JSON array of objects to file (atomic).
    // keyOrder controls field output order.
    bool SaveJsonArray(const std::string& path,
                       const std::vector<JsonObject>& items,
                       const std::vector<std::string>& keyOrder);

} // namespace JsonUtil
} // namespace LCEServer
