# ArduinoSquareWaveGenerator1Khz
Two Channel Square Wave generator using Arduino Uno (Range 16Hz ~ 1024Hz)

This is a simple Square Wave Generator (16Hz ~ 1024Hz) using a Look Up Table (LUT) and Timer 1.
Timer 1 is set as a free running counter and both Output Compare registers are used to generate the desired frequency.
Output pins toogle automatically controlled by the Waveform Generator.

Input control is done though 4 variable resistors (2 per channel, one for Fast and the other for Slow speed).

This project will later change to receive the values over the serial port.

This project is free for everyone to use, modify, distribute
