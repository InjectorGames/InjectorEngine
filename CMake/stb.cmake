project(stb LANGUAGES CXX)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
    ${PROJECT_SOURCE_DIR}/Libraries/stb)
