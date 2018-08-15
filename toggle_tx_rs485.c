/* Example program, delay specifiying the amount of time the transmitter is to be enabled before any data is 
sent can be configured as well. */

#include <fcntl.h>
#include <termios.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/serial.h>

void rs485_mode(int on) {
	struct serial_rs485 rs485conf;

	if(on) {
		rs485conf.flags |= SER_RS485_ENABLED;
		rs485conf.delay_rts_before_send = 0x00000004;
		ioctl(fd, TIOCSRS485, &rs485conf);
	}	else {
		rs485conf.flags &= ~SER_RS485_ENABLED;
		ioctl(fd, TIOCSRS485, &rs485conf);
	}
}

/* Disbale the receiver while transmit, since transmit and receive lines are shared in a RS485 two wire bus, 
it might be useful to disable the receiver during a transmit to avoid reading back currently send data. 
For that case use c_cflag in struct termios.
*/
void rs485_receiver(int on) {
	struct termios options;

	tcgetattr(fd, &options);
	if(on)
		options.c_cflag |= CREAD;
	else
		options.c_cflag &= ~CREAD;
	tcsetattr(fd, TCSANOW, &options);
	fcntl(fd, F_SETFL, FNDELAY);
}


int main (void) {
   rs485_mode(1);
   rs485_receiver(1);
  return 0;
}
