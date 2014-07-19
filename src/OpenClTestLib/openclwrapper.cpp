#include "openclwrapper.h"



OpenClWrapper::OpenClWrapper(OpenCl_1_0_Binder& binder):
    binder(&binder)
{}



std::vector<cl_platform_id> OpenClWrapper::getPlatformIds() const
{
    cl_uint platformCount = 0;
    cl_int error = binder->clGetPlatformIDs(0, nullptr, &platformCount);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }

    std::vector<cl_platform_id> result(platformCount);
    error = binder->clGetPlatformIDs(platformCount, result.data(), nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }
    return result;
}



std::string OpenClWrapper::getPlatformInfo(
        cl_platform_id platformId,
        cl_platform_info parameterName) const
{
    size_t resultSize;
    cl_int error = binder->clGetPlatformInfo(platformId, parameterName, 0,
            nullptr, &resultSize);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform info", error);
    }

    std::string result(resultSize, '\0');
    error = binder->clGetPlatformInfo(platformId, parameterName, resultSize,
            &result[0], nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform info", error);
    }
    return result;
}



std::vector<cl_device_id> OpenClWrapper::getDeviceIds(
        cl_platform_id platformId) const
{
    cl_uint deviceCount = 0;
    cl_int error = binder->clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 0,
            nullptr, &deviceCount);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }

    std::vector<cl_device_id> result(deviceCount);
    error = binder->clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, deviceCount,
            result.data(), nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }
    return result;
}



template<>
std::string OpenClWrapper::getDeviceInfo<std::string>(
        cl_device_id deviceId,
        cl_device_info parameterName) const
{
    size_t resultSize;
    cl_int error = binder->clGetDeviceInfo(deviceId, parameterName, 0, nullptr,
            &resultSize);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }

    std::string result(resultSize, '\0');
    error = binder->clGetDeviceInfo(deviceId, parameterName, resultSize,
            &result[0], nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    return result;
}



template<>
std::vector<size_t> OpenClWrapper::getDeviceInfo<std::vector<size_t> >(
        cl_device_id deviceId,
        cl_device_info parameterName) const
{
    size_t resultSize;
    cl_int error = binder->clGetDeviceInfo(deviceId, parameterName, 0, nullptr,
            &resultSize);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }

    std::vector<size_t> result(resultSize / sizeof(size_t));
    error = binder->clGetDeviceInfo(deviceId, parameterName, resultSize,
            result.data(), nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    return result;
}



template<>
bool OpenClWrapper::getDeviceInfo<bool>(
        cl_device_id deviceId,
        cl_device_info parameterName) const
{
    cl_bool result;
    cl_int error = binder->clGetDeviceInfo(deviceId, parameterName,
            sizeof(result), &result, nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    return result;
}
