#ifndef SPOOF_H
#define SPOOF_H

#include <libnet.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_spoof(const char *src_ip, const char *dst_ip, int dst_port, int src_port, const char *packet_type);
int send_spoofed_packet();
void cleanup_spoof();

#endif
