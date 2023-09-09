cmake_minimum_required(VERSION 3.26.0)

project(stound VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(JUCE_BUILD_EXTRAS OFF)
set(JUCE_BUILD_EXAMPLES OFF)
set(JUCE_MODULES_ONLY ON)

add_subdirectory(external/JUCE)

file(GLOB_RECURSE main_sources main/src/*.cpp)
file(GLOB_RECURSE main_includes main/inc/*.h)

add_executable(stound ${main_sources})

target_include_directories(
    stound
    PRIVATE 
        ${main_includes}
        external/JUCE/modules/juca_audio_basics
        external/JUCE/modules/juca_audio_devices
        external/JUCE/modules/juca_core
)

target_link_libraries(
    stound
    PRIVATE
        juce_audio_basics
        juce_audio_devices
        juce_core
        
        ## Folloing are Windows Libraries to compile the juce modules
        winmm # For Multimedia functions
        ole32  # For COM functions
        wininet  # For WinINet functions
        version  # For GetFileVersionInfoW and VerQueryValueW
        ws2_32  # For setsockopt
        Shlwapi  # For PathStripToRootW
        ## END WINDOWS LIBS
)