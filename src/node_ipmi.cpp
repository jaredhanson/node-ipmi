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

/*
//V8_ESCTOR(NodeIpmi) { V8_CTOR_NO_JS }

NODE_ETYPE(NodeIpmi, "NodeIpmi") {
	//Local<Function> func = templ->GetFunction();
	target->Set(v8u::Symbol("init"), v8u::Func(Init)->GetFunction());

	//NODE_SET_PROTOTYPE_METHOD(templ, "getChassisPowerStatus", GetChassisPowerStatus);
} NODE_TYPE_END()
V8_POST_TYPE(NodeIpmi);

V8_SCB(NodeIpmi::Init) {
	if(args.Length() != 1) V8_STHROW(v8u::RangeErr("Invalid Argument"));

        String::Utf8Value int_name(args[0]->ToString());

	ipmi_intf *intf = ipmi_intf_load(*int_name);
        //int argc = 11; char *argv[] = { "ipmitool", "-I", "lan", "-H", "192.168.0.30", "-U", "root", "-P", "calvin", "power", "status" };
        //int argc = 2; char *argv[] = {"ipmitool", "-h"};
        //int rc = ipmi_main(argc, argv, ipmitool_cmd_list, NULL);

        if (intf == NULL) {
           std::sstringstream msg;
           V8_STHROW(v8u::Err((msg << "Error loading interface named \"" << int_name << "\"")));
        }
	//return (new NodeIpmi(intf))->Wrapped();
}
*/

/*
V8_CB(NodeIpmi::GetChassisPowerStatus) {
  ipmi_intf_session_set_hostname(interface, "192.168.0.30");
  ipmi_intf_session_set_username(interface, "root");
  ipmi_intf_session_set_password(interface, "calvin");
  int chassis_status = ipmi_chassis_power_status(interface);
  if (chassis_status == -1) {
     V8_STHROW(v8u::Err("call failed"));
     std::sstringstream msg;
     V8_STHROW(v8u::Err((
           (msg << "a" << "." << "B").str()
     )); //FIXME concat without std or malloc?
  }
  V8_RET(chassis_status);
} V8_CB_END()
*/

NODE_DEF_MAIN() {
//	NodeIpmi::init(target);
} NODE_DEF_MAIN_END(ipmi)
