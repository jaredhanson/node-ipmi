should = require 'should'
ipmi = require '..'

describe 'general tests', ->
    intf = ipmi.init 'lan'
    intf.hostname = '192.168.0.30'
    intf.username = 'root'
    intf.password = 'calvin'
    it 'should return power status', ->
        intf.power.status.should.eql 'on'
    it 'bootdev', ->
        intf.bootdev = 'pxe'
        #intf.bootdev.should.eql 'pxe'
    it 'users', ->
        #console.log intf
        #console.log intf.users
        #console.log intf.users.root
        #console.log intf.users.add 'root' #should throw exc
        console.log intf.users.add 'user13'
        ##console.log(ipmi.power.off());
        #console.log(ipmi.power.status);
        #console.log("userlist: " + ipmi.users);
        #for (var ndx=0; ndx < ipmi.users.length; ndx++) {
        #    user = ipmi.users[ndx]
        #    console.log("user: " + [user.id, user.name].join())
        #}

        #//TODO add ipmi.getUsersByName -> object mapping names to users
        #uid = 6
        #console.log(ipmi.users[uid])
        #console.log(ipmi.users[uid].enabled = false)
        #console.log(ipmi.users[uid].name = "test2")
        #console.log(ipmi.users[uid].password = "testfoo")
        #console.log(ipmi.users[uid].privilegeLevel=2)
        #console.log(ipmi.users[uid])

#TODO tests:
# mockup for power on/off etc?
# negative:
#  bad type for each field
#  too short, long for user.name
