add_library (OpenClTest SHARED
    clinfo.cpp
    openclbinder.cpp
    opencltester.cpp
    openclwrapper.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(OpenClTest dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
