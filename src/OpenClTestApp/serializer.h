#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>



class ClDeviceInfo;
class ClInfo;
class ClParameter;
class ClPlatformInfo;



/**
 * Abstract base class for objects that serialize a ClInfo object into a string.
 */
class Serializer
{
public:
    virtual ~Serializer() = default;
    virtual std::string serialize(const ClInfo& info) const = 0;
};



#endif // SERIALIZER_H
