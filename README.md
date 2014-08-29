node-rcswitch
=============

[![NPM version](https://badge.fury.io/js/rcswitch.svg)](http://badge.fury.io/js/rcswitch)

Node bindings for the [rcswitch RaspberryPi port](https://github.com/r10r/rcswitch-pi).

Successfully tested on Raspbian Wheezy (2014-06-20) up-to-date.

## Requirements

* Like the C++ version of rcswitch, [WiringPi must be installed](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) in order to compile.
* Both the data and the power Pins of the 315/433Mhz emitter must be connected to the RPi. Note the number of the WiringPi data Pin. (see http://wiringpi.com/pins/)

## Usage

```javascript
var rcswitch = require('rcswitch');

rcswitch.enableTransmit(0); // Use data Pin 0
rcswitch.switchOn("10110", 1); // Switch on the first unit of 10110 (code 1x23x) group
rcswitch.switchOff("11000", 2); // Switch off the second unit of 11000 (code 12xxx) group
```

## API

### rcswitch.enableTransmit(`pin`)

Enable transmission.

* `pin` - (Number) data Pin to use following [the WiringPi schema](http://wiringpi.com/pins/)

Return true if everything went fine, false otherwise.

### rcswitch.disableTransmit()

Disable transmission.

Return true.

### rcswitch.switchOn(`group`, `switch`)

Switch a remote switch on (Type A with 10 pole DIP switches)

* `group` - (String) code of the switch group (refers to DIP switches 1..5 where "1" = on and "0" = off, if all DIP switches are on it's "11111")
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.switchOf(`group`, `switch`)

Switch a remote switch off (Type A with 10 pole DIP switches)

* `group` - (String) code of the switch group (refers to DIP switches 1..5 where "1" = on and "0" = off, if all DIP switches are on it's "11111")
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.switchOn(`group`, `switch`)

Switch a remote switch on (Type B with two rotary/sliding switches).

* `group` - (Number) group (1..4)
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.switchOff(`group`, `switch`)

Switch a remote switch off (Type B with two rotary/sliding switches).

* `group` - (Number) group (1..4)
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.switchOn(`family`, `group`, `switch`)

Switch a remote switch on (Type C Intertechno)

* `family` - (String) familycode (a..f)
* `group` - (Number) group (1..4)
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.switchOff(`family`, `group`, `switch`)

Switch a remote switch off (Type C Intertechno)

* `family` - (String) familycode (a..f)
* `group` - (Number) group (1..4)
* `switch` - (Number) switch (1..4)

Return true.

### rcswitch.send(`codeWord`)

Send raw codeword

* `codeword` - (String) codeword

Return true.