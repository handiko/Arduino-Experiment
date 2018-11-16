# Serial GPS RX

Using an Arduino UNO board and GPS module uBlox CN-06 as a GPS receiver.

## Dependencies

* Arduino IDE (of course)
* GPS serial output is read using Arduino IDE's Serial Monitor.

## Installation

* Give the GPS module the proper +5V power and GND.
* Connect TXD pin from GPS module to the pin-1 of the Arduino UNO.
* Set serial monitor's baudrate to 9600 baud.
* Upload the skecth.

## Operation

Basically the Arduino UNO does nothing except to set it's pin-1 as an input, to ensure high impedance condition.
We are just using the Arduino's built-in USB-to-TTL for interfacing the GPS module to the computer.

Serial monitor's output (GPS wasn't achive locked condition yet)
![alt text](https://github.com/handiko/Arduino-Project/blob/master/Serial_GPS_RX/Arduino-UNO_CN-06_GPS_output.png)

...

