#include "clinfogatherer.h"
#include "jsonclinfoserializer.h"
#include "openclwrapper.h"
#include <cstdlib>
#include <exception>
#include <iostream>



int main()
{
    try {
        OpenClWrapper openClWrapper("/opt/AMDAPP/lib/x86_64/libOpenCL.so");
        ClInfoGatherer infoGatherer(openClWrapper);
        ClInfo info = infoGatherer.gatherInfo();
        JsonClInfoSerializer infoSerializer;
        std::cout << infoSerializer.serialize(info) << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

