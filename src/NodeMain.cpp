#include "NodeIpmi.hpp"
#include "NodeIpmiPower.hpp"

// some globals needed by ipmitool
int verbose = 0;
int csv_output = 0;

NODE_DEF_MAIN() {
    NodeIpmi::init(target);
    // maybe this should be made inaccessible from ipmi.NodeIpmiPower in js
    NodeIpmiPower::init(target);
    NodeIpmiUser::init(target);
    /*
       target->Set(
       v8u::Symbol("myversion"),
       new v8u::Version(2,9,1)->Wrapped()
       );
     */
} NODE_DEF_MAIN_END(ipmi)
