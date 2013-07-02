ipmi = require '../build/Release/ipmi'
moduleWrapper = {}
module.exports = moduleWrapper

moduleWrapper['init'] = (interfaceName) -> wrapInterface(new ipmi.NodeIpmi interfaceName)

wrapInterface = (obj) ->
    interfaceWrapper = {}

    wrappers = {
        users:
            get: () -> obj.users
            set: (value) -> obj.users = value
    }

    wrap = (x) ->
        if not wrappers[x]?
            get = () -> obj[x]
            set = (value) -> obj[x] = value
            #console.log "wrapping #{x} with default"
        else
            get = wrappers[x].get
            set = wrappers[x].set
        Object.defineProperty(interfaceWrapper, x,
            get : get
            set : set
            configurable : false
            enumerable : true
            writeable: true
        )
            

    # GOTCHA: 'x' doesn't have the right scope in generated JS if you try to inline the wrapit() function
    wrap(x) for x in Object.keys obj

    #Object.defineProperty(interfaceWrapper, 'power',
    #    get : () -> obj['power']
    #    set : (value) -> obj['power'] = value
    #    configurable : false
    #    enumerable : true
    #    writeable: true
    #)
    #Object.defineProperty(interfaceWrapper, 'hostname',
    #    get : () -> obj['hostname']
    #    set : (value) -> obj['hostname'] = value
    #    configurable : false
    #    enumerable : true
    #    writeable: true
    #)
    #Object.defineProperty(interfaceWrapper, 'username',
    #    get : () -> obj['username']
    #    set : (value) -> obj['username'] = value
    #    configurable : false
    #    enumerable : true
    #    writeable: true
    #)
    #Object.defineProperty(interfaceWrapper, 'password',
    #    get : () -> obj['password']
    #    set : (value) -> obj['password'] = value
    #    configurable : false
    #    enumerable : true
    #    writeable: true
    #)

    #interfaceWrapper['power'] = obj.power
    interfaceWrapper
