#include "roarm.hh"
#include <unistd.h>

int main(){
    roarm::roarm arm(std::string port = "/dev/ttyUSB0", int baudrate = 115200);
    usleep(5000000);
    arm.init();
}