#include "roarm.hh"
#include <unistd.h>
#include <iostream>


int main(){
    roarm arm("/dev/ttyUSB0", 115200);
    usleep(5000000);
    arm.init();
    while(true){
        std::cout << arm.read_line() << std::endl;
        usleep(100000);
    }
    
}