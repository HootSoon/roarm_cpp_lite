#include "roarm.hh"
#include "common.hh"

roarm::roarm(std::string port, int baudrate ) : armCom(port, baudrate,serial::Timeout::simpleTimeout(1000)) {
    
}

bool roarm::init(){
    return send_command(JsonCmd::MOVE_INIT);
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
    return armCom.readline();
}


