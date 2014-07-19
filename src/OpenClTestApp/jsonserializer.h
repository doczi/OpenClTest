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
    void setJsonValue(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClParameter& clValue) const;
};



#endif // JSONSERIALIZER_H
