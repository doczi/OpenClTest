#include "clinfogatherer.h"
#include "jsonserializer.h"
#include "openclbinder.h"
#include "openclwrapper.h"
#include "xmlserializer.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>



int main(int argc, char* argv[])
{
    try {
        std::map<std::string, std::unique_ptr<Serializer> > serializers;
        serializers.emplace("json", std::unique_ptr<Serializer>(
                new JsonSerializer()));
        serializers.emplace("xml", std::unique_ptr<Serializer>(
                new XmlSerializer()));

        if (argc < 2) {
            throw std::runtime_error("Missing arguments.");
        }
        std::string libraryPath(argv[1]);
        std::string format((argc >= 3) ? argv[2] : "json");

        auto foundSerializer = serializers.find(format);
        if (foundSerializer == serializers.end()) {
            throw std::runtime_error("Unknown format.");
        }
        Serializer& serializer = *(foundSerializer->second);
        OpenCl_1_0_Binder openClBinder(libraryPath);
        OpenClWrapper openClWrapper(openClBinder);
        ClInfoGatherer infoGatherer(openClWrapper);
        ClInfo info = infoGatherer.gatherInfo();
        std::cout << serializer.serialize(info) << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: OpenClTest <library path> [format]" << std::endl;
        return EXIT_FAILURE;
    }
}























#include <memory>

const char *KernelSource = "\n" \
"__kernel void square(                                                       \n" \
"   __global float* input,                                              \n" \
"   __global float* output,                                             \n" \
"   const unsigned int count)                                           \n" \
"{                                                                      \n" \
"   int i = get_global_id(0);                                           \n" \
"   if(i < count)                                                       \n" \
"       output[i] = input[i] * input[i];                                \n" \
"}                                                                      \n" \
"\n";

void compileKernel()
{
    OpenCl_1_2_Binder* binder;
    int err;

    cl_device_id deviceId;
    err = binder->clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_GPU, 1, &deviceId,
            nullptr);
    if (err != CL_SUCCESS) {
        throw OpenClException("Failed to create a device group!", err);
    }

    std::unique_ptr<_cl_context, decltype(binder->clReleaseContext)> context(
            binder->clCreateContext(0, 1, &deviceId, nullptr, nullptr, &err),
            binder->clReleaseContext);
    if (!context) {
        throw OpenClException("Failed to create a compute context!", err);
    }

    std::unique_ptr<_cl_command_queue, decltype(binder->clReleaseCommandQueue)>
            commands(
            binder->clCreateCommandQueue(context.get(), deviceId, 0, &err),
            binder->clReleaseCommandQueue);
    if (!commands) {
        throw OpenClException("Failed to create a command commands!", err);
    }

    std::unique_ptr<_cl_program, decltype(binder->clReleaseProgram)> program(
            binder->clCreateProgramWithSource(context.get(), 1,
                    (const char**)&KernelSource, nullptr, &err),
            binder->clReleaseProgram);
    if (!program) {
        throw OpenClException("Failed to create compute program!", err);
    }

    err = binder->clBuildProgram(program.get(), 0, nullptr, nullptr, nullptr,
            nullptr);
    if (err != CL_SUCCESS) {
        throw OpenClException("Failed to build program executable!", err);
    }

    cl_build_status buildStatus;
    err = binder->clGetProgramBuildInfo(program.get(), deviceId,
            CL_PROGRAM_BUILD_STATUS, sizeof(buildStatus), &buildStatus,
            nullptr);
    if (err != CL_SUCCESS) {
        throw OpenClException("Failed to get build status!", err);
    }

    //err = binder->clGetProgramInfo(program.get(), CL_PROGRAM_BINARIES)
}
