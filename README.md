# HACKABLE SIGN
This electronic sign project uses an ESP8266 broadcasting an SSID. It allows users to connect to the network where they can interact with a web server that allows an authenticated user to change the text on a dot matrix display (MAX7219). Non-authenticated users can attempt to hack the web server to change the text.

Most of the code used to communicate to the MAX7219 dot matrix display was taken from Micro Controllers Lab https://microcontrollerslab.com/max7219-led-dot-matrix-display-esp8266-nodemcu-tutorial/.

NOTE: This project is intentionally insecure. It is meant to be hacked. 

## Hardware requirements
- ESP8266 
- MAX7219 Dot Matrix Display
- Micro USB cable
- Computer with the Arduino IDE (or PlatformIO; however, the instructions below will use the Arduino IDE)
- Wires

## Default settings:
- SSID: hackable-sign
- Web portal: http://192.168.4.1
- Web portal username: admin
- Web portal password: 31337

## Variables you may want to change:
On line 18 you can find the default text. This is the text that the device will display on boot. There is no persistence when you change the text from the web interface. 
```String text = "HACK THE PLANET!!!";```

On lines 22 and 23 you'll find the web console default credentials. There is no password to connect to the sign via WiFi. The credentials are only for when you actually try to change the text. 
```const char* http_username = "admin";```
```const char* http_password = "31337";```

On line 30 you'll find the IP address of the web interface. You should be able to change it to anything you want within the 192.168.4.0/24 range but this is not very important. The important thing to know is that this will be how you access the web interface to change the text. By default you'd go to http://192.168.4.1. 
```IPAddress local_IP(192, 168, 4, 1);```

Lastly on line 62 you can change the SSID. The default is "hackable-sign".
```const char* ssid = "hackable-sign";```

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
