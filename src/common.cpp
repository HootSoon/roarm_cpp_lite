#include "common.hh"
#include <sstream>

std::string handle_message_format(const std::vector<double>& values, JsonCmd commandID) {
    std::ostringstream msg;
    uint16_t id = static_cast<uint16_t>(commandID); // Cast to int to use in message

    switch (commandID) {
        // Joints radian ctrl (102)
        // {"T":102,"base":0,"shoulder":0,"elbow":1.57,"wrist":0,"roll":0,"hand":1.57,"spd":0,"acc":10}
        case (JsonCmd::JOINTS_RADIAN_CTRL):
            if (values.size() >= 8) {
                msg << "{\"T\":" << id << ","
                    << "\"base\":" << values[0] << ","
                    << "\"shoulder\":" << values[1] << ","
                    << "\"elbow\":" << values[2] << ","
                    << "\"wrist\":" << values[3] << ","
                    << "\"roll\":" << values[4] << ","
                    << "\"hand\":" << values[5] << ","
                    << "\"spd\":" << values[6] << ","
                    << "\"acc\":" << values[7]
                    << "}\n";
            }
            break;

        // Joints angle ctrl (122)
        // {"T":122,"b":0,"s":0,"e":90,"t":0,"r":0,"h":180,"spd":10,"acc":10}
        case (JsonCmd::JOINTS_ANGLE_CTRL):
            if (values.size() >= 8) {
                msg << "{\"T\":" << id << ","
                    << "\"b\":" << values[0] << ","
                    << "\"s\":" << values[1] << ","
                    << "\"e\":" << values[2] << ","
                    << "\"t\":" << values[3] << ","
                    << "\"r\":" << values[4] << ","
                    << "\"h\":" << values[5] << ","
                    << "\"spd\":" << values[6] << ","
                    << "\"acc\":" << values[7]
                    << "}\n";
            }
            break;

        // Light ctrl (114)
        // {"T":114,"led":255}
        case (JsonCmd::LED_CTRL):
            if (!values.empty()) {
                msg << "{\"T\":" << id << ","
                    << "\"led\":" << static_cast<int>(values[0])
                    << "}\n";
            }
            break;

        default:
            break;
    }

    return msg.str();
}