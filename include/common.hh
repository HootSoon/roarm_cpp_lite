#ifndef COMMON_HH
#define COMMON_HH
#include <cstdint>

//Command table
enum class JsonCmd : uint16_t {
    JOINT_RADIAN_CTRL            = 101,
    JOINTS_RADIAN_CTRL           = 102,
    FEEDBACK_GET                 = 105,
    DYNAMIC_ADAPTATION_SET       = 112,
    LED_CTRL                     = 114,
    JOINT_ANGLE_CTRL             = 121,
    JOINTS_ANGLE_CTRL            = 122,
    TORQUE_SET                   = 210,
    GRIPPER_MODE_SET             = 222,
    WIFI_ON_BOOT                 = 401,
    AP_SET                       = 402,
    STA_SET                      = 403,
    APSTA_SET                    = 404,
    WIFI_CONFIG_CREATE_BY_STATUS = 406,
    WIFI_CONFIG_CREATE_BY_INPUT  = 407,
    WIFI_STOP                    = 408,
    MIDDLE_SET                   = 502,
    ECHO_SET                     = 605,
    POSE_CTRL                    = 1041
};

#endif