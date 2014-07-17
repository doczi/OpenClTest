#ifndef CLINFO_H
#define CLINFO_H

#include <string>
#include <vector>



struct ClInfoField
{
    std::string name;
    std::string value;
};

struct ClDeviceInfo
{
    std::vector<ClInfoField> fields;
};

struct ClPlatformInfo
{
    std::vector<ClInfoField> fields;
    std::vector<ClDeviceInfo> devices;
};

struct ClInfo
{
    std::vector<ClPlatformInfo> platforms;
};



#endif // CLINFO_H
