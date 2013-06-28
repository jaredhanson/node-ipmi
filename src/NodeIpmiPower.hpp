#ifndef NODEIPMIPOWER_H
#define NODEIPMIPOWER_H
#include "v8u.hpp"
extern "C" {
#include "ipmitool/ipmi_intf.h"
}

using namespace v8;

class NodeIpmiPower : public node::ObjectWrap {
    public:
        NodeIpmiPower(ipmi_intf *interface);
        V8_SCTOR() { V8_CTOR_NO_JS }
        static V8_SCB(On);
        static V8_SCB(Off);
        V8_SGET(GetStatus);
        NODE_TYPE(NodeIpmiPower, "NodeIpmiPower") {
            V8_DEF_CB("on", On);
            V8_DEF_CB("off", Off);
            V8_DEF_GET("status", GetStatus);
        } NODE_TYPE_END()
    private:
        ipmi_intf *interface;
};
#endif
