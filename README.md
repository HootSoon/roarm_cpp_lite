# roarm_cpp_lite

**A lightweight C++ library for controlling the Waveshare RoArm M3 over serial.**

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.18%2B-064F8C?logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue)](LICENSE)

`roarm_cpp_lite` provides a small C++ interface to the arm's JSON command protocol.
It focuses on serial communication and joint control, with a familiar API inspired
by the [Waveshare RoArm SDK](https://github.com/waveshareteam/waveshare_roarm_sdk).

Link it into an existing C++ application, create a controller, and send commands
directly—without a Python runtime or ROS.

[Getting started](#getting-started) · [Usage](#usage) · [API](#api-at-a-glance) · [Build](#build-the-library)

---

## What it provides

- **Joint control** in degrees or radians.
- **Serial communication** with configurable port and baud rate.
- **Raw JSON commands** for accessing firmware features directly.
- **CMake integration** that brings in the serial dependency automatically.

The current implementation uses the six-joint RoArm M3 command format and a Linux
serial backend. This is an independent project, with a smaller feature set than
the official SDK.

## Getting started

You need **Linux**, a **C++17 compiler**, **CMake 3.18 or newer**, and **Git**.
An internet connection is needed on the first configure to download dependencies.

In your application's `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.18)
project(robot_app LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(roarm_cpp_lite
    GIT_REPOSITORY https://github.com/HootSoon/roarm_cpp_lite.git
    GIT_TAG main
)
FetchContent_MakeAvailable(roarm_cpp_lite)

add_executable(robot_app main.cpp)
target_link_libraries(robot_app PRIVATE roarm_cpp_lite)
```

CMake supplies the library's headers, serial backend, and thread dependencies.
For reproducible builds, replace `main` with a specific commit SHA.

If you already have a checkout inside your project, use this instead:

```cmake
add_subdirectory(external/roarm_cpp_lite)
target_link_libraries(robot_app PRIVATE roarm_cpp_lite)
```

Replace `robot_app` with your application's executable target name.

## Usage

### Connect and request feedback

This example opens the serial connection and prints raw feedback without sending
a motion command:

```cpp
#include "roarm.hh"

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

int main() {
    try {
        roarm arm("/dev/ttyUSB0", 115200);

        // Allow the controller to boot if opening serial resets it.
        std::this_thread::sleep_for(std::chrono::seconds(3));

        if (!arm.send_command("{\"T\":105}\n")) {
            std::cerr << "Could not send feedback request.\n";
            return 1;
        }

        for (int i = 0; i < 100; ++i) {
            const auto response = arm.read_line();
            if (!response.empty()) {
                std::cout << response;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (const std::exception& error) {
        std::cerr << "RoArm: " << error.what() << '\n';
        return 1;
    }
}
```

The defaults are `/dev/ttyUSB0` and `115200` baud. Change them to match your
connection. Construction opens the port; it does not call `init()`.

### Control the joints

Pass six joint values in this order:

| Index | Joint |
| :---: | --- |
| 0 | Base |
| 1 | Shoulder |
| 2 | Elbow |
| 3 | Wrist bend |
| 4 | Wrist roll |
| 5 | Hand / gripper |

With a connected controller, a movement command looks like this:

```cpp
// Degrees: joints, speed, acceleration
arm.joints_angle_ctrl({0, 0, 90, 0, 0, 180}, 10, 10);

// Radians: joints, speed, acceleration
arm.joints_radian_ctrl({0, 0, 1.5708, 0, 0, 3.1416}, 10, 10);
```

These commands move the arm. Choose joint values appropriate for your hardware
and workspace. Speed and acceleration are passed through to the firmware.

A successful return means the command bytes were written; it does not confirm
that the arm reached its target.

## API at a glance

| Method | Purpose |
| --- | --- |
| `roarm(port, baudrate)` | Open a serial connection |
| `joints_angle_ctrl(angles, speed, acc)` | Send six joint positions in degrees |
| `joints_radian_ctrl(radians, speed, acc)` | Send six joint positions in radians |
| `send_command(message)` | Write a raw command string; include its terminating newline |
| `read_line()` | Read a serial line, or return an empty string when no data is available |
| `init()` | Enable torque and command the initial joint position |
| `poll_pose()` | Start the experimental background feedback reader |
| `pose_get()` | Retrieve the latest cached values from that reader |
| `clean_up()` | Stop and join the background reader |

**`init()` moves the arm** to `{0, 0, 90, 0, 0, 180}` degrees. It is not
required simply to open the serial connection.

The destructor calls `clean_up()`; the serial connection is then released
with the controller object.

### Current limitations

- Background feedback parsing is experimental: empty or malformed input can
  cause an unhandled exception in the reader. Use raw `read_line()` for initial
  feedback work, and do not use it concurrently with `poll_pose()`.
- `joints_angle_get()` and `joints_radian_get()` are declared in the header but
  do not yet have implementations.
- Joint-limit validation, motion planning, and collision avoidance must be
  handled by the calling application.

## Build the library

To compile the library on its own:

```bash
git clone https://github.com/HootSoon/roarm_cpp_lite.git
cd roarm_cpp_lite

cmake -S . -B build
cmake --build build -j
```

This builds `libroarm_cpp_lite.a` and its serial backend as static libraries.
It does not build an executable or move connected hardware.

## Dependencies and license

Serial communication uses [wjwwood/serial](https://github.com/wjwwood/serial),
which CMake downloads at a pinned commit and builds directly using its Linux
sources.

This project is licensed under **Apache-2.0**. See [LICENSE](LICENSE).
The serial dependency is licensed separately under MIT.
