# WiFi LED Control Application

## Project Scope
The purpose of this project is to implement a WiFi module, specifically a mobile application that controls the effects displayed on an LED stripe using designated buttons. Through this project, we learn how to establish a connection between a mobile application and an Arduino board through a WiFi module, as well as how LED stripes function and the multitude of effects we can create using them.

## Components Used
For this project, the following components were utilized:
- USB cable, cut at one end to power the LEDs from a socket or any other power source such as a laptop's USB port or an external battery.
- ESP8266 ESP-12E CH340G NodeMCU V3 Development Board used for code implementation.
- Male-to-male jumper wires, cut open to connect the wires from the cut cable to the LED wires, which were subsequently insulated.

## Project Design and Implementation Details
1. **Mobile Application Design:**
   - The mobile application was designed to include 8 buttons that toggle between 8 operational modes.
   - A color selector, presented as a zebra pattern, allows users to choose any desired color to be displayed on the LEDs.

2. **Connection and Communication:**
   - Once the mobile application was ready, virtual ports were set up using the Blynk application in the Arduino code.
   - Values of 0 or 1, representing button states (pressed or not), were transmitted to the Arduino code. A value of 1 is sent when a button is pressed, and 0 when it is released.

3. **Libraries and Modules:**
   - The necessary libraries, including FastLed and Blynk, were installed for coding.
   - The required library for the ESP8266 board was also incorporated.
   - The built-in WiFi module on the ESP8266 board was utilized to establish an internet connection.

## Getting Started
1. Connect the cut end of the USB cable to the power source.
2. Connect the jumper wires to the LED wires after isolating them.
3. Upload the Arduino code to the ESP8266 board.
4. Open the Blynk mobile application and control the LED effects using the designated buttons.

## Acknowledgments
This project was made possible through the collaborative efforts of [Juhasz Norbert](https://github.com/juhasznorbert99)

