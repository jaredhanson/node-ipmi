#include <sstream>
#include "NodeIpmiPower.hpp"
extern "C" {
#include "ipmitool/ipmi_chassis.h"
}
V8_POST_TYPE(NodeIpmiPower);

using namespace node;
using namespace v8;

NodeIpmiPower::NodeIpmiPower(ipmi_intf *interface) {
    this->interface = interface;
}

V8_EGET(NodeIpmiPower, GetStatus) {
    NodeIpmiPower *self = Unwrap(info.Holder());
    int chassis_status = ipmi_chassis_power_status(self->interface);
    switch (chassis_status) {
        case 0:
            V8_RET(String::New("off"));
            break;
        case 1:
            V8_RET(String::New("on"));
            break;
        case -1: // indicates failure
        default:
            std::stringstream msg;
            msg << "call failed: " << "getstatus";
            V8_STHROW(v8u::Err(msg.str().c_str()));
    }
} V8_GET_END()

V8_CB(NodeIpmiPower::On) {
    NodeIpmiPower *self = Unwrap(args.This());
    int rc = ipmi_chassis_power_control(self->interface, IPMI_CHASSIS_CTL_POWER_UP);
    V8_RET(Integer::New(rc));
} V8_CB_END()

V8_CB(NodeIpmiPower::Off) {
    NodeIpmiPower *self = Unwrap(args.This());
    int rc = ipmi_chassis_power_control(self->interface, IPMI_CHASSIS_CTL_POWER_DOWN);
    V8_RET(Integer::New(rc));
} V8_CB_END()
