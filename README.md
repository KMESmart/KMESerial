# KMESerial Library

`KMESerial` is a lightweight Arduino library designed for serial communication with KME Smart devices. It facilitates the control of sensors, switches, and provides system status updates. The library supports bidirectional communication with microcontrollers like ESP32, ESP8266, and more, making it easy to integrate with sensors and actuators via serial communication.

## Features

- Hardware serial communication using `HardwareSerial`.
- Control GPIO pins based on switch state changes.
- Retrieve status and settings of multiple switches and sensors.
- Callback function for handling switch state changes.
- Time synchronization for accurate clock settings.
- Manage multiple sensors and switches.

## Installation

1. Download the `KMESerial` library from GitHub.
2. Extract and move the library to your Arduino libraries directory, typically located at `~/Documents/Arduino/libraries/`.
3. In your Arduino sketch, include the library:

```cpp
/*
 * License: KME Smart Software License
 * 
 * This software is provided by Adnan Elabdullah "as is" and any express or implied
 * warranties, including, but not limited to, the implied warranties of merchantability
 * and fitness for a particular purpose are disclaimed. In no event shall the author be
 * liable for any direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute goods or services;
 * loss of use, data, or profits; or business interruption) however caused and on any
 * theory of liability, whether in contract, strict liability, or tort (including negligence
 * or otherwise) arising in any way out of the use of this software, even if advised of
 * the possibility of such damage.
 * 
 * Author: Adnan Elabdullah
 * 
 * Description: This firmware controls GPIO pins based on switch states received from
 * the KMESerial library and updates sensor values periodically. It also handles
 * time synchronization based on information received from KMESerial.
 */

#include <KMESerial.h>
#include <TimeLib.h>

KMESerial KMESerial;
int val = 0;
int secondSensorVal = 50; // Initialize the value for the second sensor
uint8_t ledpin = 13;

/**
 * switchstate() - This function is a callback that handles switch state changes.
 * It checks the switch ID (State.id) and maps it to a corresponding GPIO pin.
 * Based on the switch state (ON or OFF), it controls the output (HIGH or LOW) 
 * on the respective pin and updates the KMESerial with the switch state.
 *
 * @param State: The state object that contains the ID and value of the switch.
 */
void switchstate(KME State) {
  byte gpio = 0;
  // Check for each switch ID and assign corresponding GPIO pin
  if (State.id == 0) {
    gpio = 13;
  } else if (State.id == 1) {
    gpio = 8;
  } else if (State.id == 2) {
    gpio = 7;
  } else if (State.id == 3) {  // New switch with ID 3
    gpio = 12;
  }

  // Set the corresponding GPIO pin HIGH or LOW based on the switch state
  digitalWrite(gpio, State.value == 1 ? true : false);
  KMESerial.SetSwitch(State.id, State.value == 1 ? true : false);
}

int heartbeat = 0;
bool timegeted = true;

/**
 * setup() - This function is called once when the microcontroller starts. 
 * It sets up serial communication, initializes GPIO pins as outputs, 
 * and prepares the KMESerial communication. It also retrieves the status and 
 * settings of the switches and sets up a callback to handle switch state changes.
 */
void setup() {
  Serial.begin(74880); // Initialize serial communication with baud rate 74880
  Serial.setTimeout(50); // Set serial timeout to 50 milliseconds

  // Set up the GPIO pins as outputs
  pinMode(ledpin, OUTPUT); // Set LED pin as output
  pinMode(8, OUTPUT); // Set pin 8 as output
  pinMode(7, OUTPUT); // Set pin 7 as output
  pinMode(12, OUTPUT); // Set pin 12 as output (for new switch)

  // Initialize KMESerial object and perform initial setup
  KMESerial.getStatus(0); // Get status for ID 0
  KMESerial.getStatus(1); // Get status for ID 1
  KMESerial.getStatus(2); // Get status for ID 2 (if applicable)
  KMESerial.getStatus(3); // Get status for the new switch (ID 3)
  
  KMESerial.setCallback(switchstate); // Set callback function for handling switch state changes
  KMESerial.getSettings(0); // Get settings for ID 0
}

/**
 * loop() - This function is called repeatedly after the setup() function.
 * It continuously updates the sensor values, handles KMESerial communication,
 * checks for heartbeat changes, and synchronizes time once a condition is met.
 * It runs in an infinite loop and executes the tasks every iteration.
 */
void loop() {
  val = val + 20; // Increment val by 20 each loop iteration
  secondSensorVal = secondSensorVal + 10; // Increment second sensor value by 10

  KMESerial.loop(); // Execute KMESerial library loop function
  delay(300); // Delay for 300 milliseconds

  // Set sensor values for both sensors (ID 0 and ID 1)
  KMESerial.setSensor(0, val); // Set sensor value for ID 0 to current value of val
  KMESerial.setSensor(1, secondSensorVal); // Set sensor value for ID 1 to current value of secondSensorVal

  // Check if heartbeat value has changed and print it if it has
  if (heartbeat != KMESerial.info().heartbeat) {
    Serial.print("heartbeat:");
    Serial.print(KMESerial.info().heartbeat);
    heartbeat = KMESerial.info().heartbeat;
  }

  // Perform time synchronization if 'timegeted' is true and val > 100
  if (timegeted && val > 100) {
    timegeted = false; // Mark time synchronization as completed
    Serial.print("info:");
    Serial.println(KMESerial.info().currentTime); // Print current time received from KMESerial

    setTime(KMESerial.info().currentTime); // Set the Arduino system time to the received current time

    // Print the current time in a readable format
    Serial.print("Current Time: ");
    Serial.println(now());

    // Print formatted time (hh:mm:ss dd/mm/yyyy)
    Serial.print("Formatted Time: ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print(" ");
    Serial.print(day());
    Serial.print("/");
    Serial.print(month());
    Serial.print("/");
    Serial.println(year());
  }
}
