#ifndef ROARM_HH
#define ROARM_HH


class roarm{
    public:
    roarm();
    bool joints_angle_ctrl();
    bool joints_radian_ctrl();
    //Change void to return packets instead, or whatever
    void joints_angle_get();
    void joints_radian_get();


    private:
    //Change void to return packets
    void pose_get();
    void read_line();
    
};

#endif
