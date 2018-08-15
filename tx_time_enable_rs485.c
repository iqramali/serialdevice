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

int main (void) {
  rs485_mode(1);
  return 0;
}
