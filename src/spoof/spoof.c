#include "spoof.h"
#include "../network/network_utils.h"
#include "../utils/ip_utils.h"

static libnet_t *libnet_ctx;
static uint32_t src_ip_addr, dst_ip_addr;
static uint16_t dst_port_num, src_port_num;
static char *pkt_type;

int init_spoof(const char *src_ip, const char *dst_ip, int dst_port, int src_port, const char *packet_type) {
    char errbuf[LIBNET_ERRBUF_SIZE];

    libnet_ctx = libnet_init(LIBNET_RAW4, NULL, errbuf);
    if (libnet_ctx == NULL) {
        fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
        return -1;
    }

    src_ip_addr = ip_to_uint32(libnet_ctx, src_ip);
    dst_ip_addr = ip_to_uint32(libnet_ctx, dst_ip);
    dst_port_num = dst_port;
    src_port_num = src_port ? src_port : libnet_get_prand(LIBNET_PRu16);
    pkt_type = strdup(packet_type);

    if (src_ip_addr == -1 || dst_ip_addr == -1) {
        fprintf(stderr, "Invalid IP address\n");
        libnet_destroy(libnet_ctx);
        return -1;
    }

    return 0;
}

int send_spoofed_packet() {
    if (strcmp(pkt_type, "TCP") == 0) {
        return build_and_send_tcp_packet(libnet_ctx, src_ip_addr, dst_ip_addr, src_port_num, dst_port_num);
    } else if (strcmp(pkt_type, "UDP") == 0) {
        return build_and_send_udp_packet(libnet_ctx, src_ip_addr, dst_ip_addr, src_port_num, dst_port_num);
    } else if (strcmp(pkt_type, "ICMP") == 0) {
        return build_and_send_icmp_packet(libnet_ctx, src_ip_addr, dst_ip_addr);
    } else {
        fprintf(stderr, "Unsupported packet type: %s\n", pkt_type);
        return -1;
    }
}

void cleanup_spoof() {
    libnet_destroy(libnet_ctx);
    free(pkt_type);
}
