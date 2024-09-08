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
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Firmware Documentation</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
        }
        h1, h2, h3 {
            color: #333;
        }
        pre {
            background: #f4f4f4;
            border: 1px solid #ddd;
            padding: 10px;
            overflow-x: auto;
        }
        code {
            background: #f4f4f4;
            padding: 2px 4px;
            border-radius: 3px;
            font-size: 1.1em;
        }
    </style>
</head>
<body>
    <h1>Firmware for GPIO Control and Sensor Updates</h1>
    
    <p>This firmware controls GPIO pins based on switch states received from the <code>KMESerial</code> library and periodically updates sensor values. It also synchronizes time based on information from <code>KMESerial</code>.</p>
    
    <h2>Example Usage</h2>
    <pre><code>void switchstate(KME State) {
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

  // Control the corresponding GPIO based on the switch state
  if (State.value == 1) {
    digitalWrite(gpio, HIGH);  // Turn ON the GPIO pin
  } else {
    digitalWrite(gpio, LOW);   // Turn OFF the GPIO pin
  }

  // Send updated switch state back to KMESerial
  KMESerial.setSwitch(State.id, State.value);
}

void setup() {
  Serial.begin(74880); 
  pinMode(13, OUTPUT);  // GPIO pin 13
  pinMode(8, OUTPUT);   // GPIO pin 8
  pinMode(7, OUTPUT);   // GPIO pin 7
  pinMode(12, OUTPUT);  // GPIO pin 12 (new switch)

  KMESerial.getStatus(0);
  KMESerial.getStatus(1);
  KMESerial.getStatus(2);
  KMESerial.getStatus(3);
  
  KMESerial.setCallback(switchstate);
  KMESerial.getSettings(0);
}

void loop() {
  val += 20;
  secondSensorVal += 10;
  
  KMESerial.loop();
  delay(300);
  
  KMESerial.setSensor(0, val);
  KMESerial.setSensor(1, secondSensorVal);
  
  if (heartbeat != KMESerial.info().heartbeat) {
    Serial.print("heartbeat:");
    Serial.print(KMESerial.info().heartbeat);
    heartbeat = KMESerial.info().heartbeat;
  }
  
  if (timegeted && val > 100) {
    timegeted = false;
    Serial.print("info:");
    Serial.println(KMESerial.info().currentTime);
    
    setTime(KMESerial.info().currentTime);
    Serial.print("Current Time: ");
    Serial.println(now());
    
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
</code></pre>
    
    <h2>Functions</h2>
    
    <h3>switchstate(KME State)</h3>
    <p>This function is a callback that handles changes in switch states. Based on the <code>State.id</code>, it maps to a corresponding GPIO pin. When the switch is turned ON or OFF, the function updates the GPIO pin output to HIGH or LOW and sends the updated switch state back through the <code>KMESerial</code> library.</p>
    <p><strong>Parameters:</strong></p>
    <ul>
        <li><code>State</code>: A <code>KME</code> object that contains the <code>id</code> and <code>value</code> of the switch.</li>
    </ul>
    <p>The function controls the following GPIO pins based on the switch <code>id</code>:</p>
    <ul>
        <li><code>id == 0</code> -> GPIO 13</li>
        <li><code>id == 1</code> -> GPIO 8</li>
        <li><code>id == 2</code> -> GPIO 7</li>
        <li><code>id == 3</code> -> GPIO 12 (new switch)</li>
    </ul>
    <p>The GPIO pin is set to HIGH if <code>State.value == 1</code>, otherwise LOW.</p>
    
    <h3>setup()</h3>
    <p>This function is called once when the microcontroller starts. It initializes serial communication, sets GPIO pins as outputs, prepares communication through the <code>KMESerial</code> library, retrieves switch statuses, and sets up a callback to handle switch state changes.</p>
    <p><strong>Key Tasks:</strong></p>
    <ul>
        <li>Initializes serial communication with a baud rate of <code>74880</code>.</li>
        <li>Sets up GPIO pins 7, 8, 12, and 13 as output pins for controlling external components.</li>
        <li>Retrieves initial switch statuses for IDs 0, 1, 2, and 3 using <code>KMESerial.getStatus()</code>.</li>
        <li>Sets up the <code>switchstate()</code> callback to handle switch state changes.</li>
        <li>Retrieves settings for switch ID 0 using <code>KMESerial.getSettings()</code>.</li>
    </ul>
    
    <h3>loop()</h3>
    <p>This function is called repeatedly after the <code>setup()</code> function and performs the following tasks:</p>
    <p><strong>Key Tasks:</strong></p>
    <ul>
        <li>Increments sensor values <code>val</code> by 20 and <code>secondSensorVal</code> by 10 on each iteration.</li>
        <li>Updates sensor values for ID 0 and ID 1 using <code>KMESerial.setSensor()</code>.</li>
        <li>Executes the <code>KMESerial.loop()</code> function to handle communication with the <code>KMESerial</code> library.</li>
        <li>Checks if the heartbeat value has changed and prints it if there is an update.</li>
        <li>Performs time synchronization once <code>val > 100</code> and prints the synchronized time in both raw and formatted formats.</li>
    </ul>
    <p><strong>Time Synchronization:</strong></p>
    <ul>
        <li>Once the condition <code>val > 100</code> is met, the current time from <code>KMESerial</code> is retrieved and set using the <code>setTime()</code> function.</li>
        <li>The current time is printed in both raw seconds and in a formatted <code>hh:mm:ss dd/mm/yyyy</code> format.</li>
    </ul>
    
    <h2>Variables</h2>
    <ul>
        <li><strong><code>val</code></strong>: The main sensor value that is incremented by 20 in each loop iteration.</li>
        <li><strong><code>secondSensorVal</code></strong>: The second sensor value that is incremented by 10 in each loop iteration.</li>
        <li><strong><code>heartbeat</code></strong>: Tracks the heartbeat signal received from <code>KMESerial</code>. If the heartbeat changes, it prints the new value.</li>
        <li><strong><code>timegeted</code></strong>: A flag that ensures time synchronization only happens once when <code>val > 100</code>.</li>
    </ul>
    
    <h2>Notes</h2>
    <ul>
        <li>The firmware controls four switches mapped to GPIO pins 7, 8, 12, and 13. Additional switches can be added by extending the <code>switchstate()</code> function.</li>
        <li>The sensor values for ID 0 and 1 are updated periodically based on <code>val</code> and <code>secondSensorVal</code>.</li>
        <li>The <code>KMESerial</code> library handles the communication and switch state changes, and is also used for time synchronization.</li>
    </ul>
</body>
</html>







