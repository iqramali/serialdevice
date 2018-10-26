# Serialdevice

Serial device, RS485 programming C and Python

## Introduction to RS485 

RS485 uses the same wires to send and receive, you need to set a microcontroller output to the apropriate mode to command the RS485 transceiver to work in the aprorpriate direction.

### Hardware:

* RS485 requires a RS485 tranceiver chip to be connected to an USART that is not level converted to RS232. 
* In general USART1 is ```/dev/ttyS*```. 
* Recommended to use the USART's RTS line to control transmitter enable since RTS is used by the serial kernel driver in RS485 mode.

### Software
* We just treat rs485 as normal serial device, the main difference is that the RS485 tranceiver needs to be considered correctly.
* Software should either be aware of that or should disable the receiver during transmit.

#### How to enable or disable RS485 mode?
* Using ```linux/serial.h```. RTS is not used for any handshake in RS485 mode.
* RTS is used to enable or disbale the transmitter an is handled by the serial driver automatically.

All the program here are compiled only in Linux environment.

Comiple the C code using gcc.
terminal.c program reads the response from serial device with certain timeout period that 0.5 seconds, this timeout is configurable.

```
gcc -g terminal.c
gcc -g rs485.c
```

Run the python script to read the serial device line.

### How to access the serial device from the Linux user space?

From Linux user space, one can use the command line utility stty to configure the serial speed. 
Then the port can be treated as as a regular file:
```
 stty -F /dev/ttyS1 115200
 echo Test > /dev/ttyS1
```

To set extra delays for TXEN/RTS signal before and after transmitted packet using stty
```
 stty -F $SERIAL_DEV rs485delaybefore 100
 stty -F $SERIAL_DEV rs485delayafter 100
```

### Use of ioctl() in C

The ioctl() calls (I/O Control) are generic calls that can be used to communicate with wide variety of hardware devices on a Linux system. Simple example how to use ioct() calls to set and clear the RTS and DTR pins .

Syntax: ``` ioct(fd,command,argument);```

#### Example using ioctl.

```
#include <sys/ioctl.h> //ioctl() call defenitions
main()
{
   int fd;
   fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY );
  
   int RTS_flag;
   RTS_flag = TIOCM_RTS;
   ioctl(fd,TIOCMBIS,&RTS_flag);//Set RTS pin
   getchar();
   ioctl(fd,TIOCMBIC,&RTS_flag);//Clear RTS pin
   //Checking the condition of DTR
     ioctl(fd, TIOCMGET, &serial);
   if (serial & TIOCM_DTR)
       puts("TIOCM_DTR is not set");
   else
       puts("TIOCM_DTR is set");
   close(fd);
}
```
Footnote: TIOCMBIS (const int *argp) set the indicated modem bits.

