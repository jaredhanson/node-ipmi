var ipmi = require("./build/Release/ipmi");

var methods = [];
for (var m in ipmi) {
    if (typeof ipmi[m] == "function") {
        methods.push(m);
    }
    else {
    console.log(m);
    }
}
console.log(methods.join(","));

ipmi = new ipmi.NodeIpmi("lan")
//console.log(i);
//ipmi.hostname = 1;
console.log(ipmi.hostname);
ipmi.hostname = "192.168.0.30";
ipmi.username = "root"
ipmi.password = "calvin"
console.log(ipmi.hostname);
console.log(ipmi.bootdev);
ipmi.bootdev = "pxe"
console.log(ipmi.bootdev);
console.log(ipmi.power.status);
//console.log(ipmi.power.off());
console.log(ipmi.power.status);
console.log("userlist: " + ipmi.users);
for (var ndx=0; ndx < ipmi.users.length; ndx++) {
    u = ipmi.users[ndx]
    console.log("user: " + [u.id, u.name].join())
}
