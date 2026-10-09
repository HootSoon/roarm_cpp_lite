cmake_minimum_required(VERSION 3.18)
project(roarm_cpp_lite LANGUAGES CXX)

include(FetchContent)
find_package(Threads REQUIRED)

# Download serial without running its ROS/catkin CMake build.
FetchContent_Declare(roarm_serial
    GIT_REPOSITORY https://github.com/wjwwood/serial.git
    GIT_TAG 69e0372cf0d3796e84ce9a09aff1d74496f68720
    SOURCE_SUBDIR unused
)
FetchContent_MakeAvailable(roarm_serial)

add_library(roarm_serial_backend STATIC
    ${roarm_serial_SOURCE_DIR}/src/serial.cc
    ${roarm_serial_SOURCE_DIR}/src/impl/unix.cc
    ${roarm_serial_SOURCE_DIR}/src/impl/list_ports/list_ports_linux.cc
)
target_include_directories(roarm_serial_backend PUBLIC
    ${roarm_serial_SOURCE_DIR}/include
)
target_link_libraries(roarm_serial_backend PUBLIC Threads::Threads rt)

add_library(roarm_cpp_lite STATIC
    src/common.cpp
    src/roarm.cpp
)
target_compile_features(roarm_cpp_lite PUBLIC cxx_std_17)
target_include_directories(roarm_cpp_lite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(roarm_cpp_lite PUBLIC roarm_serial_backend)