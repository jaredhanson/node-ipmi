#include <sstream>
#include "NodeIpmiUser.hpp"
V8_POST_TYPE(NodeIpmiUser);
extern "C" {
#include "ipmitool/ipmi_user.h"
int ipmi_get_user_access(struct ipmi_intf *intf, uint8_t channel_number, uint8_t user_id, struct user_access_rsp *user_access);
int ipmi_get_user_name(struct ipmi_intf *intf, uint8_t user_id, char *user_name);
}


using namespace node;
using namespace v8;

NodeIpmiUser::NodeIpmiUser(ipmi_intf *interface) {
    this->interface = interface;
}

V8_EGET(NodeIpmiUser, GetList) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    struct user_access_rsp access;
    int rc = ipmi_get_user_access(self->interface, 0xE, 1, &access);
    char name[17];
    rc = ipmi_get_user_name(self->interface, 2, name);

    //Handle<Object> user = Object::New();
    //h_version->Set(v8u::Symbol("name"), String::New(version->build_date));
    //h_version->Set(v8u::Symbol("scm_revision"), String::New(version->scm_revision));

    //std::stringstream msg;
    //msg << "NodeIpmiUser::GetList" << " is not yet implemented.";
    //V8_RET(Integer::New(rc));

    V8_RET(String::New(name));
} V8_GET_END()
