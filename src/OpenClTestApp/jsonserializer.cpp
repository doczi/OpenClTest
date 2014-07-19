#include "jsonserializer.h"

#include "clinfo.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>



std::string JsonSerializer::serialize(const ClInfo& info) const
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::MemoryPoolAllocator<>& allocator = document.GetAllocator();

    for (const ClPlatformInfo& platformInfo: info.platforms) {
        rapidjson::Value platformValue;
        setJsonValueToPlatform(platformValue, allocator, platformInfo);
        document.PushBack(platformValue, document.GetAllocator());
    }

    rapidjson::StringBuffer stringBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);
    document.Accept(writer);
    return stringBuffer.GetString();
}



void JsonSerializer::setJsonValueToPlatform(
        rapidjson::Value& jsonValue,
        rapidjson::MemoryPoolAllocator<>& allocator,
        const ClPlatformInfo& platformInfo) const
{
    jsonValue.SetObject();
    for (const auto& parameter: platformInfo.parameters) {
        rapidjson::Value parameterValue;
        setJsonValueToParameter(parameterValue, allocator, parameter.second);
        jsonValue.AddMember(parameter.first.c_str(), parameterValue, allocator);
    }

    rapidjson::Value devices;
    devices.SetArray();
    for (const ClDeviceInfo& deviceInfo: platformInfo.devices) {
        rapidjson::Value deviceValue;
        setJsonValueToDevice(deviceValue, allocator, deviceInfo);
        devices.PushBack(deviceValue, allocator);
    }
    jsonValue.AddMember("devices", devices, allocator);
}



void JsonSerializer::setJsonValueToDevice(
        rapidjson::Value& jsonValue,
        rapidjson::MemoryPoolAllocator<>& allocator,
        const ClDeviceInfo& deviceInfo) const
{
    jsonValue.SetObject();
    for (const auto& parameter: deviceInfo.parameters) {
        rapidjson::Value parameterValue;
        setJsonValueToParameter(parameterValue, allocator, parameter.second);
        jsonValue.AddMember(parameter.first.c_str(), parameterValue, allocator);
    }
}



void JsonSerializer::setJsonValueToParameter(
        rapidjson::Value& jsonValue,
        rapidjson::MemoryPoolAllocator<>& allocator,
        const ClParameter& clValue) const
{
    switch (clValue.type) {
    case ClParameter::Type::BOOLEAN:
        jsonValue.SetBool(clValue.number);
        break;
    case ClParameter::Type::NUMBER:
        jsonValue.SetUint64(clValue.number);
        break;
    case ClParameter::Type::SIZE_ARRAY:
        jsonValue.SetArray();
        for (size_t size: clValue.sizeArray) {
            jsonValue.PushBack(size, allocator);
        }
        break;
    default:
        jsonValue.SetString(clValue.toString().c_str(), allocator);
        break;
    }
}
