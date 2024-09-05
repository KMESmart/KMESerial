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
This `README.md` file contains all necessary information for installing and using the `KMESerial` library, along with hardware setup instructions for an ESP32, a usage example, and licensing information.






