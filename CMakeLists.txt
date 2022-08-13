cmake_minimum_required(VERSION 2.8.9)
project (GLOBAL_STATE)

set(CMAKE_BUILD_TYPE Debug)

set(GLOBAL_STATE_INCLUDE_MODELS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/context)
add_subdirectory(context)
include_directories(${GLOBAL_STATE_INCLUDE_CONTEXT_DIR})

add_executable(global_state main.c)

target_link_libraries(global_state context)