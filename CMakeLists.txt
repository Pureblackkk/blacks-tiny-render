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

# Set png
set(PNG_DIR /opt/homebrew/Cellar/libpng/1.6.40)
find_package(PNG REQUIRED)

# Inclue directories 
include_directories(include libs ${SDL_DIR}/include/ ${PNG_DIR}/include/)
link_directories(${SDL_DIR}/lib/ ${PNG_DIR}/lib/) 


# Set OpenMP compiler
message(STATUS "set compipler")
set(CMAKE_C_COMPILER "/opt/homebrew/Cellar/llvm/17.0.6/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/llvm/17.0.6/bin/clang++")
set(OPENMP_LIBRARIES "/opt/homebrew/Cellar/llvm/17.0.6/lib")
set(OPENMP_INCLUDES "/opt/homebrew/Cellar/llvm/17.0.6/include")
set(OpenMP_OMP "/opt/homebrew/Cellar/llvm/17.0.6/lib/libomp.dylib") # Set omp position

if(APPLE)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY ${OpenMP_OMP})
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY ${OpenMP_OMP})
    endif()
endif()

# Find OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    message(STATUS "found openmp")
    include_directories("${OPENMP_INCLUDES}")
    link_directories(${OPENMP_LIBRARIES})
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}, ${OPENMP_C_FLAGS})
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(FATAL_ERROR "openmp not found")
endif()

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

# Link SDL2 OpenMp
target_link_libraries(blacks_tiny_render SDL2 PNG OpenMP::OpenMP_CXX)