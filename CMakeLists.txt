cmake_minimum_required (VERSION 3.1)
project(blacks_tiny_render)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Support arm architecture
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

# Inclue directories 
include_directories(include libs)

# Source files
file(GLOB SOURCES
    "*.h"
    "*.cpp"
    "include/*.h"
    "libs/*.h"
    "libs/*.cpp"
    "src/*.cpp"
)
# Add the executable
add_executable(blacks_tiny_render ${SOURCES})