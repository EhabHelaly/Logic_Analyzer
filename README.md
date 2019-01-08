# Logic_Analyzer
Turns your cheap AVR into powerful logic analyzer up to 400k sample rate. it's a very handy tool for debugging communication protocols, GPIOs, digital and analog sensors and modules

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/H4AfqcDREzQ/0.jpg)](https://www.youtube.com/watch?v=H4AfqcDREzQ)

## Hardware Requirments
* Atmega16/32/64/128
* USB to TTL module
* 8M to 16M Crystal (or use internal 8M, the higher the F_CPU the higher sample rate)
* PC (currently windows only)

## Features
* 4 Operation modes
	- 8 channel digital input display up to 200k sample rate
	- 4 channel digital input display up to 400k sample rate
	- 10 bit resolution analog input display up to 100k sample rate
	- 8 bit resolution analog input display up to 200k sample rate
* Digital and Analog signal analysis including
	- Frequency (min,max,average)
	- Pulse width (min,max)
	- Duty cycle
	- Other parameterts
* Digital protocol decoding
	- I2C
	- SPI
	- NEC (IR protocol)
* Supports digitalization of analog signal using schmitt trigger
* Analyzes different parts of recoreded signal
* Supports multiple hardware clock frequency configurations (.hex code is independent of clock frequency)
* Configurable internal pull-up resistances when capturing signals 
* 2 different color themes for better display

## Dependancies
* Qt v5.7 or equivalent 
* qcustomplot v2.0 (source code is already included in project)

