#include <sstream>
#include "node_ipmi.hpp"
extern "C" {
#include "ipmitool/ipmi_chassis.h"
}

using namespace node;
using namespace v8;

// some globals needed by ipmitool
int verbose = 0;
int csv_output = 0;

NodeIpmi::NodeIpmi(const char *interface_name) {
    interface = ipmi_intf_load((char *)interface_name);

    if (interface == NULL) {
        std::stringstream msg;
        msg << "Error loading interface named \"" << interface_name << "\"";
        V8_THROW(v8u::Err(msg.str().c_str()));
    }
    power = new NodeIpmiPower(interface);
}

NodeIpmi::~NodeIpmi() {
    delete power;
    interface->close(interface);
}

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

V8_EGET(NodeIpmi, GetPower) {
    NodeIpmi* self = Unwrap(info.Holder());
    V8_RET(self->power->Wrapped());
} V8_GET_END()

V8_EGET(NodeIpmi, GetHostname) {
    NodeIpmi* self = Unwrap(info.Holder());
    V8_RET(String::New((const char *)self->interface->session->hostname));
} V8_GET_END()

V8_ESET(NodeIpmi, SetHostname) {
    if (!value->IsString()) {
        V8_THROW(v8u::Err("hostname must be a string"));
    }

    NodeIpmi* self = Unwrap(info.Holder());
    String::Utf8Value strval(value->ToString());
    ipmi_intf_session_set_hostname(self->interface, *strval);
} V8_SET_END()

V8_EGET(NodeIpmi, GetUsername) {
    NodeIpmi* self = Unwrap(info.Holder());
    V8_RET(String::New((const char *)self->interface->session->username));
} V8_GET_END()

V8_ESET(NodeIpmi, SetUsername) {
    if (!value->IsString()) {
        V8_THROW(v8u::Err("username must be a string"));
    }

    NodeIpmi* self = Unwrap(info.Holder());
    String::Utf8Value strval(value->ToString());
    ipmi_intf_session_set_username(self->interface, *strval);
} V8_SET_END()

V8_EGET(NodeIpmi, GetPassword) {
    NodeIpmi* self = Unwrap(info.Holder());
    V8_RET(String::New((const char *)self->interface->session->authcode));
} V8_GET_END()

V8_ESET(NodeIpmi, SetPassword) {
    if (!value->IsString()) {
        V8_THROW(v8u::Err("password must be a string"));
    }

    NodeIpmi* self = Unwrap(info.Holder());
    String::Utf8Value strval(value->ToString());
    ipmi_intf_session_set_password(self->interface, *strval);
} V8_SET_END()

V8_EGET(NodeIpmi, GetBootdev) {
    NodeIpmi* self = Unwrap(info.Holder());
    /*
    //ipmi_chassis_get_bootparam(IPMI_CHASSIS_BOOTPARAM_BOOT_FLAGS
    // this logic is copied from ipmitool
    switch( ((rsp->data[3]>>2)&0x0f))
    {  
        case 0: printf("No override\n"); break;
        case 1: printf("Force PXE\n"); break;
        case 2: printf("Force Boot from default Hard-Drive\n"); break;
        case 3: printf("Force Boot from default Hard-Drive, request Safe-Mode\n"); break;
        case 4: printf("Force Boot from Diagnostic Partition\n"); break;
        case 5: printf("Force Boot from CD/DVD\n"); break;
        case 6: printf("Force Boot into BIOS Setup\n"); break;
        case 15: printf("Force Boot from Floppy/primary removable media\n"); break;
        default: printf("Flag error\n"); break;
    }
    */
    V8_RET(String::New("TODO"));
} V8_GET_END()

V8_ESET(NodeIpmi, SetBootdev) {
    // TODO maybe this should be wrapped in a .js module itself to check for
    // membership of this implicit enum type. I really don't feel like doing
    // that in C...
    if (!value->IsString()) {
        V8_THROW(v8u::Err("bootdev must be a string, one of: none, pxe, disk, safe, diag, cdrom, floppy, bios"));
    }

    NodeIpmi* self = Unwrap(info.Holder());
    String::Utf8Value strval(value->ToString());
    char *argv[] = {"bootdev", *strval};
    ipmi_chassis_main(self->interface, sizeof(argv)/sizeof(*argv), argv);
} V8_SET_END()


NODE_DEF_MAIN() {
    NodeIpmi::init(target);
    // maybe this should be made inaccessible from ipmi.NodeIpmiPower in js
    NodeIpmiPower::init(target);
    /*
    target->Set(
            v8u::Symbol("myversion"),
            new v8u::Version(2,9,1)->Wrapped()
            );
     */
} NODE_DEF_MAIN_END(ipmi)
