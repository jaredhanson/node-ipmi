var ipmi, moduleWrapper, wrapObject;

ipmi = require('../build/Release/ipmi');

moduleWrapper = {};

module.exports = moduleWrapper;

moduleWrapper['init'] = function(interfaceName) {
  return wrapObject(new ipmi.NodeIpmi(interfaceName));
};

wrapObject = function(obj) {
  var wrap, wrapped, wrappers, x, _i, _len, _ref;
  wrapped = {};
  wrappers = {
    users: {
      get: function() {
        var users, x, _i, _len, _ref;
        users = {};
        _ref = obj.users;
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          x = _ref[_i];
          if (x.name !== '') {
            users[x.name] = x;
          }
        }
        users.add = function(name) {
          var k, unused;
          if (name === 'add' || name === 'delete') {
            throw Error("Don't use name: " + name);
          }
          unused = (function() {
            var _j, _len1, _ref1, _results;
            _ref1 = (Object.keys(obj.users)).slice(1);
            _results = [];
            for (_j = 0, _len1 = _ref1.length; _j < _len1; _j++) {
              k = _ref1[_j];
              if (typeof obj.users[k] !== 'function' && obj.users[k].name === '') {
                _results.push(obj.users[k]);
              }
            }
            return _results;
          })();
          if (users[name] != null) {
            throw Error('User already exists');
          }
          if (unused.length === 0) {
            throw Error('Empty user slot unavailable');
          }
          return unused[0].name = name;
        };
        users["delete"] = function(name) {
          if (name === 'add' || name === 'delete') {
            throw Error("Don't use name: " + name);
          }
          if (!(users[name] != null)) {
            throw Error('User not found');
          }
          return users[name].name = '';
        };
        return users;
      },
      set: function(_) {
        throw 'setting users not allowed';
      }
    }
  };
  wrap = function(x) {
    var accessors;
    if (!(wrappers[x] != null)) {
      accessors = {
        get: function() {
          return obj[x];
        },
        set: function(value) {
          return obj[x] = value;
        }
      };
    } else {
      accessors = {
        get: wrappers[x].get,
        set: wrappers[x].set
      };
    }
    return Object.defineProperty(wrapped, x, {
      get: accessors.get,
      set: accessors.set,
      configurable: false,
      enumerable: true,
      writeable: true
    });
  };
  _ref = Object.keys(obj);
  for (_i = 0, _len = _ref.length; _i < _len; _i++) {
    x = _ref[_i];
    wrap(x);
  }
  return wrapped;
};
