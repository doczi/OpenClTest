#include "xmlserializer.h"

#include "clinfo.h"

#include <rapidxml/rapidxml_print.hpp>



std::string XmlSerializer::serialize(const ClInfo& info) const
{
    rapidxml::xml_document<> document;
    for (const ClPlatformInfo& platformInfo: info.platforms) {
        document.append_node(platformToNode(platformInfo, document));
    }
    std::string result;
    rapidxml::print(std::back_inserter(result), document, 0);
    return result;
}



rapidxml::xml_node<>* XmlSerializer::platformToNode(
        const ClPlatformInfo& platform,
        rapidxml::xml_document<>& document) const
{
    rapidxml::xml_node<>* platformNode = document.allocate_node(
            rapidxml::node_element, "Platform");
    for (const auto& parameter: platform.parameters) {
        platformNode->append_node(
                parameterToNode(parameter.first, parameter.second, document));
    }
    for (const ClDeviceInfo& deviceInfo: platform.devices) {
        platformNode->append_node(deviceToNode(deviceInfo, document));
    }
    return platformNode;
}



rapidxml::xml_node<>* XmlSerializer::deviceToNode(
        const ClDeviceInfo& device,
        rapidxml::xml_document<>& document) const
{
    rapidxml::xml_node<>* deviceNode =
            document.allocate_node(rapidxml::node_element, "Device");
    for (const auto& parameter: device.parameters) {
        deviceNode->append_node(
                parameterToNode(parameter.first, parameter.second, document));
    }
    return deviceNode;
}



rapidxml::xml_node<>* XmlSerializer::parameterToNode(
        const std::string& name,
        const ClParameter& parameter,
        rapidxml::xml_document<>& document) const
{
    rapidxml::xml_node<>* parameterNode = document.allocate_node(
            rapidxml::node_element, "Parameter");
    parameterNode->append_attribute(document.allocate_attribute(
            "name", document.allocate_string(name.c_str())));
    parameterNode->append_attribute(document.allocate_attribute(
            "value", document.allocate_string(parameter.toString().c_str())));
    return parameterNode;
}
