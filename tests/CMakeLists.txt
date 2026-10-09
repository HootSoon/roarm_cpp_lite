cmake_minimum_required(VERSION 3.16)
project(roarm_cpp_lite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------------------
# 1. Fetch and compile wjwwood/serial automatically
# -------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    serial
    GIT_REPOSITORY https://github.com/wjwwood/serial.git
    GIT_TAG        main
)

FetchContent_GetProperties(serial)
if(NOT serial_POPULATED)
    FetchContent_Populate(serial)

    # Build only the raw Linux/Unix serial files without ROS
    add_library(serial STATIC
        ${serial_SOURCE_DIR}/src/serial.cc
        ${serial_SOURCE_DIR}/src/impl/unix.cc
        ${serial_SOURCE_DIR}/src/impl/list_ports/list_ports_linux.cc
    )

    target_include_directories(serial PUBLIC
        ${serial_SOURCE_DIR}/include
    )

    find_package(Threads REQUIRED)
    target_link_libraries(serial PUBLIC Threads::Threads rt)
endif()

# -------------------------------------------------------------
# 2. Build your roarm_cpp_lite library
# -------------------------------------------------------------
add_library(roarm_cpp_lite
    ../src/common.cpp
    ../src/roarm.cpp
)

target_include_directories(roarm_cpp_lite PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

# Link your internal static serial library
target_link_libraries(roarm_cpp_lite PUBLIC serial)

# -------------------------------------------------------------
# 3. Build test executable
# -------------------------------------------------------------
add_executable(test_roarm main.cpp)
target_link_libraries(test_roarm PRIVATE roarm_cpp_lite)