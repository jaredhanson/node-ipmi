ipmi = require '../build/Release/ipmi'
moduleWrapper = {}
module.exports = moduleWrapper

moduleWrapper['init'] = (interfaceName) -> wrapObject new ipmi.NodeIpmi(interfaceName)

wrapObject = (obj) ->
    wrapped = {}
    wrappers =
        users:
            get: ->
                users = {}
                (users[x.name] = x) for x in obj.users when x.name isnt ''
                users.add = (name) ->
                    if name in ['add', 'delete']
                        throw Error "Don't use name: #{name}"
                    # XXX slot id 1 can never be used??
                    unused = (obj.users[k] for k in (Object.keys obj.users)[1..] when typeof obj.users[k] isnt 'function' and obj.users[k].name is '')
                    if users[name]?
                        throw Error 'User already exists'
                    if unused.length is 0
                        throw Error 'Empty user slot unavailable'
                    unused[0].name = name
                users.delete = (name) ->
                    if name in ['add', 'delete']
                        throw Error "Don't use name: #{name}"
                    if not users[name]?
                        throw Error 'User not found'
                    users[name].name = ''
                users
            set: (_) -> throw 'setting users not allowed'

    wrap = (x) ->
        if not wrappers[x]?
            accessors =
                get: -> obj[x]
                set: (value) -> obj[x] = value
        else
            accessors =
                get: wrappers[x].get
                set: wrappers[x].set
        Object.defineProperty(wrapped, x,
            get: accessors.get
            set: accessors.set
            configurable: false
            enumerable: true
            writeable: true
        )
            

    # GOTCHA: 'x' doesn't have the right scope in generated JS if you try to inline the wrapit() function
    wrap(x) for x in Object.keys obj
    wrapped
