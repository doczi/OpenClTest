add_library (OpenClTest SHARED
    clinfo.cpp
    clinfogatherer.cpp
    openclbinder.cpp
    openclwrapper.cpp)
target_link_libraries(OpenClTest dl)

