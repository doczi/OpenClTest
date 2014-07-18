#ifndef OPENCLWRAPPER_H
#define OPENCLWRAPPER_H

#include "openclbinder.h"
#include "openclexception.h"
#include <string>
#include <vector>



class OpenClWrapper
{
public:
    OpenClWrapper(OpenClBinder& binder);

    std::vector<cl_platform_id> getPlatformIds() const;
    std::string getPlatformInfo(
            cl_platform_id platformId,
            cl_platform_info parameterName) const;
    std::vector<cl_device_id> getDeviceIds(
            cl_platform_id platformId) const;
    template<class T> T getDeviceInfo(
            cl_device_id deviceId,
            cl_device_info parameterName) const;
    cl_context createContext(const std::vector<cl_device_id>& deviceIds) const;
    void releaseContext(cl_context context) const;
private:
    OpenClBinder* binder;
};



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
