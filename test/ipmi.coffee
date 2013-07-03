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
    it '- user prohibited names', ->
        (-> intf.users.add 'add').should.throw
        (-> intf.users.add 'delete').should.throw
        (-> intf.users.delete 'add').should.throw
        (-> intf.users.delete 'delete').should.throw
    it '- user duplicate name', ->
        (-> intf.users.add 'root').should.throw
    it '- user long names', ->
        (-> intf.users.add '12345678901234567').should.throw
    it 'user max length name', ->
        intf.users.add '123456789012345'
        intf.users.delete '123456789012345'
    it '- user long password', ->
        (-> intf.users.ipmi.password '123456789012345678901').should.throw
    it 'user max length passwords', ->
        # 16 and 20 lengths have different wire formats
        (-> intf.users.ipmi.password '1234567890123456').should.throw
        (-> intf.users.ipmi.password '12345678901234567890').should.throw
    it 'user max length passwords', ->
    it 'user max length passwords', ->
    it 'add+rem users', ->
        intf.users.add('test12')#.should.eql 'test12'
        intf.users.delete 'test12'
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
