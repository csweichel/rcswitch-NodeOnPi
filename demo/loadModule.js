var rcswitch = require(__dirname + '/../build/Release/rcswitch.node');

var sw = new rcswitch.RCSwitch();
if(sw.enableTransmit(1)) sw.send("1100");

sw.protocol = 2
sw.send("0110");

sw.switchOn(1, 1);
sw.switchOn("1100", 1);
//sw.switchOn("1", 1, 1); segfaults in RCSwitch

sw.switchOff(1, 1);
sw.switchOff("1100", 1);

sw.disableTransmit();
sw.send("0011");