#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdlib.h>

void init_logging();
void log_packet_info(int packet_number, const char *src_ip, const char *dst_ip, int dst_port, const char *packet_type);

#endif
