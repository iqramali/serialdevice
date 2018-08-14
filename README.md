# serialdevice

serial device, RS485 programming C and Python

All the program here are compiled only in Linux environment.

Comiple the C code using gcc.
terminal.c program reads the response from serial device with certain timeout period that 0.5 seconds, this timeout is configurable.

```
gcc -g terminal.c
gcc -g rs485.c

```

Run the python script to read the serial device line.

How to access the serial device from the Linux user space?

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
   close(fd);
}
```
