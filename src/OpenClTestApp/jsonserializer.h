#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "serializer.h"

#include <rapidjson/document.h>



class ClParameter;



/**
 * Serializes a ClInfo object into JSON format.
 */
class JsonSerializer: public Serializer
{
public:
    std::string serialize(const ClInfo& info) const override;
private:
    void setJsonValueToPlatform(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClPlatformInfo& platformInfo) const;
    void setJsonValueToDevice(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClDeviceInfo& deviceInfo) const;
    void setJsonValueToParameter(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClParameter& parameter) const;
};



#endif // JSONSERIALIZER_H
