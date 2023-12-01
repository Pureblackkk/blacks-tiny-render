cmake_minimum_required (VERSION 3.1)
project(blacks_tiny_render)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Support arm architecture
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Set SDL2
set(SDL_DIR /opt/homebrew/Cellar/sdl2/2.28.5)
find_package(SDL2 REQUIRED)

# Inclue directories 
include_directories(include libs ${SDL_DIR}/include/)

link_directories(${SDL_DIR}/lib/)

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

# Link SDL2
target_link_libraries(blacks_tiny_render SDL2)