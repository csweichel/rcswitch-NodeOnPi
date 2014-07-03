{
  'targets': [
    {
      'target_name': 'rcswitch',
      'sources': [ 'src/RCSwitchNode.cpp', 'externals/rcswitch-pi/RCSwitch.cpp' ],
      'include_dirs': [ '/usr/local/include' ],
      'ldflags': [ '-lwiringPi' ]
    }
  ]
}
