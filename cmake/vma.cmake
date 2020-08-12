project(vma LANGUAGES CXX)

add_library(vma INTERFACE)

target_include_directories(vma INTERFACE
    ${PROJECT_SOURCE_DIR}/3rdparty/vma/src
)
