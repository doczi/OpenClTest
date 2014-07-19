cmake_minimum_required (VERSION 2.6)
project (OpenClTest)

include_directories(
    ${OpenClTest_SOURCE_DIR}/include
    ${OpenClTest_SOURCE_DIR}/src/OpenClTestLib)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)

