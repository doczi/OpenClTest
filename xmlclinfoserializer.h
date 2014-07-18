#ifndef XMLCLINFOSERIALIZER_H
#define XMLCLINFOSERIALIZER_H



#include "clinfoserializer.h"
#include <rapidxml/rapidxml.hpp>



class XmlClInfoSerializer: public ClInfoSerializer
{
public:
    std::string serialize(const ClInfo& info) const override;
};



#endif // XMLCLINFOSERIALIZER_H
