#ifndef UTILS_H
#define UTILS_H

#include <libnet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t ip_to_uint32(libnet_t *libnet_ctx, const char *ip_str);
void init_logging();
void log_packet_info(int packet_number, const char *src_ip, const char *dst_ip, int dst_port, const char *packet_type);

#endif
