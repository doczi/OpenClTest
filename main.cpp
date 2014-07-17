#include "clinfogatherer.h"
#include "jsonclinfoserializer.h"

#include <cstdlib>
#include <exception>
#include <iostream>



int main()
{
    try {
        ClInfoGatherer infoGatherer;
        ClInfo info = infoGatherer.gatherInfo();
        JsonClInfoSerializer infoSerializer;
        std::cout << infoSerializer.serialize(info) << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

