#include "jsonclinfoserializer.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>



std::string JsonClInfoSerializer::serialize(const ClInfo& info) const
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::MemoryPoolAllocator<>& allocator = document.GetAllocator();

    for (const ClPlatformInfo& platformInfo: info.platforms) {
        rapidjson::Value platform;
        platform.SetObject();
        for (const auto& field: platformInfo.fields) {
            rapidjson::Value jsonValue;
            setJsonValue(jsonValue, allocator, field.second);
            platform.AddMember(field.first.c_str(), jsonValue, allocator);
        }

        rapidjson::Value devices;
        devices.SetArray();
        for (const ClDeviceInfo& deviceInfo: platformInfo.devices) {
            rapidjson::Value device;
            device.SetObject();
            for (const auto& field: deviceInfo.fields) {
                rapidjson::Value jsonValue;
                setJsonValue(jsonValue, allocator, field.second);
                device.AddMember(field.first.c_str(), jsonValue, allocator);
            }
            devices.PushBack(device, document.GetAllocator());
        }
        platform.AddMember("devices", devices, document.GetAllocator());
        document.PushBack(platform, document.GetAllocator());
    }

    rapidjson::StringBuffer stringBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);
    document.Accept(writer);
    return stringBuffer.GetString();
}



void JsonClInfoSerializer::setJsonValue(
        rapidjson::Value& jsonValue,
        rapidjson::MemoryPoolAllocator<>& allocator,
        const ClValue& clValue) const
{
    switch (clValue.type) {
    case ClValue::Type::BOOLEAN:
        jsonValue.SetBool(clValue.number);
        break;
    case ClValue::Type::NUMBER:
        jsonValue.SetUint64(clValue.number);
        break;
    case ClValue::Type::SIZE_ARRAY:
        jsonValue.SetArray();
        for (size_t size: clValue.sizeArray) {
            jsonValue.PushBack(size, allocator);
        }
        break;
    default:
        jsonValue.SetString(clValue.toString().c_str());
        break;
    }
}
