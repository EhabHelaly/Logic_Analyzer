## Graph Shortcut keys
* mouse left button (horizontal drag) --> move left/right through graph
* mouse scroll button (scroll) --> zoom in/out through graph
* mouse right button (press) --> display signal parameters at current position 
* mouse right button (press + CTRL down) --> copy current time position to Analyze Start Edit Box
* mouse right button (press + ALT down) --> copy current time position to Analyze End Edit Box

## Protocols Decoding
* I2C
	- a valid i2c frame must start with [start/repeated start] condtion and end with [repeated start/stop] condition
	- supports clock stretching 
	- supports Ack/Nack display of slave addresses and tranceived data bytes
* SPI
	- currently decoding SPI signal with configuration [CPOL=0, CPHA=1, MSB sent first] 
* NEC
	- supports both extended NEC versions (NEC1, NECx2)


