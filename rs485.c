#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <assert.h>

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <linux/serial.h>

/* Add your serial device below here, USB0 is just an example */
#define SERIAL_DEVICE "/dev/ttyUSB0"

int main (void) {
    
    struct serial_rs485 rs485conf;

    /* Open your specific device (e.g., /dev/mydevice): */
    int fd = open (SERIAL_DEVICE, O_RDWR);
  
    if (fd < 0) {
        /* Error handling. See errno. */
        assert("Failed to open the serial device\n");
    }

    /* Don't forget to read first the current state of the RS-485 options with ioctl.
    If You don't do this, You will destroy the rs485conf.delay_rts_last_char_tx
    parameter which is automatically calculated by the driver when You opens the
    port device. */
    if (ioctl (fd, TIOCGRS485, &rs485conf) < 0)
        fprintf(stderr, "TIOCGRS485 ioctl not supported.\n");
  
  	/* Enable RS485 mode: */
  	rs485conf.flags |= SER_RS485_ENABLED;

  	/* Set logical level for RTS pin equal to 1 when sending: */
  	rs485conf.flags |= SER_RS485_RTS_ON_SEND;
  	/* or, set logical level for RTS pin equal to 0 when sending: */
  	rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);

  	/* Set logical level for RTS pin equal to 1 after sending: */
  	rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
  	/* or, set logical level for RTS pin equal to 0 after sending: */
  	rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);

  	/* Set rts delay before send, if needed: */
  	rs485conf.delay_rts_before_send = 0;

  	/* Set rts delay after send, if needed: */
  	rs485conf.delay_rts_after_send = 0;
  	/* Set this flag if you want to receive data even whilst sending data */
  	rs485conf.flags |= SER_RS485_RX_DURING_TX;

  	if (ioctl (fd, TIOCSRS485, &rs485conf) < 0)
        fprintf(stderr, "TIOCSRS485 ioctl not supported.\n");

  	/* Use read() and write() syscalls here... */
    int w_ret, r_ret;
    uint8_t buf[256];

    fcntl(fd, F_SETFL, 0);

    /*Write the data in the serial device */
    w_ret = write(fd, buf, sizeof(buf));
    if (w_ret <= 0) {
      if (w_ret == 0) {
          fprintf(stderr, "%s: write failed, EOF\n", SERIAL_DEVICE);
          return -1;
      }

      fprintf(stderr, "%s: write failed %s\n", SERIAL_DEVICE, strerror(errno));
      return 0;
  }

    /* Read the data in serial device */
    r_ret = read(fd, buf, sizeof(fd));
    if (r_ret <=0) {
      if (r_ret == 0) {
        fprintf(stderr, "%s Failed to read: EOF \n", SERIAL_DEVICE);
      }
      if (errno != EAGAIN) {
        close(fd);
        return 0;
      }
    }
  
  	/* Close the device when finished: */
  	if (close (fd) < 0)
        fprintf(stderr, "Failed to close the fd\n");

  return 0;
}
