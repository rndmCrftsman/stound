cmake_minimum_required(VERSION 3.26.0)

project(stound VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(stound main/src/main.cpp)

target_include_directories(
    stound
    PRIVATE
       main/inc
)

find_package(portaudio)

target_link_libraries(
    stound
    PRIVATE
        portaudio
)