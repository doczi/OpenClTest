#ifndef CLINFO_H
#define CLINFO_H

#include <cstdint>
#include <string>
#include <map>
#include <vector>



class ClValue
{
public:
    enum class Type {
        BOOLEAN,
        NUMBER,
        TEXT,
        SIZE_ARRAY,

        FP_CONFIG,
        DEVICE_EXEC_CAPABILITIES,
        DEVICE_MEM_CACHE_TYPE,
        DEVICE_LOCAL_MEM_TYPE,
        COMMAND_QUEUE_PROPERTIES,
        DEVICE_TYPE,
    };

    Type type;
    uint64_t number;
    std::string text;
    std::vector<size_t> sizeArray;

    ClValue(bool boolean);
    ClValue(uint32_t number);
    ClValue(uint64_t number, Type type = Type::NUMBER);
    ClValue(const std::string& text);
    ClValue(const std::vector<size_t> sizeArray);
    std::string toString() const;
private:
    static std::string formatNumber(uint64_t number);
    static std::string formatSizeArray(const std::vector<size_t> array);
    static std::string formatBitField(
            uint64_t number,
            const std::vector<std::string>& fieldNames);
};



class ClDeviceInfo
{
public:
    std::map<std::string, ClValue> fields;
};



class ClPlatformInfo
{
public:
    std::map<std::string, ClValue> fields;
    std::vector<ClDeviceInfo> devices;
};



class ClInfo
{
public:
    std::vector<ClPlatformInfo> platforms;
};



#endif // CLINFO_H
