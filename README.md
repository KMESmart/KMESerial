# KMESerial Library

`KMESerial` is a lightweight Arduino library designed for serial communication with KME Smart devices, allowing easy control of sensors, switches, and the retrieval of system information. This library enables bidirectional communication with microcontrollers like ESP32, ESP8266, and others, making it simple to interface with sensors and actuators through a serial connection.

## Features

- Supports hardware serial communication using Arduino's `HardwareSerial`.
- Easily control GPIO pins based on switch state changes.
- Retrieve status and settings for multiple switches and sensors.
- Send and receive data via serial communication.
- Callback function support for handling switch state changes.
- Time synchronization feature for accurate timing.

## Installation

1. Download the `KMESerial` library from GitHub.
2. Move the folder to your Arduino libraries directory, usually located at `~/Documents/Arduino/libraries/`.
3. Include the library in your Arduino sketch:

```cpp
#include <KMESerial.h>
