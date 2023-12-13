# HACKABLE SIGN
This electronic sign project uses an ESP8266 broadcasting an SSID. It allows users to connect to the network where they can interact with a web server that allows an authenticated user to change the text on a dot matrix display (MAX7219). Non-authenticated users can attempt to hack the web server to change the text.

Most of the code used to communicate to the MAX7219 dot matrix display was taken from Micro Controllers Lab https://microcontrollerslab.com/max7219-led-dot-matrix-display-esp8266-nodemcu-tutorial/.

## Hardware requirements
- ESP8266 
- MAX7219 Dot Matrix Display
- Micro USB cable
- Computer with the Arduino IDE (or PlatformIO; however, the instructions below will use the Arduino IDE)
- Wires

## Default settings:
SSID: hackable-sign
Web portal: http://192.168.4.22

## Connect MAX7219 to ESP8266
The following table shows how to connect the pins on the MAX7219 display to the ESP8266 using wires. If the ESP8266 has pins pre-sodered you can use the female to female wires that typically come bundled with the MAX7219. 
```
+---------------------+
|  MAX7219 | ESP8266  |
+---------------------+
|    VCC   |   3.3V   |
|    GND   |   GND    |
|    DIN   |   D7     |
|    CS    |   D8     |
|    CLK   |   D5     |
+---------------------+
```

## Arduino Setup
COMING SOON lol
