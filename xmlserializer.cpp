#include "xmlserializer.h"

#include "clinfo.h"

#include <rapidxml/rapidxml_print.hpp>



std::string XmlSerializer::serialize(const ClInfo& info) const
{
    rapidxml::xml_document<> document;
    for (const ClPlatformInfo& platformInfo: info.platforms) {
        rapidxml::xml_node<>* platform = document.allocate_node(
                rapidxml::node_element, "Platform");
        for (const auto& field: platformInfo.fields) {
            rapidxml::xml_node<>* parameter = document.allocate_node(
                    rapidxml::node_element, "Parameter");
            parameter->append_attribute(document.allocate_attribute(
                    "name", field.first.c_str()));
            parameter->append_attribute(document.allocate_attribute(
                    "value", document.allocate_string(
                            field.second.toString().c_str())));
            platform->append_node(parameter);
        }
        for (const ClDeviceInfo& deviceInfo: platformInfo.devices) {
            rapidxml::xml_node<>* device =
                    document.allocate_node(rapidxml::node_element, "Device");
            for (const auto& field: deviceInfo.fields) {
                rapidxml::xml_node<>* parameter = document.allocate_node(
                        rapidxml::node_element, "Parameter");
                parameter->append_attribute(document.allocate_attribute(
                        "name", field.first.c_str()));
                parameter->append_attribute(document.allocate_attribute(
                        "value", document.allocate_string(
                                field.second.toString().c_str())));
                device->append_node(parameter);
            }
            platform->append_node(device);
        }
        document.append_node(platform);
    }
    std::string result;
    rapidxml::print(std::back_inserter(result), document, 0);
    return result;
}
