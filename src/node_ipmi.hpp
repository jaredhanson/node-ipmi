#include "v8u.hpp"
extern "C" {
#include "ipmitool/ipmi_intf.h"
}

class NodeIpmi : public node::ObjectWrap {
private:
	ipmi_intf *interface;
public:
	NodeIpmi(const char *interface_name);
	~NodeIpmi();

        //static V8_SCB(Init);

	V8_CTOR() {
          if(args.Length() != 1) V8_STHROW(v8u::RangeErr("Invalid Argument"));
          v8::String::Utf8Value interface_name(args[0]->ToString());
          V8_WRAP(new NodeIpmi(*interface_name));
        } V8_CTOR_END()

/*
        V8_SCB(GetChassisPowerStatus);

	//static V8_SCB(Init);
        NODE_DEF_TYPE("NodeIpmi") {
          V8_DEF_CB("getChassisPowerStatus", GetChassisPowerStatus);
        } NODE_DEF_TYPE_END()
*/
};

