#include "clinfogatherer.h"

#include "openclwrapper.h"

#include <sstream>



ClInfoGatherer::ClInfoGatherer(OpenClWrapper& openClWrapper):
    openClWrapper(&openClWrapper)
{}



ClInfo ClInfoGatherer::gatherInfo()
{
    ClInfo result;
    std::vector<cl_platform_id> platformIds = openClWrapper->getPlatformIds();
    for (cl_platform_id platformId: platformIds) {
        result.platforms.emplace_back(gatherPlatformInfo(platformId));
    }
    return result;
}



ClPlatformInfo ClInfoGatherer::gatherPlatformInfo(cl_platform_id platformId)
{
    ClPlatformInfo result;
    result.parameters.emplace("CL_PLATFORM_PROFILE",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_PROFILE));
    result.parameters.emplace("CL_PLATFORM_VERSION",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_VERSION));
    result.parameters.emplace("CL_PLATFORM_NAME",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_NAME));
    result.parameters.emplace("CL_PLATFORM_VENDOR",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_VENDOR));
    result.parameters.emplace("CL_PLATFORM_EXTENSIONS",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS));
    std::vector<cl_device_id> deviceIds =
            openClWrapper->getDeviceIds(platformId);
    for (cl_device_id deviceId: deviceIds) {
        result.devices.emplace_back(gatherDeviceInfo(deviceId));
    }
    return result;
}



#define DEVICE_PARAMETER(type, parameterName) std::make_pair( \
        std::string(#parameterName), \
        openClWrapper->getDeviceInfo<type>(deviceId, parameterName))

#define DEVICE_PARAMETER2(type, parameterName, valueType) std::make_pair( \
        #parameterName, ClParameter(openClWrapper->getDeviceInfo<type>( \
        deviceId, parameterName), valueType))

ClDeviceInfo ClInfoGatherer::gatherDeviceInfo(cl_device_id deviceId)
{
    ClDeviceInfo result;
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_ADDRESS_BITS));
    result.parameters.insert(DEVICE_PARAMETER(bool, CL_DEVICE_AVAILABLE));
    result.parameters.insert(DEVICE_PARAMETER(bool, CL_DEVICE_COMPILER_AVAILABLE));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG, ClParameter::Type::FP_CONFIG));
    result.parameters.insert(DEVICE_PARAMETER(bool, CL_DEVICE_ENDIAN_LITTLE));
    result.parameters.insert(DEVICE_PARAMETER(bool, CL_DEVICE_ERROR_CORRECTION_SUPPORT));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_exec_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES, ClParameter::Type::DEVICE_EXEC_CAPABILITIES));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DEVICE_EXTENSIONS));
    result.parameters.insert(DEVICE_PARAMETER(cl_ulong, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, ClParameter::Type::DEVICE_MEM_CACHE_TYPE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(cl_ulong, CL_DEVICE_GLOBAL_MEM_SIZE));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_fp_config, CL_DEVICE_HALF_FP_CONFIG, ClParameter::Type::FP_CONFIG));
    result.parameters.insert(DEVICE_PARAMETER(cl_bool, CL_DEVICE_HOST_UNIFIED_MEMORY));
    result.parameters.insert(DEVICE_PARAMETER(cl_bool, CL_DEVICE_IMAGE_SUPPORT));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_IMAGE2D_MAX_HEIGHT));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_IMAGE2D_MAX_WIDTH));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_IMAGE3D_MAX_DEPTH));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_IMAGE3D_MAX_HEIGHT));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_IMAGE3D_MAX_WIDTH));
    result.parameters.insert(DEVICE_PARAMETER(cl_ulong, CL_DEVICE_LOCAL_MEM_SIZE));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE, ClParameter::Type::DEVICE_LOCAL_MEM_TYPE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_CLOCK_FREQUENCY));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_COMPUTE_UNITS));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_CONSTANT_ARGS));
    result.parameters.insert(DEVICE_PARAMETER(cl_ulong, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(cl_ulong, CL_DEVICE_MAX_MEM_ALLOC_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_MAX_PARAMETER_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_READ_IMAGE_ARGS));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_SAMPLERS));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_MAX_WORK_GROUP_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS));
    result.parameters.insert(DEVICE_PARAMETER(std::vector<size_t>, CL_DEVICE_MAX_WORK_ITEM_SIZES));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MAX_WRITE_IMAGE_ARGS));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MEM_BASE_ADDR_ALIGN));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DEVICE_NAME));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DEVICE_OPENCL_C_VERSION));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF));
    result.parameters.insert(DEVICE_PARAMETER(size_t, CL_DEVICE_PROFILING_TIMER_RESOLUTION));
    result.parameters.insert(DEVICE_PARAMETER2(cl_command_queue_properties, CL_DEVICE_QUEUE_PROPERTIES, ClParameter::Type::COMMAND_QUEUE_PROPERTIES));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_fp_config, CL_DEVICE_SINGLE_FP_CONFIG, ClParameter::Type::FP_CONFIG));
    result.parameters.insert(DEVICE_PARAMETER2(cl_device_type, CL_DEVICE_TYPE,  ClParameter::Type::DEVICE_TYPE));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DEVICE_VENDOR));
    result.parameters.insert(DEVICE_PARAMETER(cl_uint, CL_DEVICE_VENDOR_ID));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DEVICE_VERSION));
    result.parameters.insert(DEVICE_PARAMETER(std::string, CL_DRIVER_VERSION));
    return result;
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
