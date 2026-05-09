cmake_minimum_required(VERSION 3.14)
project(app CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.3
)
FetchContent_MakeAvailable(httplib)

FetchContent_Declare(
    boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)

add_executable(app
    src/main.cpp
    src/config.cpp
    src/scanner.cpp
)

target_include_directories(app PRIVATE inc)

target_link_libraries(app PRIVATE nlohmann_json::nlohmann_json httplib::httplib Boost::program_options)
