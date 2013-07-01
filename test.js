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

//TODO tests:
// mockup for power on/off etc?
// negative:
//  bad type for each field
//  too short, long for user.name

ipmi = new ipmi.NodeIpmi("lan")
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
    user = ipmi.users[ndx]
    console.log("user: " + [user.id, user.name].join())
}

//TODO add ipmi.getUsersByName -> object mapping names to users
console.log(ipmi.users[3])
console.log(ipmi.users[3].name = "test")
console.log(ipmi.users[3].password = "testfoo")
