var ipmi, should;

should = require('should');

ipmi = require('..');

describe('general tests', function() {
  var intf;
  intf = ipmi.init('lan');
  intf.hostname = '192.168.0.30';
  intf.username = 'root';
  intf.password = 'calvin';
  it('should return power status', function() {
    return intf.power.status.should.eql('off');
  });
  it('bootdev', function() {
    return intf.bootdev = 'pxe';
  });
  it('- user prohibited names', function() {
    (function() {
      return intf.users.add('add');
    }).should["throw"]();
    (function() {
      return intf.users.add('delete');
    }).should["throw"]();
    (function() {
      return intf.users["delete"]('add');
    }).should["throw"]();
    return (function() {
      return intf.users["delete"]('delete');
    }).should["throw"]();
  });
  it('- user duplicate name', function() {
    return (function() {
      return intf.users.add('root');
    }).should["throw"]();
  });
  it('user long names', function() {
    (function() {
      return intf.users.add(([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15].map(function() {
        return 'x';
      })).join(''));
    }).should.not["throw"]();
    return (function() {
      return intf.users["delete"](([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15].map(function() {
        return 'x';
      })).join(''));
    }).should.not["throw"]();
  });
  it('- user long names', function() {
    return (function() {
      return intf.users.add(([1.16].map(function() {
        return 'x';
      })).join(''));
    }).should["throw"]();
  });
  it('- user long password', function() {
    return (function() {
      var _i, _results;
      return intf.users.ipmi.password = ((function() {
        _results = [];
        for (_i = 1; _i <= 30; _i++){ _results.push(_i); }
        return _results;
      }).apply(this).map(function() {
        return 'x';
      })).join('');
    }).should["throw"]();
  });
  it('user long password', function() {
    (function() {
      return intf.users.ipmi.password = ([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16].map(function() {
        return 'x';
      })).join('');
    }).should.not["throw"]();
    return (function() {
      return intf.users.ipmi.password = ([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20].map(function() {
        return 'x';
      })).join('');
    }).should.not["throw"]();
  });
  it('add+rem users', function() {
    intf.users.add('test12');
    return intf.users["delete"]('test12');
  });
  it('power tests', function() {
    return intf.power.status;
  });
  return it('user settings', function() {
    var name;
    name = 'ipmi';
    intf.users[name].enabled = false;
    intf.users[name].enabled = true;
    intf.users[name].password = 'testfoo';
    return intf.users[name].privilegeLevel = 2;
  });
});
