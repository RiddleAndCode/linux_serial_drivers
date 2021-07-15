//
// Created by firat on 14.07.21.
//
#include "Lora_E5_serial_drivers.h"
#include <errno.h>
#include <fcntl.h>

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static int file_descriptor;
static struct termios oldtio;

int open_serial_port(char *port_name) {
    struct termios options;
    file_descriptor = open(port_name, O_RDWR | O_NOCTTY);

    if (file_descriptor < 0) {
        printf("Error opening serial port\n");
        exit(1);
    }

    bzero(&options, sizeof(options));
    tcgetattr(file_descriptor, &oldtio); /* save current port settings */

    /*
          BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
          CS8     : 8n1 (8bit,no parity,1 stopbit)
          CLOCAL  : local connection, no modem control
          CREAD   : enable receiving characters
        */
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
    options.c_cc[VTIME] = 1;
    options.c_cc[VMIN] = 255;
    tcflush(file_descriptor, TCIFLUSH);
    tcsetattr(file_descriptor, TCSANOW, &options);


}

ssize_t write_command(char *at_command) {
    size_t cmd_len = strlen(at_command);
    ssize_t ret = write(file_descriptor, at_command, cmd_len);
    if ( ret < cmd_len) {
        printf("Write error - %s \n", strerror(errno));
    }
    return ret;

}

ssize_t read_response(char *response_buffer, size_t buff_size) {
    ssize_t n = read(file_descriptor, response_buffer, buff_size);
    if ( n < 0) {
        printf("Read error - %s \n", strerror(errno));
    }
    return n;

}

int close_serial_port(){

    tcsetattr(file_descriptor, TCSANOW, &oldtio);
    int n = close(file_descriptor);
    return n;

}

