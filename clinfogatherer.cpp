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
    result.fields.emplace("CL_PLATFORM_PROFILE",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_PROFILE));
    result.fields.emplace("CL_PLATFORM_VERSION",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_VERSION));
    result.fields.emplace("CL_PLATFORM_NAME",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_NAME));
    result.fields.emplace("CL_PLATFORM_VENDOR",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_VENDOR));
    result.fields.emplace("CL_PLATFORM_EXTENSIONS",
            openClWrapper->getPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS));
    std::vector<cl_device_id> deviceIds =
            openClWrapper->getDeviceIds(platformId);
    for (cl_device_id deviceId: deviceIds) {
        result.devices.emplace_back(gatherDeviceInfo(deviceId));
    }
    return result;
}



#define ADD_DEVICE_FIELD(type, parameterName) result.fields.emplace( \
        #parameterName, ClValue(openClWrapper->getDeviceInfo<type>( \
        deviceId, parameterName)))

#define ADD_DEVICE_FIELD2(type, parameterName, valueType) \
        result.fields.emplace( \
        #parameterName, ClValue(openClWrapper->getDeviceInfo<type>( \
        deviceId, parameterName), valueType))

ClDeviceInfo ClInfoGatherer::gatherDeviceInfo(cl_device_id deviceId)
{
    ClDeviceInfo result;
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_ADDRESS_BITS);
    ADD_DEVICE_FIELD(bool, CL_DEVICE_AVAILABLE);
    ADD_DEVICE_FIELD(bool, CL_DEVICE_COMPILER_AVAILABLE);
    ADD_DEVICE_FIELD2(cl_device_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG, ClValue::Type::FP_CONFIG);
    ADD_DEVICE_FIELD(bool, CL_DEVICE_ENDIAN_LITTLE);
    ADD_DEVICE_FIELD(bool, CL_DEVICE_ERROR_CORRECTION_SUPPORT);
    ADD_DEVICE_FIELD2(cl_device_exec_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES, ClValue::Type::DEVICE_EXEC_CAPABILITIES);
    ADD_DEVICE_FIELD(std::string, CL_DEVICE_EXTENSIONS);
    ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
    ADD_DEVICE_FIELD2(cl_device_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, ClValue::Type::DEVICE_MEM_CACHE_TYPE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
    ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_GLOBAL_MEM_SIZE);
    ADD_DEVICE_FIELD2(cl_device_fp_config, CL_DEVICE_HALF_FP_CONFIG, ClValue::Type::FP_CONFIG);
    ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_HOST_UNIFIED_MEMORY);
    ADD_DEVICE_FIELD(cl_bool, CL_DEVICE_IMAGE_SUPPORT);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_IMAGE2D_MAX_HEIGHT);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_IMAGE2D_MAX_WIDTH);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_IMAGE3D_MAX_DEPTH);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_IMAGE3D_MAX_HEIGHT);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_IMAGE3D_MAX_WIDTH);
    ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_LOCAL_MEM_SIZE);
    ADD_DEVICE_FIELD2(cl_device_local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE, ClValue::Type::DEVICE_LOCAL_MEM_TYPE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_CLOCK_FREQUENCY);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_COMPUTE_UNITS);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_CONSTANT_ARGS);
    ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
    ADD_DEVICE_FIELD(cl_ulong, CL_DEVICE_MAX_MEM_ALLOC_SIZE);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_MAX_PARAMETER_SIZE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_READ_IMAGE_ARGS);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_SAMPLERS);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_MAX_WORK_GROUP_SIZE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
    ADD_DEVICE_FIELD(std::vector<size_t>, CL_DEVICE_MAX_WORK_ITEM_SIZES);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MEM_BASE_ADDR_ALIGN);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE);
    ADD_DEVICE_FIELD(std::string, CL_DEVICE_NAME);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF);
    ADD_DEVICE_FIELD(std::string, CL_DEVICE_OPENCL_C_VERSION);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF);
    ADD_DEVICE_FIELD(size_t, CL_DEVICE_PROFILING_TIMER_RESOLUTION);
    ADD_DEVICE_FIELD2(cl_command_queue_properties, CL_DEVICE_QUEUE_PROPERTIES, ClValue::Type::COMMAND_QUEUE_PROPERTIES);
    ADD_DEVICE_FIELD2(cl_device_fp_config, CL_DEVICE_SINGLE_FP_CONFIG, ClValue::Type::FP_CONFIG);
    ADD_DEVICE_FIELD2(cl_device_type, CL_DEVICE_TYPE,  ClValue::Type::DEVICE_TYPE);
    ADD_DEVICE_FIELD(std::string, CL_DEVICE_VENDOR);
    ADD_DEVICE_FIELD(cl_uint, CL_DEVICE_VENDOR_ID);
    ADD_DEVICE_FIELD(std::string, CL_DEVICE_VERSION);
    ADD_DEVICE_FIELD(std::string, CL_DRIVER_VERSION);
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
