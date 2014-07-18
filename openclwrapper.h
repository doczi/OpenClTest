#ifndef OPENCLWRAPPER_H
#define OPENCLWRAPPER_H

#include <CL/opencl.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>



#define PROCESS_OPEN_CL_FUNCTION_LIST(action) \
    action(clGetPlatformIDs) \
    action(clGetPlatformInfo) \
    action(clGetDeviceIDs) \
    action(clGetDeviceInfo) \
    action(clCreateSubDevices) \
    action(clRetainDevice) \
    action(clReleaseDevice) \
    action(clCreateContext) \
    action(clCreateContextFromType) \
    action(clRetainContext) \
    action(clReleaseContext) \
    action(clGetContextInfo) \
    action(clCreateCommandQueue) \
    action(clRetainCommandQueue) \
    action(clReleaseCommandQueue) \
    action(clGetCommandQueueInfo) \
    action(clCreateBuffer) \
    action(clCreateSubBuffer) \
    action(clCreateImage) \
    action(clRetainMemObject) \
    action(clReleaseMemObject) \
    action(clGetSupportedImageFormats) \
    action(clGetMemObjectInfo) \
    action(clGetImageInfo) \
    action(clSetMemObjectDestructorCallback) \
    action(clCreateSampler) \
    action(clRetainSampler) \
    action(clReleaseSampler) \
    action(clGetSamplerInfo) \
    action(clCreateProgramWithSource) \
    action(clCreateProgramWithBinary) \
    action(clCreateProgramWithBuiltInKernels) \
    action(clRetainProgram) \
    action(clReleaseProgram) \
    action(clBuildProgram) \
    action(clCompileProgram) \
    action(clLinkProgram) \
    action(clUnloadPlatformCompiler) \
    action(clGetProgramInfo) \
    action(clGetProgramBuildInfo) \
    action(clCreateKernel) \
    action(clCreateKernelsInProgram) \
    action(clRetainKernel) \
    action(clReleaseKernel) \
    action(clSetKernelArg) \
    action(clGetKernelInfo) \
    action(clGetKernelArgInfo) \
    action(clGetKernelWorkGroupInfo) \
    action(clWaitForEvents) \
    action(clGetEventInfo) \
    action(clCreateUserEvent) \
    action(clRetainEvent) \
    action(clReleaseEvent) \
    action(clSetUserEventStatus) \
    action(clSetEventCallback) \
    action(clGetEventProfilingInfo) \
    action(clFlush) \
    action(clFinish) \
    action(clEnqueueReadBuffer) \
    action(clEnqueueReadBufferRect) \
    action(clEnqueueWriteBuffer) \
    action(clEnqueueWriteBufferRect) \
    action(clEnqueueFillBuffer) \
    action(clEnqueueCopyBuffer) \
    action(clEnqueueCopyBufferRect) \
    action(clEnqueueReadImage) \
    action(clEnqueueWriteImage) \
    action(clEnqueueFillImage) \
    action(clEnqueueCopyImage) \
    action(clEnqueueCopyImageToBuffer) \
    action(clEnqueueCopyBufferToImage) \
    action(clEnqueueMapBuffer) \
    action(clEnqueueMapImage) \
    action(clEnqueueUnmapMemObject) \
    action(clEnqueueMigrateMemObjects) \
    action(clEnqueueNDRangeKernel) \
    action(clEnqueueTask) \
    action(clEnqueueNativeKernel) \
    action(clEnqueueMarkerWithWaitList) \
    action(clEnqueueBarrierWithWaitList) \
    action(clGetExtensionFunctionAddressForPlatform)



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
            cl_device_info parameterName) const;
    cl_context createContext(const std::vector<cl_device_id>& deviceIds) const;
    void releaseContext(cl_context context) const;
private:
    void* libraryHandle;

    void* openLibrary(const std::string& path);
    template<class T> void bindFunction(
            T& functionPointer,
            const std::string& name);

    #define DECLARE_FUNCTION_POINTER(function) decltype(&::function) function;
    PROCESS_OPEN_CL_FUNCTION_LIST(DECLARE_FUNCTION_POINTER)
    #undef DECLARE_FUNCTION_POINTER
};



template<class T>
T OpenClWrapper::getDeviceInfo(
        cl_device_id deviceId,
        cl_device_info parameterName) const
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
