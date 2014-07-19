#ifndef OPENCLBINDER_H
#define OPENCLBINDER_H

#include "openclexception.h"

#include <CL/opencl.h>

#include <memory>
#include <string>



#define OCLB_PROCESS_CL_1_0_FUNCTIONS(action) \
        action(clGetPlatformIDs) \
        action(clGetPlatformInfo) \
        action(clGetDeviceIDs) \
        action(clGetDeviceInfo) \
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
        action(clCreateImage2D) \
        action(clCreateImage3D) \
        action(clRetainMemObject) \
        action(clReleaseMemObject) \
        action(clGetSupportedImageFormats) \
        action(clGetMemObjectInfo) \
        action(clGetImageInfo) \
        action(clCreateSampler) \
        action(clRetainSampler) \
        action(clReleaseSampler) \
        action(clGetSamplerInfo) \
        action(clCreateProgramWithSource) \
        action(clCreateProgramWithBinary) \
        action(clRetainProgram) \
        action(clReleaseProgram) \
        action(clBuildProgram) \
        action(clGetProgramInfo) \
        action(clGetProgramBuildInfo) \
        action(clCreateKernel) \
        action(clCreateKernelsInProgram) \
        action(clRetainKernel) \
        action(clReleaseKernel) \
        action(clSetKernelArg) \
        action(clGetKernelInfo) \
        action(clGetKernelWorkGroupInfo) \
        action(clWaitForEvents) \
        action(clGetEventInfo) \
        action(clRetainEvent) \
        action(clReleaseEvent) \
        action(clGetEventProfilingInfo) \
        action(clFlush) \
        action(clFinish) \
        action(clEnqueueReadBuffer) \
        action(clEnqueueWriteBuffer) \
        action(clEnqueueCopyBuffer) \
        action(clEnqueueReadImage) \
        action(clEnqueueWriteImage) \
        action(clEnqueueCopyImage) \
        action(clEnqueueCopyImageToBuffer) \
        action(clEnqueueCopyBufferToImage) \
        action(clEnqueueMapBuffer) \
        action(clEnqueueMapImage) \
        action(clEnqueueUnmapMemObject) \
        action(clEnqueueNDRangeKernel) \
        action(clEnqueueNativeKernel) \
        action(clEnqueueMarker) \
        action(clEnqueueWaitForEvents) \
        action(clEnqueueBarrier) \
        action(clEnqueueTask) \
        action(clUnloadCompiler) \
        action(clGetExtensionFunctionAddress)

#define OCLB_PROCESS_CL_1_1_FUNCTIONS(action) \
        action(clCreateSubBuffer) \
        action(clSetMemObjectDestructorCallback) \
        action(clCreateUserEvent) \
        action(clSetUserEventStatus) \
        action(clSetEventCallback) \
        action(clEnqueueReadBufferRect) \
        action(clEnqueueWriteBufferRect) \
        action(clEnqueueCopyBufferRect)

#define OCLB_PROCESS_CL_1_2_FUNCTIONS(action) \
        action(clCreateSubDevices) \
        action(clRetainDevice) \
        action(clReleaseDevice) \
        action(clCreateImage) \
        action(clCreateProgramWithBuiltInKernels) \
        action(clCompileProgram) \
        action(clLinkProgram) \
        action(clUnloadPlatformCompiler) \
        action(clGetKernelArgInfo) \
        action(clEnqueueFillBuffer) \
        action(clEnqueueFillImage) \
        action(clEnqueueMigrateMemObjects) \
        action(clEnqueueMarkerWithWaitList) \
        action(clEnqueueBarrierWithWaitList) \
        action(clGetExtensionFunctionAddressForPlatform)

#define OCLB_PROCESS_CL_2_0_FUNCTIONS(action) \
        action(clCreateCommandQueueWithProperties) \
        action(clCreatePipe) \
        action(clGetPipeInfo) \
        action(clSVMAlloc) \
        action(clSVMFree) \
        action(clCreateSamplerWithProperties) \
        action(clSetKernelArgSVMPointer) \
        action(clSetKernelExecInfo) \
        action(clEnqueueSVMFree) \
        action(clEnqueueSVMMemcpy) \
        action(clEnqueueSVMMemFill) \
        action(clEnqueueSVMMap) \
        action(clEnqueueSVMUnmap)



#define OCLB_DECLARE_POINTER(function) decltype(&::function) const function;



/**
 * Provides access to OpenCL 1.0 functions loaded dynamically in runtime.
 */
class OpenCl_1_0_Binder
{
protected:
    class Loader;
    std::unique_ptr<Loader> loader;
public:
    OpenCl_1_0_Binder(const std::string& openClPath);
    virtual ~OpenCl_1_0_Binder();
    OCLB_PROCESS_CL_1_0_FUNCTIONS(OCLB_DECLARE_POINTER)
};



/**
 * Provides access to OpenCL 1.1 functions loaded dynamically in runtime.
 */
class OpenCl_1_1_Binder: public OpenCl_1_0_Binder
{
public:
    OpenCl_1_1_Binder(const std::string& openClPath);
    OCLB_PROCESS_CL_1_1_FUNCTIONS(OCLB_DECLARE_POINTER)
};



/**
 * Provides access to OpenCL 1.2 functions loaded dynamically in runtime.
 */
class OpenCl_1_2_Binder: public OpenCl_1_1_Binder
{
public:
    OpenCl_1_2_Binder(const std::string& openClPath);
    OCLB_PROCESS_CL_1_2_FUNCTIONS(OCLB_DECLARE_POINTER)
};



/**
 * Provides access to OpenCL 2.0 functions loaded dynamically in runtime.
 */
class OpenCl_2_0_Binder: public OpenCl_1_2_Binder
{
public:
    OpenCl_2_0_Binder(const std::string& openClPath);
    OCLB_PROCESS_CL_2_0_FUNCTIONS(OCLB_DECLARE_POINTER)
};



#undef OCLB_DECLARE_POINTER



#endif // OPENCLBINDER_H
