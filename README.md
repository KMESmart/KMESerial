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
#include <KMESerial.h>
//note for ESP32
RX Pin (ESP32): GPIO 26
TX Pin (ESP32): GPIO 27
Functions
switchstate(KME State)
This function is a callback that handles changes in switch states. Based on the State.id, it maps to a corresponding GPIO pin. When the switch is turned ON or OFF, the function updates the GPIO pin output to HIGH or LOW and sends the updated switch state back through the KMESerial library.

Parameters:

State: A KME object that contains the id and value of the switch.
The function controls the following GPIO pins based on the switch id:

id == 0 -> GPIO 13
id == 1 -> GPIO 8
id == 2 -> GPIO 7
id == 3 -> GPIO 12 (new switch)
The GPIO pin is set to HIGH if State.value == 1, otherwise LOW.

setup()
This function is called once when the microcontroller starts. It initializes serial communication, sets GPIO pins as outputs, prepares communication through the KMESerial library, retrieves switch statuses, and sets up a callback to handle switch state changes.

Key Tasks:

Initializes serial communication with a baud rate of 74880.
Sets up GPIO pins 7, 8, 12, and 13 as output pins for controlling external components.
Retrieves initial switch statuses for IDs 0, 1, 2, and 3 using KMESerial.getStatus().
Sets up the switchstate() callback to handle switch state changes.
Retrieves settings for switch ID 0 using KMESerial.getSettings().
loop()
This function is called repeatedly after the setup() function and performs the following tasks:

Key Tasks:

Increments sensor values val by 20 and secondSensorVal by 10 on each iteration.
Updates sensor values for ID 0 and ID 1 using KMESerial.setSensor().
Executes the KMESerial.loop() function to handle communication with the KMESerial library.
Checks if the heartbeat value has changed and prints it if there is an update.
Performs time synchronization once val > 100 and prints the synchronized time in both raw and formatted formats.
Time Synchronization:

Once the condition val > 100 is met, the current time from KMESerial is retrieved and set using the setTime() function.
The current time is printed in both raw seconds and in a formatted hh:mm:ss dd/mm/yyyy format.
Variables
val: The main sensor value that is incremented by 20 in each loop iteration.
secondSensorVal: The second sensor value that is incremented by 10 in each loop iteration.
heartbeat: Tracks the heartbeat signal received from KMESerial. If the heartbeat changes, it prints the new value.
timegeted: A flag that ensures time synchronization only happens once when val > 100.
Notes
The firmware controls four switches mapped to GPIO pins 7, 8, 12, and 13. Additional switches can be added by extending the switchstate() function.
The sensor values for ID 0 and 1 are updated periodically based on val and secondSensorVal.
The KMESerial library handles the communication and switch state changes, and is also used for time synchronization.





