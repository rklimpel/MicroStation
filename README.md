# MicroStation

### Run Microcontroller Code

requirements:
- Visual Studio Code with installed 'platformio-ide' Extension

steps:
- open `wifi-controller` root folder in visual studio code
- platformio should index the project so you can build and `upload to esp8266 chip` via statusbar icons
- open `main-controller` root folder in visual studio code 
- platformio should index the project so you can build and `upload to main controller board (arduino)` via statusbar icons

### How to upload to ESP8266 Wifi Chip?

Build a circuit like this (neglect GPIO_15):

<img src="https://tttapa.github.io/Images/ESP8266-2.png" alt="alt text" width="400" height="300">

Here's a little hint for the ESP8266 pins assignment:

<img src="https://components101.com/sites/default/files/component_pin/ESP8266-Pinout.png" alt="alt text" width="250" height="150">

Connect RX und TX with the Controller Boards (Arduino) RX and TX pins.
Connect Connect Controller Boards (Arduino) RESET pin to GND pin. This will setup the board as serial bridge.


Follow this steps to boot into progamming mode:
1. press and hold the reset button
2. press and hold the program button
3. release the reset button, the ESP will boot in program mode
4. release the program button
5. upload the sketch
6. press reset button to boot into normal mode again after upload finished
