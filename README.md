node-rcswitch
=============

[![NPM version](https://badge.fury.io/js/rcswitch.svg)](http://badge.fury.io/js/rcswitch)

Node bindings for the [rcswitch RaspberryPi port](https://github.com/r10r/rcswitch-pi).

Successfully tested on Raspbian Wheezy up-to-date as of 2015-02-28.

## Requirements

* Like the C++ version of rcswitch, [WiringPi must be installed](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) in order to compile.
* Both the data and the power Pins of the 315/433Mhz emitter must be connected to the RPi. Note the number of the WiringPi data Pin. (see http://wiringpi.com/pins/)
* The node command must be run with root access

## Usage

```javascript
var rcswitch = require('rcswitch'); // Might throw an error if wiring pi init failed, or exit process if no root (must work on that)

rcswitch.enableTransmit(0); // Use data Pin 0
rcswitch.switchOn("10110", 1); // Switch on the first unit of 10110 (code 1x23x) group
rcswitch.switchOff("11000", 2); // Switch off the second unit of 11000 (code 12xxx) group
```

## API

### Configuration

#### rcswitch.enableTransmit(`pin`)

Enable transmission on the given pin (make it an OUTPUT). Must be called before any other functions.

* `pin` - (Number) data Pin to use following [the WiringPi schema](http://wiringpi.com/pins/)

Return true if `pin` is an integer, false otherwise.

#### rcswitch.disableTransmit()

Disable transmission (set the pin to -1 which disable any following function call).

Return true.

### Type A

![Type A](http://gladysproject.com/img/IMG_0628_2.jpg)

#### rcswitch.switchOn(`group`, `switch`)

Switch a remote switch on (Type A with 10 pole DIP switches).

* `group` - (String) code of the switch group (refers to DIP switches 1, 2, 3, 4 and 5 where "1" = on and "0" = off - e.g. if all DIP switches are on it's "11111")
* `switch` - (Number) switch number (can be 1 (if DIP switch A is on), 2 (if DIP switch B is on) and so on until 4)

Return true.

#### rcswitch.switchOff(`group`, `switch`)

Switch a remote switch off (Type A with 10 pole DIP switches).

* `group` - (String) code of the switch group (refers to DIP switches 1, 2, 3, 4 and 5 where "1" = on and "0" = off - e.g. if all DIP switches are on it's "11111")
* `switch` - (Number) switch number (can be 1 (if DIP switch A is on), 2 (if DIP switch B is on) and so on until 4)

Return true.

### Type B

![Type B](http://i9.instantgallery.de/s/su/sui/b0d5c19446819.png)

(don't care about the mySwitch, here only for reference)

#### rcswitch.switchOn(`group`, `switch`)

Switch a remote switch on (Type B with two rotary/sliding switches).

* `group` - (Number) group (can be 1, 2, 3, 4)
* `switch` - (Number) switch (can be 1, 2, 3, 4)

Return true.

#### rcswitch.switchOff(`group`, `switch`)

Switch a remote switch off (Type B with two rotary/sliding switches).

* `group` - (Number) group (can be 1, 2, 3, 4)
* `switch` - (Number) switch (can be 1, 2, 3, 4)

Return true.

### Type C

#### rcswitch.switchOn(`family`, `group`, `switch`)

Switch a remote switch on (Type C Intertechno).

* `family` - (String) familycode (can be a, b, c, d, e, f)
* `group` - (Number) group (can be 1, 2, 3, 4)
* `switch` - (Number) switch (can be 1, 2, 3, 4)

Return true.

#### rcswitch.switchOff(`family`, `group`, `switch`)

Switch a remote switch off (Type C Intertechno).

* `family` - (String) familycode (can be a, b, c, d, e, f)
* `group` - (Number) group (can be 1, 2, 3, 4)
* `switch` - (Number) switch (can be 1, 2, 3, 4)

Return true.

### Other

#### rcswitch.send(`codeWord`)

Send raw codeword.

* `codeword` - (String) codeword

Return true.
