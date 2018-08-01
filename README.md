# serialdevice
serial device programming C and Python

Comiple the C code using gcc.
terminal.c program reads the response from serial device with certain timeout period that 0.5 seconds, this timeout is configurable.

gcc -g terminal.c

Run the python script to read the serial device line.

How to access the serial device from the Linux user space?

From Linux user space, one can use the command line utility stty to configure the serial speed. 
Then the port can be treated as as a regular file:

stty -F /dev/ttyS1 115200
# echo Test > /dev/ttyS1
