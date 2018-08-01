import sys
import serial
 
ser = serial.Serial(
    port='/dev/ttyUSB0', 
    baudrate=9600, 
    timeout=1,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)  

linecounter=0
bytecounter=0
bytesperline = 8
while True:     
    bytesToRead = ser.inWaiting()
    
    if bytesToRead>0:
        value=ser.read(1)
        if (bytecounter % bytesperline) == 0:
            print "\n[%04X] - " % bytecounter ,
            sys.stdout.flush()
            linecounter=linecounter+1
             
        print "%02X " % ord(value) ,
        sys.stdout.flush()
        bytecounter=bytecounter+1
        if bytecounter==0:
            print
            bytecounter=0
