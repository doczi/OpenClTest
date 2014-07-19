add_library (OpenClTest SHARED
    clinfo.cpp
    clinfogatherer.cpp
    openclbinder.cpp
    openclwrapper.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(OpenClTest dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
