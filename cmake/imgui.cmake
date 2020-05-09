
project(imgui LANGUAGES CXX)

file(GLOB IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui/*.cpp
)

add_library(imgui STATIC
    ${IMGUI_SOURCES}
)

target_include_directories(imgui PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui
)