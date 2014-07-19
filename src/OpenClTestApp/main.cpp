#include "jsonserializer.h"
#include "openclbinder.h"
#include "opencltester.h"
#include "xmlserializer.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>



/*
 * I copied this kernel from here:
 * https://developer.apple.com/library/mac/samplecode/OpenCL_Hello_World_Example/Introduction/Intro.html
 */
const char *KERNEL_SOURCE = "\n"
        "__kernel void square(                   \n"
        "   __global float* input,               \n"
        "   __global float* output,              \n"
        "   const unsigned int count)            \n"
        "{                                       \n"
        "   int i = get_global_id(0);            \n"
        "   if(i < count)                        \n"
        "       output[i] = input[i] * input[i]; \n"
        "}                                       \n"
        "\n";



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
        OpenClTester infoGatherer(openClBinder);
        ClInfo info = infoGatherer.gatherInfo();
        std::cout << serializer.serialize(info) << std::endl;
        std::cout << "COMPILATION TEST:" << std::endl;
        std::cout << KERNEL_SOURCE << std::endl;
        std::cout << infoGatherer.testCompilation(KERNEL_SOURCE) << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: OpenClTest <library path> [format]" << std::endl;
        return EXIT_FAILURE;
    }
}
