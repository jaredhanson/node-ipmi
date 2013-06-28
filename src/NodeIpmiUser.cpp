#include <sstream>
#include "NodeIpmiUser.hpp"
V8_POST_TYPE(NodeIpmiUser);

using namespace node;
using namespace v8;

NodeIpmiUser::NodeIpmiUser(ipmi_intf *interface) {
    this->interface = interface;
}

V8_EGET(NodeIpmiUser, GetList) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    std::stringstream msg;
    msg << "NodeIpmiUser::GetList" << " is not yet implemented.";
    //V8_STHROW(v8u::Err(msg.str().c_str()));
    V8_RET(String::New(msg.str().c_str()));
} V8_GET_END()
