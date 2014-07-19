#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>



class ClInfo;



class Serializer
{
public:
    virtual ~Serializer() = default;
    virtual std::string serialize(const ClInfo& info) const = 0;
};



#endif // SERIALIZER_H
