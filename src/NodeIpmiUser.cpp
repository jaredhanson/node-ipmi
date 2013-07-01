#include <sstream>
#include "NodeIpmiUser.hpp"
V8_POST_TYPE(NodeIpmiUser);
extern "C" {
#include "ipmitool/ipmi_user.h"
int ipmi_get_user_access(struct ipmi_intf *intf, uint8_t channel_number, uint8_t user_id, struct user_access_rsp *user_access);
int ipmi_get_user_name(struct ipmi_intf *intf, uint8_t user_id, char *user_name);
int ipmi_user_set_username( struct ipmi_intf *intf, uint8_t user_id, const char *name);
}


using namespace node;
using namespace v8;

V8_EGET(NodeIpmiUser, GetName) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    char name[17];
    int rc = ipmi_get_user_name(self->interface, self->id, name);
    if (rc) V8_STHROW(v8u::Err("Error getting User's name"));
    V8_RET(String::New(name));
} V8_GET_END()

V8_EGET(NodeIpmiUser, GetId) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    V8_RET(Integer::New(self->id));
} V8_GET_END()

V8_ESET(NodeIpmiUser, SetName) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    if (!value->IsString() || value->ToString()->Length() < 1 || value->ToString()->Length() > 16) {
        V8_THROW(v8u::Err("value must be a string with length in range [1,16]"));
    }
    String::Utf8Value strval(value->ToString());
    int rc = ipmi_user_set_username(self->interface, self->id, *strval);
    if (rc) V8_THROW(v8u::Err("Error setting User's name"));
} V8_SET_END()
