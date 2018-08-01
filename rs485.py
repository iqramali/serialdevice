"""It sends character on the RS485 bus on at91 board(it can be any board) that is connected to ttyS0"""

import serial,fcntl, struct
 
ser = serial.Serial(
    port='/dev/ttyS0', 
    baudrate=9600, 
    timeout=1,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)  
 
fd=ser.fileno()
 
ser.write("0123456789") # Send characters on the RS485 bus
s = ser.read(1)         # Wait for char
print s
ser.close()
