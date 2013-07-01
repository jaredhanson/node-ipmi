#include <sstream>
#include "NodeIpmiUser.hpp"
V8_POST_TYPE(NodeIpmiUser);
extern "C" {
#include "lanplus.h"
#include "ipmitool/ipmi_user.h"
// XXX from ipmi_user.c (not in its header file)
#define IPMI_PASSWORD_DISABLE_USER  0x00
#define IPMI_PASSWORD_ENABLE_USER   0x01
#define IPMI_PASSWORD_SET_PASSWORD  0x02
#define IPMI_PASSWORD_TEST_PASSWORD 0x03
int ipmi_get_user_access(struct ipmi_intf *intf, uint8_t channel_number, uint8_t user_id, struct user_access_rsp *user_access);
int ipmi_get_user_name(struct ipmi_intf *intf, uint8_t user_id, char *user_name);
int ipmi_user_set_username( struct ipmi_intf *intf, uint8_t user_id, const char *name);
int ipmi_user_set_password( struct ipmi_intf * intf, uint8_t user_id, uint8_t operation, const char *password, int is_twenty_byte_password);
int ipmi_user_set_userpriv(struct ipmi_intf *intf, uint8_t channel, uint8_t user_id, const unsigned char privLevel);
}


using namespace node;
using namespace v8;

V8_EGET(NodeIpmiUser, GetName) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    char name[17];
    int rc = ipmi_get_user_name(self->interface, self->id, name);
    if (rc) V8_STHROW(v8u::Err("Error getting user's name"));
    V8_RET(String::New(name));
} V8_GET_END()

V8_EGET(NodeIpmiUser, GetId) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    V8_RET(Integer::New(self->id));
} V8_GET_END()

V8_ESET(NodeIpmiUser, SetName) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    // XXX 16 should be a const
    if (!value->IsString() || value->ToString()->Length() < 1 || value->ToString()->Length() > 16) {
        V8_THROW(v8u::Err("Value must be a string with length within the range of [1,16]"));
    }
    String::Utf8Value strval(value->ToString());
    int rc = ipmi_user_set_username(self->interface, self->id, *strval);
    if (rc) V8_THROW(v8u::Err("Error setting user's name"));
} V8_SET_END()

V8_EGET(NodeIpmiUser, GetPassword) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    V8_RET(String::New("<Not Implemented>"));
} V8_GET_END()

V8_ESET(NodeIpmiUser, SetPassword) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    // XXX 20 should be a const
    if (!value->IsString() || value->ToString()->Length() < 1 || value->ToString()->Length() > 20) {
        V8_THROW(v8u::Err("Value must be a string with length within the range of [1,20]"));
    }
    String::Utf8Value strval(value->ToString());
    // XXX 16 should be a different const (silly extern function signature, really)
    int rc = ipmi_user_set_password(self->interface, self->id, IPMI_PASSWORD_SET_PASSWORD, *strval, strlen(*strval) > 16);
    if (rc) V8_THROW(v8u::Err("Error setting user's password"));
} V8_SET_END()

V8_EGET(NodeIpmiUser, GetEnabled) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    V8_RET(String::New("<Not Implemented>"));
} V8_GET_END()

V8_ESET(NodeIpmiUser, SetEnabled) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    if (!value->IsBoolean()) {
        V8_THROW(v8u::Err("Value must be boolean"));
    }
    int op = value->ToBoolean()->Value() ? IPMI_PASSWORD_ENABLE_USER : IPMI_PASSWORD_DISABLE_USER;
    int rc = ipmi_user_set_password(self->interface, self->id, op, NULL, false);
    if (rc) {
        V8_THROW(v8u::Err("Error enabling or disabling user"));
    }
} V8_SET_END()

V8_EGET(NodeIpmiUser, GetPrivilegeLevel) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    V8_RET(String::New("<Not Implemented>"));
} V8_GET_END()

V8_ESET(NodeIpmiUser, SetPrivilegeLevel) {
    NodeIpmiUser *self = Unwrap(info.Holder());
    if (!value->IsUint32() || value->ToUint32()->Value() > 0x0f) {
        V8_THROW(v8u::Err("Value must be an integer within the range of [0,15]"));
    }
    int rc = ipmi_user_set_userpriv(self->interface, IPMI_LAN_CHANNEL_E, self->id, value->ToUint32()->Value());
    if (rc) {
        V8_THROW(v8u::Err("Error setting user's privilege level"));
    }
} V8_SET_END()
