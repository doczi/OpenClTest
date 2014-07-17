#ifndef CLINFOGATHERER_H
#define CLINFOGATHERER_H

#include "clinfo.h"

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>



class ClInfoGatherer
{
public:
    ClInfoGatherer();
    void start();
    ClInfo gatherInfo();
    void finish();

    ClInfoField getPlatformField(
            const cl::Platform& platform,
            const std::string fieldName,
            cl_platform_info fieldId) const;
    template<class T>
    ClInfoField getDeviceField(
            const cl::Device& device,
            const std::string fieldName,
            cl_device_info fieldId) const;
};



#endif // CLINFOGATHERER_H
