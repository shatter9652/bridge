// LCEServer — NBT implementation
#include "Nbt.h"
#include "../core/Logger.h"
#include <zlib.h>
#include <fstream>
#include <cstring>

namespace LCEServer
{
    // --- Convenience constructors ---
    std::shared_ptr<NbtTag> NbtTag::Byte(int8_t v)   { auto t = std::make_shared<NbtTag>(NbtTagType::Byte); t->byteVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::Short(int16_t v)  { auto t = std::make_shared<NbtTag>(NbtTagType::Short); t->shortVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::Int(int32_t v)    { auto t = std::make_shared<NbtTag>(NbtTagType::Int); t->intVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::Long(int64_t v)   { auto t = std::make_shared<NbtTag>(NbtTagType::Long); t->longVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::Float(float v)    { auto t = std::make_shared<NbtTag>(NbtTagType::Float); t->floatVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::Double(double v)  { auto t = std::make_shared<NbtTag>(NbtTagType::Double); t->doubleVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::String(const std::string& v) { auto t = std::make_shared<NbtTag>(NbtTagType::String); t->stringVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::ByteArray(const std::vector<uint8_t>& v) { auto t = std::make_shared<NbtTag>(NbtTagType::ByteArray); t->byteArrayVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::IntArray(const std::vector<int32_t>& v) { auto t = std::make_shared<NbtTag>(NbtTagType::IntArray); t->intArrayVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::LongArray(const std::vector<int64_t>& v) { auto t = std::make_shared<NbtTag>(NbtTagType::LongArray); t->longArrayVal = v; return t; }
    std::shared_ptr<NbtTag> NbtTag::List(NbtTagType elemType) { auto t = std::make_shared<NbtTag>(NbtTagType::List); t->listType = elemType; return t; }
    std::shared_ptr<NbtTag> NbtTag::Compound() { return std::make_shared<NbtTag>(NbtTagType::Compound); }

    void NbtTag::set(const std::string& key, std::shared_ptr<NbtTag> val) { compoundVal[key] = val; }
    std::shared_ptr<NbtTag> NbtTag::get(const std::string& key) const {
        auto it = compoundVal.find(key);
        return (it != compoundVal.end()) ? it->second : nullptr;
    }
    bool NbtTag::has(const std::string& key) const { return compoundVal.count(key) > 0; }
    int32_t NbtTag::getInt(const std::string& key, int32_t def) const { auto t = get(key); return (t && t->type == NbtTagType::Int) ? t->intVal : def; }
    int64_t NbtTag::getLong(const std::string& key, int64_t def) const { auto t = get(key); return (t && t->type == NbtTagType::Long) ? t->longVal : def; }
    int8_t NbtTag::getByte(const std::string& key, int8_t def) const { auto t = get(key); return (t && t->type == NbtTagType::Byte) ? t->byteVal : def; }
    float NbtTag::getFloat(const std::string& key, float def) const { auto t = get(key); return (t && t->type == NbtTagType::Float) ? t->floatVal : def; }
    double NbtTag::getDouble(const std::string& key, double def) const { auto t = get(key); return (t && t->type == NbtTagType::Double) ? t->doubleVal : def; }
    std::string NbtTag::getString(const std::string& key, const std::string& def) const { auto t = get(key); return (t && t->type == NbtTagType::String) ? t->stringVal : def; }

    // --- Binary stream reader for NBT ---
    class NbtReader
    {
    public:
        NbtReader(const uint8_t* d, int s) : data(d), size(s), pos(0) {}
        bool ok() const { return pos <= size; }
        int remaining() const { return size - pos; }

        uint8_t readByte() { return (pos < size) ? data[pos++] : 0; }
        int16_t readShort() {
            uint8_t a = readByte(), b = readByte();
            return (int16_t)((a << 8) | b);
        }
        int32_t readInt() {
            uint8_t a=readByte(),b=readByte(),c=readByte(),d=readByte();
            return (int32_t)((a<<24)|(b<<16)|(c<<8)|d);
        }
        int64_t readLong() {
            int32_t hi = readInt(), lo = readInt();
            return ((int64_t)hi << 32) | ((int64_t)(uint32_t)lo);
        }
        float readFloat() {
            int32_t v = readInt(); float f; memcpy(&f,&v,4); return f;
        }
        double readDouble() {
            int64_t v = readLong(); double d; memcpy(&d,&v,8); return d;
        }
        std::string readString() {
            int16_t len = readShort();
            if (len <= 0 || pos + len > size) return "";
            std::string s((const char*)&data[pos], len);
            pos += len;
            return s;
        }

        std::shared_ptr<NbtTag> readTag(NbtTagType type) {
            auto tag = std::make_shared<NbtTag>(type);
            switch (type) {
            case NbtTagType::Byte:   tag->byteVal = (int8_t)readByte(); break;
            case NbtTagType::Short:  tag->shortVal = readShort(); break;
            case NbtTagType::Int:    tag->intVal = readInt(); break;
            case NbtTagType::Long:   tag->longVal = readLong(); break;
            case NbtTagType::Float:  tag->floatVal = readFloat(); break;
            case NbtTagType::Double: tag->doubleVal = readDouble(); break;
            case NbtTagType::String: tag->stringVal = readString(); break;
            case NbtTagType::ByteArray: {
                int32_t len = readInt();
                if (len > 0 && pos + len <= size) {
                    tag->byteArrayVal.assign(&data[pos], &data[pos+len]);
                    pos += len;
                }
            } break;
            case NbtTagType::IntArray: {
                int32_t len = readInt();
                tag->intArrayVal.resize(len > 0 ? len : 0);
                for (int32_t i = 0; i < len; i++)
                    tag->intArrayVal[i] = readInt();
            } break;
            case NbtTagType::LongArray: {
                int32_t len = readInt();
                tag->longArrayVal.resize(len > 0 ? len : 0);
                for (int32_t i = 0; i < len; i++)
                    tag->longArrayVal[i] = readLong();
            } break;
            case NbtTagType::List: {
                tag->listType = (NbtTagType)readByte();
                int32_t len = readInt();
                for (int32_t i = 0; i < len; i++)
                    tag->listVal.push_back(readTag(tag->listType));
            } break;
            case NbtTagType::Compound: {
                while (ok()) {
                    uint8_t childType = readByte();
                    if (childType == 0) break; // TAG_End
                    std::string name = readString();
                    tag->compoundVal[name] = readTag((NbtTagType)childType);
                }
            } break;
            default: break;
            }
            return tag;
        }
    private:
        const uint8_t* data;
        int size, pos;
    };

    // --- Binary stream writer for NBT ---
    class NbtWriter
    {
    public:
        void writeByte(uint8_t v) { buf.push_back(v); }
        void writeShort(int16_t v) { writeByte((v>>8)&0xFF); writeByte(v&0xFF); }
        void writeInt(int32_t v) { writeByte((v>>24)&0xFF); writeByte((v>>16)&0xFF); writeByte((v>>8)&0xFF); writeByte(v&0xFF); }
        void writeLong(int64_t v) { writeInt((int32_t)(v>>32)); writeInt((int32_t)(v&0xFFFFFFFF)); }
        void writeFloat(float f) { int32_t v; memcpy(&v,&f,4); writeInt(v); }
        void writeDouble(double d) { int64_t v; memcpy(&v,&d,8); writeLong(v); }
        void writeString(const std::string& s) {
            writeShort((int16_t)s.size());
            buf.insert(buf.end(), s.begin(), s.end());
        }

        void writeTag(const std::shared_ptr<NbtTag>& tag) {
            switch (tag->type) {
            case NbtTagType::Byte:   writeByte((uint8_t)tag->byteVal); break;
            case NbtTagType::Short:  writeShort(tag->shortVal); break;
            case NbtTagType::Int:    writeInt(tag->intVal); break;
            case NbtTagType::Long:   writeLong(tag->longVal); break;
            case NbtTagType::Float:  writeFloat(tag->floatVal); break;
            case NbtTagType::Double: writeDouble(tag->doubleVal); break;
            case NbtTagType::String: writeString(tag->stringVal); break;
            case NbtTagType::ByteArray:
                writeInt((int32_t)tag->byteArrayVal.size());
                buf.insert(buf.end(), tag->byteArrayVal.begin(), tag->byteArrayVal.end());
                break;
            case NbtTagType::IntArray:
                writeInt((int32_t)tag->intArrayVal.size());
                for (auto v : tag->intArrayVal) writeInt(v);
                break;
            case NbtTagType::LongArray:
                writeInt((int32_t)tag->longArrayVal.size());
                for (auto v : tag->longArrayVal) writeLong(v);
                break;
            case NbtTagType::List:
                writeByte((uint8_t)tag->listType);
                writeInt((int32_t)tag->listVal.size());
                for (auto& child : tag->listVal) writeTag(child);
                break;
            case NbtTagType::Compound:
                for (auto& [name, child] : tag->compoundVal) {
                    writeByte((uint8_t)child->type);
                    writeString(name);
                    writeTag(child);
                }
                writeByte(0); // TAG_End
                break;
            default: break;
            }
        }

        const std::vector<uint8_t>& data() const { return buf; }
    private:
        std::vector<uint8_t> buf;
    };

    // --- NbtIO public methods ---

    std::shared_ptr<NbtTag> NbtIO::ReadFromBytes(
        const uint8_t* data, int size, std::string* outName)
    {
        NbtReader r(data, size);
        uint8_t rootType = r.readByte();
        if (rootType != (uint8_t)NbtTagType::Compound) return nullptr;
        std::string name = r.readString();
        if (outName) *outName = name;
        return r.readTag(NbtTagType::Compound);
    }

    std::vector<uint8_t> NbtIO::WriteToBytes(
        const std::shared_ptr<NbtTag>& root, const std::string& rootName)
    {
        NbtWriter w;
        w.writeByte((uint8_t)NbtTagType::Compound);
        w.writeString(rootName);
        w.writeTag(root);
        return w.data();
    }

    std::shared_ptr<NbtTag> NbtIO::ReadGzipped(
        const uint8_t* data, int size, std::string* outName)
    {
        // Decompress gzip
        std::vector<uint8_t> out(size * 4);
        z_stream strm = {};
        strm.next_in = (Bytef*)data;
        strm.avail_in = size;
        if (inflateInit2(&strm, 15 + 16) != Z_OK) return nullptr;
        std::vector<uint8_t> result;
        do {
            strm.next_out = out.data();
            strm.avail_out = (uInt)out.size();
            int ret = inflate(&strm, Z_NO_FLUSH);
            int have = (int)out.size() - strm.avail_out;
            result.insert(result.end(), out.begin(), out.begin()+have);
            if (ret == Z_STREAM_END) break;
            if (ret != Z_OK) { inflateEnd(&strm); return nullptr; }
        } while (strm.avail_in > 0);
        inflateEnd(&strm);
        return ReadFromBytes(result.data(), (int)result.size(), outName);
    }

    std::vector<uint8_t> NbtIO::WriteGzipped(
        const std::shared_ptr<NbtTag>& root, const std::string& rootName)
    {
        auto raw = WriteToBytes(root, rootName);
        // Gzip compress
        z_stream strm = {};
        if (deflateInit2(&strm, Z_DEFAULT_COMPRESSION,
            Z_DEFLATED, 15+16, 8, Z_DEFAULT_STRATEGY) != Z_OK)
            return {};
        std::vector<uint8_t> out(raw.size() + 256);
        strm.next_in = raw.data();
        strm.avail_in = (uInt)raw.size();
        strm.next_out = out.data();
        strm.avail_out = (uInt)out.size();
        deflate(&strm, Z_FINISH);
        out.resize(strm.total_out);
        deflateEnd(&strm);
        return out;
    }

    std::shared_ptr<NbtTag> NbtIO::ReadFromFile(
        const std::string& path, std::string* outName)
    {
        std::ifstream f(path, std::ios::binary);
        if (!f.is_open()) return nullptr;
        std::vector<uint8_t> data(
            (std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
        f.close();
        if (data.size() < 2) return nullptr;
        // Detect gzip: magic bytes 0x1F 0x8B
        if (data[0] == 0x1F && data[1] == 0x8B)
            return ReadGzipped(data.data(), (int)data.size(), outName);
        return ReadFromBytes(data.data(), (int)data.size(), outName);
    }

    bool NbtIO::WriteToFile(const std::string& path,
        const std::shared_ptr<NbtTag>& root, const std::string& rootName)
    {
        auto data = WriteGzipped(root, rootName);
        if (data.empty()) return false;
        std::ofstream f(path, std::ios::binary);
        if (!f.is_open()) return false;
        f.write((const char*)data.data(), data.size());
        return f.good();
    }

} // namespace LCEServer
