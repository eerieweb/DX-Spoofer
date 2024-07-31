#include "network_utils.h"
#include "../utils/ip_utils.h"

libnet_ptag_t build_tcp_packet(libnet_t *libnet_ctx, uint16_t src_port, uint16_t dst_port);
libnet_ptag_t build_udp_packet(libnet_t *libnet_ctx, uint16_t src_port, uint16_t dst_port);
libnet_ptag_t build_icmp_packet(libnet_t *libnet_ctx);

int build_and_send_tcp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip, uint16_t src_port, uint16_t dst_port);
int build_and_send_udp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip, uint16_t src_port, uint16_t dst_port);
int build_and_send_icmp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip);
