#include "node_ipmi.hpp"

using namespace node;
using namespace v8;

NodeIpmi::NodeIpmi(ipmi_intf *ptr): interface(ptr) {}
NodeIpmi::~NodeIpmi() {
	interface->close(interface);
}

V8_ESCTOR(NodeIpmi) { V8_CTOR_NO_JS }

NODE_ETYPE(NodeIpmi, "NodeIpmiUtil") {
	//Local<Function> func = templ->GetFunction();
	target->Set(v8u::Symbol("init"), v8u::Func(Init)->GetFunction());
} NODE_TYPE_END()
V8_POST_TYPE(NodeIpmi);

V8_SCB(NodeIpmi::Init) {
	if(args.Length() != 1) V8_STHROW(v8u::RangeErr("Invalid Argument"));

	//Handle<String> h_int_name = args[0]->ToString();
        String::Utf8Value int_name(args[0]->ToString());

	//ipmi_intf *intf = ipmi_intf_load(*h_int_name);
	ipmi_intf *intf = ipmi_intf_load(*int_name);

        if (intf == NULL) {
           //V8_STHROW(v8u::Err(("Error loading interface " + *int_name)));
           V8_STHROW(v8u::Err("Error loading interface")); //FIXME
        }

	return (new NodeIpmi(intf))->Wrapped();
}
