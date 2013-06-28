#include "v8u.hpp"
extern "C" {
#include "ipmitool/ipmi_intf.h"
}

using namespace v8;

class NodeIpmi : public node::ObjectWrap {
   public:
      NodeIpmi(const char *interface_name);
      ~NodeIpmi();

      V8_CTOR() {
         if(args.Length() != 1) V8_STHROW(v8u::RangeErr("Invalid Argument"));
         String::Utf8Value interface_name(args[0]->ToString());
         V8_WRAP(new NodeIpmi(*interface_name));
      } V8_CTOR_END()

      void setHostname(Local<String> hostname) {this->hostname = hostname;}

      static V8_SCB(GetChassisPowerStatus);
      static V8_SCB(LoadInterface);
      V8_SSET(SetHostname);
      V8_SGET(GetHostname);

      NODE_TYPE(NodeIpmi, "NodeIpmi") {
         V8_DEF_CB("getChassisPowerStatus", GetChassisPowerStatus);
         V8_DEF_ACC("hostname", GetHostname, SetHostname);
         //V8_DEF_ACC("username", GetUsername, SetUsername);
         //V8_DEF_ACC("password", GetPassword, SetPassword);
      } NODE_TYPE_END()
   private:
      ipmi_intf *interface;
      Local<String> hostname;
};
V8_POST_TYPE(NodeIpmi)

