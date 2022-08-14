# Set the minimum CMake version
cmake_minimum_required(VERSION 2.8.12)

# Set the project name
project (GLOBAL_STATE)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Add library subdirectory
set(GLOBAL_STATE_INCLUDE_CONTEXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/context)
add_subdirectory(context)
include_directories(${GLOBAL_STATE_INCLUDE_CONTEXT_DIR})

# Add the main file, and name of its executable
add_executable(global_state main.c)

# Link the library to the main file
target_link_libraries(global_state context)