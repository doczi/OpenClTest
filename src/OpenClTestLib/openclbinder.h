#ifndef OPENCLBINDER_H
#define OPENCLBINDER_H

#include "openclexception.h"

#include <CL/opencl.h>

#include <memory>
#include <string>



#define OCLB_PROCESS_OPEN_CL_FUNCTIONS(action) \
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



/**
 * Provides access to OpenCL functions loaded dynamically in runtime.
 */
class OpenClBinder
{
private:
    class Loader;
    std::unique_ptr<Loader> loader;

    OpenClBinder(const OpenClBinder&) = delete;
    OpenClBinder& operator=(const OpenClBinder&) = delete;
public:
    OpenClBinder(const std::string& openClPath);
    ~OpenClBinder();

    #define OCLB_DECLARE_POINTER(function) decltype(&::function) const function;
    OCLB_PROCESS_OPEN_CL_FUNCTIONS(OCLB_DECLARE_POINTER)
    #undef OCLB_DECLARE_POINTER
};



#endif // OPENCLBINDER_H
