#include "clinfogatherer.h"
#include "jsonclinfoserializer.h"
#include "openclbinder.h"
#include "openclwrapper.h"
#include "xmlclinfoserializer.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>



int main(int argc, char* argv[])
{
    try {
        std::map<std::string, std::unique_ptr<ClInfoSerializer> > serializers;
        serializers.emplace("json", std::unique_ptr<ClInfoSerializer>(
                new JsonClInfoSerializer()));
        serializers.emplace("xml", std::unique_ptr<ClInfoSerializer>(
                new XmlClInfoSerializer()));

        if (argc < 2) {
            throw std::runtime_error("Missing arguments.");
        }
        std::string libraryPath(argv[1]);
        std::string format((argc >= 3) ? argv[2] : "json");

        auto foundSerializer = serializers.find(format);
        if (foundSerializer == serializers.end()) {
            throw std::runtime_error("Unknown format.");
        }
        ClInfoSerializer& serializer = *(foundSerializer->second);
        OpenClBinder openClBinder(libraryPath);
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
    OpenClBinder* binder;
    int err;

    cl_device_id device_id;
    err = binder->clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 1, &device_id,
            nullptr);
    if (err != CL_SUCCESS) {
        throw OpenClException("Failed to create a device group!", err);
    }

    std::unique_ptr<_cl_context, cl_int(*)(cl_context)> context(
            binder->clCreateContext(0, 1, &device_id, nullptr, nullptr, &err),
            binder->clReleaseContext);
    if (!context) {
        throw OpenClException("Failed to create a compute context!", err);
    }

    std::unique_ptr<_cl_command_queue, cl_int(*)(cl_command_queue)> commands(
            binder->clCreateCommandQueue(context.get(), device_id, 0, &err),
            binder->clReleaseCommandQueue);
    if (!commands) {
        throw OpenClException("Failed to create a command commands!", err);
    }

    std::unique_ptr<_cl_program, cl_int(*)(cl_program)> program(
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
}
