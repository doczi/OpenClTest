#include "jsonclinfoserializer.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>



std::string JsonClInfoSerializer::serialize(const ClInfo& info) const
{
    rapidjson::Document document;
    document.SetArray();

    for (const ClPlatformInfo& platformInfo: info.platforms) {
        rapidjson::Value platform;
        platform.SetObject();
        for (const auto& field: platformInfo.fields) {
            platform.AddMember(
                    field.first.c_str(),
                    field.second.c_str(),
                    document.GetAllocator());
        }

        rapidjson::Value devices;
        devices.SetArray();
        for (const ClDeviceInfo& deviceInfo: platformInfo.devices) {
            rapidjson::Value device;
            device.SetObject();
            for (const auto& field: deviceInfo.fields) {
                device.AddMember(
                        field.first.c_str(),
                        field.second.c_str(),
                        document.GetAllocator());
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
