# ArduinoSquareWaveGenerator1Khz
Two Channel Square Wave generator using Arduino Uno (Range 16Hz ~ 1024Hz)

This is a simple Square Wave Generator (16Hz ~ 1024Hz) using a Look Up Table (LUT) and Timer 1.
Timer 1 is set as a free running counter and both Output Compare registers are used to generate the desired frequency.
Output pins toogle automatically controlled by the Waveform Generator.

There are 2 versions of this code:
1) Uses 4 variable resistors to set the output frequency (2 per channel, using a pin to switch the preset).
2) Uses a Serial Port protocol to set the output frequency (2 per channel, again using a pin to switch the preset, with the option to save the values on EEPROM so they get restored on power on).

This project was created to help a PLC controller interface 2 stepper motors. The PLC needs to control 2 steppers, with a fast and slow speed on each. It uses a pin for each channel to switch between fast and slow.

This project is free for everyone to use, modify, distribute
