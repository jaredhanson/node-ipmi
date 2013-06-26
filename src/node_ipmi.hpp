#include "v8u.hpp"
#include "ipmitool/ipmi_intf.h"

class NodeIpmi : public node::ObjectWrap {
public:
	NodeIpmi(ipmi_intf *ptr);
	~NodeIpmi();
	V8_SCTOR();

	static V8_SCB(Init);

	NODE_STYPE(NodeIpmi);
private:
	ipmi_intf *interface;
};

