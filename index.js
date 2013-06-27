
var ipmi = new require('./build/Release/ipmi');

module.exports = function(){
	return new ipmi.Ipmi;
}
for(var k in ipmi){
	if(k !== 'NodeIpmi'){
		module.exports[k] = ipmi[k];
	}
}
