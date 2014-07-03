node-rcswitch
=============

[![NPM version](https://badge.fury.io/js/rcswitch.svg)](http://badge.fury.io/js/rcswitch)

Node bindings for the [rcswitch RaspberryPi port](https://github.com/r10r/rcswitch-pi).

Successfully tested on Raspbian Wheezy (2014-06-20) up-to-date.

## Requirements

Like C++ version of rcswitch, [WiringPi must be installed](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) in order to compile.

## Usage (non-definitive API)

```javascript
var rcswitch = require('rcswitch');

rcswitch.enableTransmit(0); // Set WiringPi Pin 0 on OUTPUT (see http://wiringpi.com/pins/ for pin numerotation)
rcswitch.switchOn("10110", 1); // Switch on the first unit of 10110 (code 1.23.) group
rcswitch.switchOff("11000", 2); // Switch off the second unit of 11000 (code 12...) group
```