#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "serializer.h"

#include <rapidjson/document.h>



class ClValue;



class JsonSerializer: public Serializer
{
public:
    std::string serialize(const ClInfo& info) const override;
private:
    void setJsonValue(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClValue& clValue) const;
};



#endif // JSONSERIALIZER_H
