#ifndef OPENCLWRAPPER_H
#define OPENCLWRAPPER_H

#include "openclbinder.h"
#include "openclexception.h"

#include <string>
#include <vector>



/**
 * Wraps some OpenCL functionality for ease of use with standard containers and
 * exceptions.
 */
class OpenClWrapper
{
public:
    OpenClWrapper(OpenCl_1_0_Binder& binder);

    std::vector<cl_platform_id> getPlatformIds() const;
    std::string getPlatformInfo(
            cl_platform_id platformId,
            cl_platform_info parameterName) const;
    std::vector<cl_device_id> getDeviceIds(
            cl_platform_id platformId) const;
    template<class T> T getDeviceInfo(
            cl_device_id deviceId,
            cl_device_info parameterName) const;
    std::string getBuildLog(
            cl_program program,
            cl_device_id device) const;
    std::vector<std::vector<unsigned char> > getProgramBinaries(
            cl_program program) const;
private:
    OpenCl_1_0_Binder* binder;
};



template<>
std::string OpenClWrapper::getDeviceInfo<std::string>(
        cl_device_id deviceId,
        cl_device_info parameterName) const;

template<>
std::vector<size_t> OpenClWrapper::getDeviceInfo<std::vector<size_t> >(
        cl_device_id deviceId,
        cl_device_info parameterName) const;

template<>
bool OpenClWrapper::getDeviceInfo<bool>(
        cl_device_id deviceId,
        cl_device_info parameterName) const;

template<class T>
T OpenClWrapper::getDeviceInfo(
        cl_device_id deviceId,
        cl_device_info parameterName) const
{
    T result;
    cl_int error = binder->clGetDeviceInfo(deviceId, parameterName,
            sizeof(result), &result, nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    return result;
}



#endif // OPENCLWRAPPER_H
