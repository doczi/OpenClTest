#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include "serializer.h"
#include <rapidxml/rapidxml.hpp>



/**
 * Serializes a ClInfo object into XML format.
 */
class XmlSerializer: public Serializer
{
public:
    std::string serialize(const ClInfo& info) const override;
    rapidxml::xml_node<>* platformToNode(
            const ClPlatformInfo& platformInfo,
            rapidxml::xml_document<>& document) const;
    rapidxml::xml_node<>* deviceToNode(
            const ClDeviceInfo& deviceInfo,
            rapidxml::xml_document<>& document) const;
    rapidxml::xml_node<>* parameterToNode(
            const std::string& name,
            const ClParameter& parameter,
            rapidxml::xml_document<>& document) const;
};



#endif // XMLSERIALIZER_H
