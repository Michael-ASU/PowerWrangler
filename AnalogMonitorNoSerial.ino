/*
  This code monitors an analog input pin on the Arduino and reports that via BLE connection

  This version is used when you do NOT want the Serial logger output via Arduino IDE

  The code is modified from an example library used to report battery levels.

  The output was tested with iOS app "LightBlue"
*/

#include <ArduinoBLE.h>

 // BLE Analog Report Service
BLEService analogService("180F");

// BLE Analog Level Characteristic
BLEUnsignedCharCharacteristic analogLevelChar("2A19", BLERead | BLENotify);

int oldAnalogLevel = 0;  // last reading from analog input
long previousMillis = 0;  // last time the analog level was checked, in ms

void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin to indicate when a central node is connected

  // begin initialization
  if (!BLE.begin()) {
    while (1);
  }

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  
  BLE.setLocalName("PowerWranglerA");
  BLE.setAdvertisedService(analogService); // add the service UUID
  analogService.addCharacteristic(analogLevelChar); // add the analog level characteristic
  BLE.addService(analogService); // Add the analog service
  analogLevelChar.writeValue(oldAnalogLevel); // set initial value for this characteristic

  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // check the analog level every 500ms
    // while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 500ms have passed, check the analog level:
      if (currentMillis - previousMillis >= 500) {
        previousMillis = currentMillis;
        updateAnalogLevel();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void updateAnalogLevel() {
  // Read the current voltage level on the A0 analog input pin.

  int analogPin = analogRead(A0);
  int analogLevel = map(analogPin, 0, 1023, 0, 100);

  if (true) {   // "True" here means it reports every 500ms, add a conditional to skip reports   
    analogLevelChar.writeValue(analogLevel); 
    oldAnalogLevel = analogLevel;           
  }
}
