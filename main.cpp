#include "clinfogatherer.h"

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <cstdlib>
#include <iostream>



int main()
{
    try {
        ClInfoGatherer infoGatherer;
        ClInfo info = infoGatherer.gatherInfo();
        for (const ClPlatformInfo& platformInfo: info.platforms) {
            for (const ClInfoField& infoField: platformInfo.fields) {
                std::cout <<
                        infoField.name << ": " <<
                        infoField.value << '\n';
            }

            for (const ClDeviceInfo& deviceInfo: platformInfo.devices) {
                for (const ClInfoField& infoField: deviceInfo.fields) {
                    std::cout <<
                            infoField.name << ": " <<
                            infoField.value << '\n';
                }
            }
            std::cout << std::endl;
        }

        return EXIT_SUCCESS;
    } catch (const cl::Error& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
}

