#ifndef JSONCLINFOSERIALIZER_H
#define JSONCLINFOSERIALIZER_H

#include "clinfoserializer.h"
#include <rapidjson/document.h>



class JsonClInfoSerializer: public ClInfoSerializer
{
public:
    std::string serialize(const ClInfo& info) const override;
private:
    void setJsonValue(
            rapidjson::Value& jsonValue,
            rapidjson::MemoryPoolAllocator<>& allocator,
            const ClValue& clValue) const;
};



#endif // JSONCLINFOSERIALIZER_H
