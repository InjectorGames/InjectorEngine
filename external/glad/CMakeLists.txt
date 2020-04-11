cmake_minimum_required (VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there.")
endif()

project (glad VERSION 0.1.33 LANGUAGES C)

add_library(glad_debug STATIC src/glad_debug.c)
target_include_directories(glad_debug PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(glad_release STATIC src/glad_release.c)
target_include_directories(glad_release PUBLIC ${PROJECT_SOURCE_DIR}/include)
