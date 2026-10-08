#include "roarm.hh"
#include "common.hh"

roarm::roarm(String port, int baudrate ) : (armCom(port, baudrate,serial::Timeout::simpleTimeout(1000)) ) {

}

bool roarm::joints_angle_ctrl(std::vector<short> angles, int speed, int acc){
    
    return 1;
}

bool roarm::joints_radian_ctrl(std::vector<short> radians, int speed, int acc){

    return 1;
}       

std::vector<short> roarm::pose_get(){

}

bool roarm::send_command(String message){
    if(armCom.isOpen()){
        armCom.write(message);
    }
}

void roarm::read_line(){

}


