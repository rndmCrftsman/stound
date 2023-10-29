cmake_minimum_required(VERSION 3.26.0)

project(stound VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(miniaudio REQUIRED)
find_package(drwav REQUIRED)
find_package(drmp3 REQUIRED)
find_package(drflac REQUIRED)
find_package(Ogg REQUIRED)
find_package(Vorbis REQUIRED)


add_executable(stound 
    main/src/miniaudio_impl.cpp
    main/src/dr_libs_impl.cpp
    main/src/main.cpp
    bindings/imgui_impl_glfw.h
    bindings/imgui_impl_glfw.cpp
    bindings/imgui_impl_opengl3.h
    bindings/imgui_impl_opengl3.cpp
)

target_include_directories(
    stound
    PRIVATE
        main/inc
        bindings
)

# target_compile_definitions(stound PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(
    stound
    PRIVATE
        imgui::imgui
        glfw::glfw
        GLEW::GLEW
        miniaudio::miniaudio
        drwav::drwav
        drmp3::drmp3
        drflac::drflac
        Ogg::ogg
        Vorbis::vorbis
)