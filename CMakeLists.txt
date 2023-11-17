cmake_minimum_required (VERSION 3.1)
project(blacks_tiny_render)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# inclue directories 
include_directories(include libs)

# Source files
file(GLOB SOURCES "*.h" "*.cpp" "src/*.cpp" "include/*.h" "libs/*.h" "libs/*.cpp")

# Add the executable
add_executable(blacks_tiny_render ${SOURCES})