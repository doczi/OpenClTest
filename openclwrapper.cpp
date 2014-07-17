#include "openclwrapper.h"

#include <dlfcn.h>



#define BIND(function) bindFunction(function, #function);



OpenClWrapper::OpenClWrapper(const std::string& openClPath)
{
    libraryHandle = openLibrary(openClPath);
    BIND(clGetPlatformIDs);
    BIND(clGetPlatformInfo);
    BIND(clGetDeviceIDs);
    BIND(clGetDeviceInfo);
}



OpenClWrapper::~OpenClWrapper()
{
    dlclose(libraryHandle);
}



std::vector<cl_platform_id> OpenClWrapper::getPlatformIds() const
{
    cl_uint platformCount = 0;
    cl_int error = clGetPlatformIDs(0, nullptr, &platformCount);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }

    std::vector<cl_platform_id> result(platformCount);
    error = clGetPlatformIDs(platformCount, result.data(), nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }
    return result;
}



std::string OpenClWrapper::getPlatformInfo(
        cl_platform_id platformId,
        cl_platform_info parameterName) const
{
    std::string result(MAX_STRING_LENGTH, '\0');
    size_t resultSize;
    cl_int error = clGetPlatformInfo(platformId, parameterName, result.size(),
            &result[0], &resultSize);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform info", error);
    }
    result.resize(resultSize);
    return result;
}



std::vector<cl_device_id> OpenClWrapper::getDeviceIds(
        cl_platform_id platformId) const
{
    cl_uint deviceCount = 0;
    cl_int error = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 0, nullptr,
            &deviceCount);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }

    std::vector<cl_device_id> result(deviceCount);
    error = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, deviceCount,
            result.data(), nullptr);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get platform IDs", error);
    }
    return result;
}



void* OpenClWrapper::openLibrary(const std::string& path)
{
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        throw OpenClException("Cannot open library: " + path +
                " (" + dlerror() + ")");
    }
    return handle;
}



template<class T>
void OpenClWrapper::bindFunction(T& functionPointer, const std::string& name)
{
    void* pointer = dlsym(libraryHandle, name.c_str());
    if (pointer == nullptr) {
        throw OpenClException("Cannot bind function: " + name +
                " (" + dlerror() + ")");
    }
    functionPointer = reinterpret_cast<T>(pointer);
}



template<>
std::string OpenClWrapper::getDeviceInfo<std::string>(
        cl_device_id deviceId,
        cl_device_info parameterName)
{
    std::string result(MAX_STRING_LENGTH, '\0');
    size_t resultSize;
    cl_int error = clGetDeviceInfo(deviceId, parameterName, result.size(),
            &result[0], &resultSize);
    if (error != CL_SUCCESS) {
        throw OpenClException("Cannot get device info", error);
    }
    result.resize(resultSize);
    return result;
}
