#ifndef ROARM_HH
#define ROARM_HH
#include <vector>
#include <string>
#include "serial/serial.h" // Serial library for arm communication

class roarm{
    public:

    //baudrate=115200, host=None, timeout=0.1, debug=False, thread_lock=True, gripper_type="angular_direct"

    roarm(std::string port = "/dev/ttyUSB0", int baudrate = 115200);
    bool joints_angle_ctrl(std::vector angles, int speed, int acc);
    bool joints_radian_ctrl(std::vector radians, int speed, int acc);
    bool init();

    //Change short to return packets instead, or whatever, might work
    std::vector<short> joints_angle_get();
    std::vector<short> joints_radian_get();


    private:
    serial::Serial armCom;
    std::vector<short> pose_get();
    void read_line();
    bool send_command(std::string message);
    
};

#endif
