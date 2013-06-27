{
  'targets': [
    {
      'target_name': 'ipmi',
      'sources': [
        'src/node_ipmi.cpp',
        'deps/ipmitool/src/plugins/ipmi_intf.c',
        'deps/ipmitool/src/plugins/lan/lan.c',
        'deps/ipmitool/lib/ipmi_strings.c',
        'deps/ipmitool/lib/log.c'
      ],
      'include_dirs': [
        'deps/v8u',
        'deps/ipmitool/include'
      ],
      'cflags!': [ '-fno-exceptions' ],                                                                                                                                
      'cflags_cc!': [ '-fno-exceptions' ]
    }
  ]
}
