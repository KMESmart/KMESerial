# KMESerial
This setup involves an ESP32 serving as a central hub for IoT communication, receiving sensor data from an Arduino via serial communication. The data can be processed and managed using the "KME Smart" application.<br>
<br>
2. Hardware Setup
ESP32: Acts as the host device.<br>
Arduino: Sends sensor values to the ESP32.and control gpios<br>
Connections: Connect the Arduino’s TX pin to the ESP32’s RX pin, and the Arduino’s RX pin to the ESP32’s TX pin. Ensure that both devices share a common ground
