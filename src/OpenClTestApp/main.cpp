#include "clinfogatherer.h"
#include "jsonserializer.h"
#include "openclbinder.h"
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
        ClInfoGatherer infoGatherer(openClBinder);
        ClInfo info = infoGatherer.gatherInfo();
        std::cout << serializer.serialize(info) << std::endl;
        std::cout << "COMPILATION TEST:" << std::endl;
        std::cout << infoGatherer.testCompilation() << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: OpenClTest <library path> [format]" << std::endl;
        return EXIT_FAILURE;
    }
}
