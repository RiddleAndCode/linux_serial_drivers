//
// Created by firat on 14.07.21.
//
#include <stdio.h>
#ifndef SERIAL_READ_LORA_E5_SERIAL_DRIVERS_H
#define SERIAL_READ_LORA_E5_SERIAL_DRIVERS_H

int open_serial_port(char * port_name);
ssize_t write_command(char *at_command);
ssize_t read_response(char *response_buffer, size_t buff_size);
int close_serial_port();


#endif //SERIAL_READ_LORA_E5_SERIAL_DRIVERS_H
