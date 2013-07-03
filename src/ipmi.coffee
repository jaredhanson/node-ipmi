ipmi = require '../build/Release/ipmi'
aop = require 'node-aop'
moduleWrapper = {}
module.exports = moduleWrapper

moduleWrapper['init'] = (interfaceName) -> wrapObject new ipmi.NodeIpmi(interfaceName)

wrapObject = (obj) ->
    wrapped = {}
    wrappers =
        users:
            get: () ->
                users = {}
                users[x.name] = x for x in obj.users when x.name?
                users.add = (name) ->
                    #used = (users[k] for k in Object.keys users) when users[k].name isnt '')
                    # XXX slot id 1 can never be used??
                    unused = (users[k] for k in (Object.keys users)[1..] when users[k].name is '')
                    #console.log "used: #{x.name}" for x in used
                    console.log "unused: #{x.name}" for x in unused
                    if users[name]?
                        throw 'User already exists'
                    # FIXME this condition is never true??
                    if unused.length is 0
                        throw 'Empty user slot unavailable'
                    console.log "using slot ##{unused[0].id}"
                    unused[0].name = name
                users
            set: (value) -> throw 'setting users not allowed'

    wrap = (x) ->
        if not wrappers[x]?
            accessors =
                get: () -> obj[x]
                set: (value) -> obj[x] = value
            #console.log "wrapping #{x} with default"
        else
            accessors =
                get: wrappers[x].get
                set: wrappers[x].set
        #aop.before accessors, 'get', () -> console.log 'hi'
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
