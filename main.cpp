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
