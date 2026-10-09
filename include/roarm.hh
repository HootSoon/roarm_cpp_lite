#pragma once
#include <vector>
#include <string>
#include "serial/serial.h" // Serial library for arm communication

class roarm{
    public:

    //baudrate=115200, host=None, timeout=0.1, debug=False, thread_lock=True, gripper_type="angular_direct"

    roarm(std::string port = "/dev/ttyUSB0", int baudrate = 115200);
    bool joints_angle_ctrl(std::vector<double> angles, int speed, int acc);
    bool joints_radian_ctrl(std::vector<double> radians, int speed, int acc);
    bool init();

    //Change short to return packets instead, or whatever, might work
    std::vector<double> joints_angle_get();
    std::vector<double> joints_radian_get();

    std::string read_line();
    bool send_command(std::string message);


    private:
    serial::Serial armCom;
    std::vector<double> pose_get();
    
};

