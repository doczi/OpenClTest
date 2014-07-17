#ifndef JSONCLINFOSERIALIZER_H
#define JSONCLINFOSERIALIZER_H

#include "clinfoserializer.h"



class JsonClInfoSerializer: public ClInfoSerializer
{
public:
    std::string serialize(const ClInfo& info) const override;
};



#endif // JSONCLINFOSERIALIZER_H
