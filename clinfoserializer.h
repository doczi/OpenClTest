#ifndef CLINFOSERIALIZER_H
#define CLINFOSERIALIZER_H

#include "clinfo.h"
#include <string>



class ClInfoSerializer
{
public:
    virtual ~ClInfoSerializer() = default;
    virtual std::string serialize(const ClInfo& info) const = 0;
};



#endif // CLINFOSERIALIZER_H
