#ifndef NODEIPMIUSER_H
#define NODEIPMIUSER_H
#include "v8u.hpp"
extern "C" {
#include "ipmitool/ipmi_intf.h"
}

using namespace v8;

class NodeIpmiUser : public node::ObjectWrap {
    public:
        NodeIpmiUser(ipmi_intf *interface, int id) : interface(interface), id(id) {}
        V8_SCTOR() { V8_CTOR_NO_JS }
        V8_SGET(GetId);
        V8_SGET(GetName);
        V8_SSET(SetName);
        NODE_TYPE(NodeIpmiUser, "NodeIpmiUser") {
            V8_DEF_GET("id", GetId);
            V8_DEF_ACC("name", GetName, SetName);
        } NODE_TYPE_END()
    private:
        ipmi_intf *interface;
        int id;
};
#endif
