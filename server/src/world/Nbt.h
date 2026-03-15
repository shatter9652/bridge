// LCEServer — Standalone NBT (Named Binary Tag) implementation
// Matches the Java/LCE big-endian NBT format exactly
#pragma once

#include "../core/Types.h"
#include <variant>
#include <map>

namespace LCEServer
{
    enum class NbtTagType : uint8_t
    {
        End       = 0,
        Byte      = 1,
        Short     = 2,
        Int       = 3,
        Long      = 4,
        Float     = 5,
        Double    = 6,
        ByteArray = 7,
        String    = 8,
        List      = 9,
        Compound  = 10,
        IntArray   = 11,
        LongArray  = 12
    };

    class NbtTag;
    using NbtCompound = std::map<std::string, std::shared_ptr<NbtTag>>;
    using NbtList     = std::vector<std::shared_ptr<NbtTag>>;

    class NbtTag
    {
    public:
        NbtTagType type;

        // Payload — only one is active depending on type
        int8_t      byteVal   = 0;
        int16_t     shortVal  = 0;
        int32_t     intVal    = 0;
        int64_t     longVal   = 0;
        float       floatVal  = 0.0f;
        double      doubleVal = 0.0;
        std::string stringVal;
        std::vector<uint8_t> byteArrayVal;
        std::vector<int32_t> intArrayVal;
        std::vector<int64_t> longArrayVal;
        NbtList     listVal;
        NbtTagType  listType = NbtTagType::End;
        NbtCompound compoundVal;

        NbtTag() : type(NbtTagType::End) {}
        explicit NbtTag(NbtTagType t) : type(t) {}

        // Convenience constructors
        static std::shared_ptr<NbtTag> Byte(int8_t v);
        static std::shared_ptr<NbtTag> Short(int16_t v);
        static std::shared_ptr<NbtTag> Int(int32_t v);
        static std::shared_ptr<NbtTag> Long(int64_t v);
        static std::shared_ptr<NbtTag> Float(float v);
        static std::shared_ptr<NbtTag> Double(double v);
        static std::shared_ptr<NbtTag> String(const std::string& v);
        static std::shared_ptr<NbtTag> ByteArray(const std::vector<uint8_t>& v);
        static std::shared_ptr<NbtTag> IntArray(const std::vector<int32_t>& v);
        static std::shared_ptr<NbtTag> LongArray(const std::vector<int64_t>& v);
        static std::shared_ptr<NbtTag> List(NbtTagType elemType);
        static std::shared_ptr<NbtTag> Compound();

        // Compound helpers
        void set(const std::string& key, std::shared_ptr<NbtTag> val);
        std::shared_ptr<NbtTag> get(const std::string& key) const;
        bool has(const std::string& key) const;
        int32_t getInt(const std::string& key, int32_t def = 0) const;
        int64_t getLong(const std::string& key, int64_t def = 0) const;
        int8_t getByte(const std::string& key, int8_t def = 0) const;
        float getFloat(const std::string& key, float def = 0) const;
        double getDouble(const std::string& key, double def = 0) const;
        std::string getString(const std::string& key, const std::string& def = "") const;
    };

    // ---------------------------------------------------------------
    // NBT I/O — read/write from byte streams
    // ---------------------------------------------------------------
    class NbtIO
    {
    public:
        // Read a root compound tag from raw NBT bytes
        static std::shared_ptr<NbtTag> ReadFromBytes(
            const uint8_t* data, int size, std::string* outRootName = nullptr);

        // Write a root compound tag to raw NBT bytes
        static std::vector<uint8_t> WriteToBytes(
            const std::shared_ptr<NbtTag>& root,
            const std::string& rootName = "");

        // Read from gzip-compressed NBT (level.dat format)
        static std::shared_ptr<NbtTag> ReadGzipped(
            const uint8_t* data, int size, std::string* outRootName = nullptr);

        // Write to gzip-compressed NBT
        static std::vector<uint8_t> WriteGzipped(
            const std::shared_ptr<NbtTag>& root,
            const std::string& rootName = "");

        // Read from a file (auto-detects gzip)
        static std::shared_ptr<NbtTag> ReadFromFile(
            const std::string& path, std::string* outRootName = nullptr);

        // Write gzipped NBT to a file
        static bool WriteToFile(
            const std::string& path,
            const std::shared_ptr<NbtTag>& root,
            const std::string& rootName = "");
    };
}
