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

var i = new ipmi.NodeIpmi("lan")
console.log(i);
console.log(i.getChassisPowerStatus("lan"));
//console.log(i['getChassisPowerStatus']());
//console.log(i['GetChassisPowerStatus']());
//console.log(i.GetChassisPowerStatus());
