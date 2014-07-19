#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include "serializer.h"
#include <rapidxml/rapidxml.hpp>



class XmlSerializer: public Serializer
{
public:
    std::string serialize(const ClInfo& info) const override;
};



#endif // XMLSERIALIZER_H
