## Hardware
* Atmega16/32 MCAL codes are the same 
* Atmega64/128 MCAL codes are the same (except for adc.c; ADSRA register bit 5 is named ADATE/ADFR  )
* Code is independent of operating clock frequency
* Clock frequency determines the max sample rate the device can operate on
	- 8M up to 200k sample rate
	- 10M up to 250k sample rate
	- 12M up to 300k sample rate
	- 14M up to 350k sample rate
	- 16M up to 400k sample rate
