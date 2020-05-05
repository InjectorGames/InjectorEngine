
project(asio LANGUAGES CXX)

add_library(asio INTERFACE)

target_include_directories(asio INTERFACE
    ${PROJECT_SOURCE_DIR}/3rdparty/asio/asio/include
)