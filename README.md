Welcome to the PowerWrangler wiki!

## Purpose
Here we will add descriptions of the various code modules and how they are used.

### Remote Node
* AnalogMonitorNoSerial.ino - Can run a remote Arduino Nano node, without IDE connection
* AnalogMonitorSerial.ino - Must be connected to Arduino IDE, will duplicate BLE output to serial logger

### Central Node
Michael is still working through communication issues with the central node. The first few Bluetooth libraries I tried were very unstable. 

We'll use this repo to host: 
* User Interface (web directory)
* Communication code to the remote nodes
* The underlying data processing code
