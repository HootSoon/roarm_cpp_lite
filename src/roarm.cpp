#include "roarm.hh"
#include "common.hh"
#include <iostream>


roarm::roarm(std::string port, int baudrate ) : armCom(port, baudrate,serial::Timeout::simpleTimeout(1000)) {
    //std::cout << "Roarm Created" << std::endl; // Debug Print

}

roarm::~roarm(){}

bool roarm::init(){
    std::cout << "Init Command Send" << std::endl;

    std::string message = handle_message_format({0,0,90,0,0,180,10,10},JsonCmd::JOINTS_ANGLE_CTRL);
    return send_command(message);
} 

bool roarm::joints_angle_ctrl(std::vector<double> angles, int speed, int acc){
    angles.push_back(speed);
    angles.push_back(acc);
    std::string message = handle_message_format(angles,JsonCmd::JOINTS_ANGLE_CTRL);
    return send_command(message);
}

bool roarm::joints_radian_ctrl(std::vector<double> radians, int speed, int acc){
    radians.push_back(speed);
    radians.push_back(acc);
    std::string message = handle_message_format(radians,JsonCmd::JOINTS_RADIAN_CTRL);
    return send_command(message);
}       

std::vector<double> roarm::pose_get(){
    return {0.1,0.2};
}

bool roarm::send_command(std::string message){
    if(armCom.isOpen()){
        return armCom.write(message) == message.size();
    }
    return false;
}


std::string roarm::read_line(){
    if(armCom.available()>0){
        return armCom.readline();
    }
}

bool roarm::get_feedback(){
    while(threadCondition){
        pose = convert_string_vector_to_double_vector(unpack_feedback_message(read_line()));
    }
}

void roarm::poll_pose(){
    //Start threading of get_feedback
    pollingThread(get_feedback());
}

roarm::clean_up(){
    threadCondition = false;
    if(pollingThread.joinable()){
        pollingThread.join();
    }
    ~roarm();
}

