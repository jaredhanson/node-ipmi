should = require 'should'
ipmi = require '..'

describe 'general tests', ->
    intf = ipmi.init 'lan'
    intf.hostname = '192.168.0.30'
    intf.username = 'root'
    intf.password = 'calvin'
    it 'should return power status', ->
        intf.power.status.should.eql 'off'
    it 'bootdev', ->
        intf.bootdev = 'pxe'
        #intf.bootdev.should.eql 'pxe'
    it 'failing user add and delete', ->
        (-> intf.users.add 'root').should.throw
        (-> intf.users.add 'add').should.throw
        (-> intf.users.add 'delete').should.throw
        (-> intf.users.delete 'add').should.throw
        (-> intf.users.delete 'delete').should.throw
    it 'add+rem users', ->
        intf.users.add('test12')#.should.eql 'test12'
        console.log intf.users.delete 'test12'
    it 'power tests', ->
        #intf.power.off
        intf.power.status
    it 'user settings', ->
        name = 'ipmi'
        intf.users[name].enabled = false
        intf.users[name].enabled = true
        intf.users[name].password = 'testfoo'
        intf.users[name].privilegeLevel = 2

#TODO tests:
# mockup for power on/off etc?
# negative:
#  bad type for each field
#  too short, long for user.name
