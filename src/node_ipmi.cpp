#include <sstream>
#include "node_ipmi.hpp"
extern "C" {
#include "ipmitool/ipmi_chassis.h"
#include "ipmitool/ipmi_main.h"
}
extern struct ipmi_cmd *ipmitool_cmd_list;

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
      //FIXME NO RETURNS ALLOWED MAKE STATIC CONST//V8_STHROW(v8u::Err(msg.str().c_str()));
   }
}

NodeIpmi::~NodeIpmi() {
	interface->close(interface);
}

//V8_ESCTOR(NodeIpmi) { V8_CTOR_NO_JS }


V8_SCB(NodeIpmi::LoadInterface) {
	if(args.Length() != 1) V8_STHROW(v8u::RangeErr("Invalid Argument"));

        String::Utf8Value interface_name(args[0]->ToString());

	ipmi_intf *intf = ipmi_intf_load(*interface_name);
        //int argc = 11; char *argv[] = { "ipmitool", "-I", "lan", "-H", "192.168.0.30", "-U", "root", "-P", "calvin", "power", "status" };
        //int argc = 2; char *argv[] = {"ipmitool", "-h"};
        //int rc = ipmi_main(argc, argv, ipmitool_cmd_list, NULL);

        if (intf == NULL) {
         std::stringstream msg;
         msg << "Error loading interface named \"" << *interface_name << "\"";
         V8_STHROW(v8u::Err(msg.str().c_str()));
        }
	//return (new NodeIpmi(intf))->Wrapped();
}

        V8_CB(NodeIpmi::GetChassisPowerStatus) {
           v8::String::Utf8Value interface_name(args[0]->ToString());
           NodeIpmi *self = Unwrap(args.This());
           ipmi_intf_session_set_username(self->interface, "root");
           ipmi_intf_session_set_password(self->interface, "calvin");
           int chassis_status = ipmi_chassis_power_status(self->interface);
           if (chassis_status == -1) {
              std::stringstream msg;
              msg << "call failed: " << "GetChassisPowerStatus";
              V8_STHROW(v8u::Err(msg.str().c_str()));
           }
           //V8_RET(chassis_status);
           return v8::Integer::New(chassis_status);
        } V8_CB_END()

        V8_ESET(NodeIpmi, SetHostname) {
           if (!value->IsString()) {
              V8_THROW(v8u::Err("hostname must be a string"));
           }

          NodeIpmi* self = Unwrap(info.Holder());
          self->hostname = value->ToString();
          String::Utf8Value hostname(self->hostname);
          ipmi_intf_session_set_hostname(self->interface, *hostname);
        } V8_SET_END()


        V8_EGET(NodeIpmi, GetHostname) {
          NodeIpmi* self = Unwrap(info.Holder());
          V8_RET(self->hostname);
        } V8_GET_END()

NODE_DEF_MAIN() {
	NodeIpmi::init(target);
} NODE_DEF_MAIN_END(ipmi)
