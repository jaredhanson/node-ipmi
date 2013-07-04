{
  'targets': [
    {
      'target_name': 'ipmi',
      'sources': [
        'src/NodeMain.cpp',
        'src/NodeIpmi.cpp',
        'src/NodeIpmiPower.cpp',
        'src/NodeIpmiUser.cpp',
        # definitely
        'deps/ipmitool/lib/ipmi_strings.c',
        'deps/ipmitool/src/plugins/ipmi_intf.c',
        'deps/ipmitool/src/plugins/open/open.c',

        # maybe
        'deps/ipmitool/src/plugins/lan/lan.c',
        'deps/ipmitool/src/plugins/lan/auth.c',

        # enable as-needed
        #'deps/ipmitool/lib/ipmi_delloem.c',
        #'deps/ipmitool/lib/ipmi_isol.c',
        #'deps/ipmitool/lib/ipmi_mc.c',
        #'deps/ipmitool/lib/ipmi_session.c',
        #'deps/ipmitool/lib/ipmi_ime.c',
        #'deps/ipmitool/lib/ipmi_kontronoem.c',
        #'deps/ipmitool/lib/ipmi_ekanalyzer.c',
        #'deps/ipmitool/lib/ipmi_sol.c',
        #'deps/ipmitool/lib/ipmi_lanp.c',
        #'deps/ipmitool/lib/ipmi_raw.c',
        #'deps/ipmitool/lib/ipmi_main.c',
        #'deps/ipmitool/lib/ipmi_tsol.c',
        #'deps/ipmitool/lib/ipmi_channel.c',
        #'deps/ipmitool/lib/ipmi_sunoem.c',
        #'deps/ipmitool/lib/ipmi_firewall.c',
        #'deps/ipmitool/lib/ipmi_sdradd.c',
         'deps/ipmitool/lib/ipmi_chassis.c',
        #'deps/ipmitool/lib/ipmi_fru.c',
         'deps/ipmitool/lib/ipmi_oem.c',
        #'deps/ipmitool/lib/ipmi_gendev.c',
         'deps/ipmitool/lib/ipmi_user.c',
        #'deps/ipmitool/lib/ipmi_dcmi.c',
        #'deps/ipmitool/lib/ipmi_fwum.c',
         'deps/ipmitool/lib/log.c',
        #'deps/ipmitool/lib/dimm_spd.c',
        #'deps/ipmitool/lib/ipmi_hpmfwupg.c',
         'deps/ipmitool/lib/ipmi_sel.c',
        #'deps/ipmitool/lib/ipmi_picmg.c',
        #'deps/ipmitool/lib/ipmi_sdr.c',
        #'deps/ipmitool/lib/ipmi_event.c',
        #'deps/ipmitool/lib/ipmi_sensor.c',
         'deps/ipmitool/lib/helper.c',
        #'deps/ipmitool/lib/ipmi_pef.c',
        #'deps/ipmitool/src/ipmishell.c',
         'deps/ipmitool/src/plugins/lanplus/lanplus_strings.c',
         'deps/ipmitool/src/plugins/lanplus/lanplus_crypt.c',
         'deps/ipmitool/src/plugins/lanplus/lanplus_dump.c',
         'deps/ipmitool/src/plugins/lanplus/lanplus.c',
         'deps/ipmitool/src/plugins/lanplus/lanplus_crypt_impl.c',
         'deps/ipmitool/src/plugins/serial/serial_basic.c',
         'deps/ipmitool/src/plugins/serial/serial_terminal.c',
         'deps/ipmitool/src/plugins/lan/md5.c',
        #'deps/ipmitool/src/plugins/bmc/bmc.c',
         'deps/ipmitool/src/plugins/imb/imb.c',
        #'deps/ipmitool/src/plugins/imb/imbapi.c',
         'deps/ipmitool/src/plugins/free/free.c',

        # compile probs maybe
        #'deps/ipmitool/src/plugins/lipmi/lipmi.c',

        # need exactly one of these
        #'deps/ipmitool/src/ipmievd.c',
        #'deps/ipmitool/src/ipmitool.c',
      ],
      'include_dirs': [
        'deps/v8u',
        'deps/ipmitool/include',
        'deps/ipmitool', # for config.h FIXME find out what in here is needed to avoid segfaults
        'deps/ipmitool/src/plugins/lanplus', # for lanplus.h:IPMI_LAN_CHANNEL_E
      ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        [ 'OS=="linux"', {
          'cflags': [
              # TODO: any way to not rely on this? any way to build on win32? cygwin ok?
              "-DHAVE_CONFIG_H",
          ],
        }]
      ]
    }
  ]
}
