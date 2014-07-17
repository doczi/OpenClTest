#ifndef OPENCLWRAPPER_H
#define OPENCLWRAPPER_H

#include <CL/opencl.h>

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>



class OpenClException: public std::runtime_error
{
public:
    OpenClException(const std::string& message):
        std::runtime_error(message)
    {}
    OpenClException(const std::string& message, cl_int errorCode):
        std::runtime_error(message + " (" + toString(errorCode) + ")")
    {}
private:
    static std::string toString(cl_int code) {
        std::ostringstream oss;
        oss << code;
        return oss.str();
    }
};



class OpenClWrapper
{
public:
    OpenClWrapper(const std::string& openClPath);
    ~OpenClWrapper();
    std::vector<cl_platform_id> getPlatformIds() const;
    std::string getPlatformInfo(
            cl_platform_id platformId,
            cl_platform_info parameterName) const;
    std::vector<cl_device_id> getDeviceIds(
            cl_platform_id platformId) const;
    template<class T> T getDeviceInfo(
            cl_device_id deviceId,
            cl_device_info parameterName);
private:
    void* libraryHandle;

    void* openLibrary(const std::string& path);
    template<class T> void bindFunction(
            T& functionPointer,
            const std::string& name);

    cl_int CL_API_CALL (*clGetPlatformIDs)(
            cl_uint num_entries,
            cl_platform_id* platforms,
            cl_uint* num_platforms);
    cl_int CL_API_CALL (*clGetPlatformInfo)(
            cl_platform_id platform,
            cl_platform_info param_name,
            size_t param_value_size,
            void* param_value,
            size_t* param_value_size_ret);
    cl_int CL_API_CALL (*clGetDeviceIDs)(
            cl_platform_id platform,
            cl_device_type device_type,
            cl_uint num_entries,
            cl_device_id* devices,
            cl_uint* num_devices);
    cl_int CL_API_CALL (*clGetDeviceInfo)(
            cl_device_id device,
            cl_device_info param_name,
            size_t param_value_size,
            void* param_value,
            size_t* param_value_size_ret);
};



template<class T>
T OpenClWrapper::getDeviceInfo(
        cl_device_id deviceId,
        cl_device_info parameterName)
{
    T result;
    cl_int error = clGetDeviceInfo(deviceId, parameterName, sizeof(result),
            &result, nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    return result;
}



#endif // OPENCLWRAPPER_H
