#ifndef CLINFO_H
#define CLINFO_H

#include <string>
#include <map>
#include <vector>



struct ClDeviceInfo
{
    std::map<std::string, std::string> fields;
};

struct ClPlatformInfo
{
    std::map<std::string, std::string> fields;
    std::vector<ClDeviceInfo> devices;
};

struct ClInfo
{
    std::vector<ClPlatformInfo> platforms;
};



#endif // CLINFO_H
