#include "clinfogatherer.h"

#include "openclwrapper.h"

#include <sstream>



ClInfoGatherer::ClInfoGatherer(OpenClWrapper& openClWrapper):
    openClWrapper(&openClWrapper)
{}



#define ADD_PLATFORM_FIELD(fieldId) platformInfo.fields.insert( \
        getPlatformField(platform, #fieldId, fieldId))
#define ADD_DEVICE_FIELD(type, fieldId) deviceInfo.fields.insert( \
        getDeviceField<type>(device, #fieldId, fieldId))

ClInfo ClInfoGatherer::gatherInfo()
{

    ClInfo result;

    std::vector<cl_platform_id> platforms = openClWrapper->getPlatformIds();
    for (cl_platform_id platform: platforms) {
        ClPlatformInfo platformInfo;
        ADD_PLATFORM_FIELD(CL_PLATFORM_PROFILE);
        ADD_PLATFORM_FIELD(CL_PLATFORM_VERSION);
        ADD_PLATFORM_FIELD(CL_PLATFORM_NAME);
        ADD_PLATFORM_FIELD(CL_PLATFORM_VENDOR);
        ADD_PLATFORM_FIELD(CL_PLATFORM_EXTENSIONS);

        std::vector<cl_device_id> devices =
                openClWrapper->getDeviceIds(platform);
        for (cl_device_id device: devices) {
            ClDeviceInfo deviceInfo;
            ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_ADDRESS_BITS);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_AVAILABLE);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_COMPILER_AVAILABLE);
            //ADD_DEVICE_FIELD(cl_device_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_ENDIAN_LITTLE);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_ERROR_CORRECTION_SUPPORT);
            //ADD_DEVICE_FIELD(cl_device_exec_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES);
            ADD_DEVICE_FIELD(std::string, CL_DEVICE_EXTENSIONS);
            ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
            //ADD_DEVICE_FIELD(cl_device_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
            ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
            ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_GLOBAL_MEM_SIZE);
            //ADD_DEVICE_FIELD(cl_device_fp_config, CL_DEVICE_HALF_FP_CONFIG);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_HOST_UNIFIED_MEMORY);
            ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_IMAGE_SUPPORT);

            platformInfo.devices.emplace_back(std::move(deviceInfo));
        }

        result.platforms.emplace_back(std::move(platformInfo));
    }

    return result;
}

#undef GET_PLATFORM_FIELD
#undef GET_DEVICE_FIELD



std::pair<std::string, std::string> ClInfoGatherer::getPlatformField(
        cl_platform_id platformId,
        const std::string fieldName,
        cl_platform_info fieldId) const
{
    std::string value = openClWrapper->getPlatformInfo(platformId, fieldId);
    return std::make_pair(fieldName, value);
}



template<class T>
std::pair<std::string, std::string> ClInfoGatherer::getDeviceField(
        cl_device_id deviceId,
        const std::string fieldName,
        cl_device_info fieldId) const
{
    std::ostringstream oss;
    oss << openClWrapper->getDeviceInfo<T>(deviceId, fieldId);
    return std::make_pair(fieldName, oss.str());
}
