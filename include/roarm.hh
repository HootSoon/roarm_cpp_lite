#pragma once
#include <vector>
#include <string>
#include <atomic>
#include <thread>
#include <unistd.h>
#include "serial/serial.h" // Serial library for arm communication
#include "common.hh"

class roarm{
    public:

    roarm(std::string port = "/dev/ttyUSB0", int baudrate = 115200);
    ~roarm();

    void clean_up();

    bool init();
    bool joints_angle_ctrl(std::vector<double> angles, int speed, int acc);
    bool joints_radian_ctrl(std::vector<double> radians, int speed, int acc);

    //Change short to return packets instead, or whatever, might work
    std::vector<double> joints_angle_get();
    std::vector<double> joints_radian_get();
    std::vector<double> pose_get();

    std::string read_line();
    bool send_command(const std::string& message);
    
    //Roarm Pose at last poll
    ThreadSafeVector pose;

    //Start threaded reading and saving of arm state
    void poll_pose();


    private:
    serial::Serial armCom;
    void get_feedback();

    std::thread pollingThread;
    std::atomic<bool> threadCondition{false};

    
};

