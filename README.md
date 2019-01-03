# Logic_Analyzer
Turns your cheap AVR into powerfull logic analyzer up to 400k sample rate
its a very handy tool for debugging communication protocols, GPIOs, digital and analog sensors and modules

Hardware Requirments
====================
* Atmega16/32/64/128
* USB to TTL module
* PC (currently windows only)

Features
========
* 4 Operation modes
	- 8 channel digital input display up to 200k sample rate
	- 4 channel digital input display up to 400k sample rate
	- 10 bit resolution analog input display up to 100k sample rate
	- 8 bit resolution analog input display up to 200k sample rate
* Digital and Analog signal anaysis
	- Frequency (min,max,average)
	- Pulse width (min,max)
	- Duty cycle
* Digital protocol decoding
	- I2C
	- SPI
	- NEC (IR protocol)
* Supports digitalization of analog signal using schmitt trigger
* Supports multiple hardware clock frequency configurations (.hex code is independant of clock frequency)
* Configurable internal pull-up resistances when capturing signals 
* 2 different color themes for better display

Software Dependancies
=====================
* Qt v5.7 or equivalent 
* qcustomplot v2.0 (source code is already included in project)

