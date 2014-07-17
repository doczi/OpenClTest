#ifndef CLINFOGATHERER_H
#define CLINFOGATHERER_H

#include "clinfo.h"
#include "openclwrapper.h"

#include <utility>



class OpenClWrapper;



class ClInfoGatherer
{
public:
    ClInfoGatherer(OpenClWrapper& openClWrapper);

    ClInfo gatherInfo();

    std::pair<std::string, std::string> getPlatformField(
            cl_platform_id platformId,
            const std::string fieldName,
            cl_platform_info fieldId) const;
    template<class T>
    std::pair<std::string, std::string> getDeviceField(
            cl_device_id deviceId,
            const std::string fieldName,
            cl_device_info fieldId) const;
private:
    OpenClWrapper* openClWrapper;
};



#endif // CLINFOGATHERER_H
