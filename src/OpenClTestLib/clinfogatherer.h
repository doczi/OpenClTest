#ifndef CLINFOGATHERER_H
#define CLINFOGATHERER_H

#include "clinfo.h"
#include "openclwrapper.h"

#include <utility>



class OpenClWrapper;



class ClInfoGatherer
{
public:
    ClInfoGatherer(OpenCl_1_0_Binder& binder);

    ClInfo gatherInfo();
    ClPlatformInfo gatherPlatformInfo(cl_platform_id platformId);
    ClDeviceInfo gatherDeviceInfo(cl_device_id);
    std::string testCompilation();
private:
    OpenCl_1_0_Binder& binder;
    OpenClWrapper wrapper;

    template<class T>
    std::pair<std::string, std::string> getDeviceParameter(
            cl_device_id deviceId,
            const std::string fieldName,
            cl_device_info fieldId) const;
};



#endif // CLINFOGATHERER_H
