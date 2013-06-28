#ifndef NODEIPMIUSER_H
#define NODEIPMIUSER_H
#include "v8u.hpp"
extern "C" {
#include "ipmitool/ipmi_intf.h"
}

using namespace v8;

class NodeIpmiUser : public node::ObjectWrap {
    public:
        NodeIpmiUser(ipmi_intf *interface);
        V8_SCTOR() { V8_CTOR_NO_JS }
        V8_SGET(GetList);
        NODE_TYPE(NodeIpmiUser, "NodeIpmiUser") {
            V8_DEF_GET("list", GetList);
        } NODE_TYPE_END()
    private:
        ipmi_intf *interface;
};
#endif
