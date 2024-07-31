#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spoof/spoof.h"
#include "utils/logging.h"
#include "utils/ip_utils.h"

void print_usage(const char *progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Options:\n");
    printf("  -s <source IP>       : Source IP address\n");
    printf("  -d <destination IP>  : Destination IP address\n");
    printf("  -p <destination port>: Destination port\n");
    printf("  -P <source port>     : Source port (optional)\n");
    printf("  -t <type>            : Packet type (TCP, UDP, ICMP)\n");
    printf("  -n <number>          : Number of packets to send (default: 1)\n");
    printf("  -l                   : Enable logging\n");
    printf("  -h                   : Show this help message\n");
}

int main(int argc, char *argv[]) {
    char *src_ip = NULL;
    char *dst_ip = NULL;
    int dst_port = 0, src_port = 0;
    int num_packets = 1;
    int enable_logging = 0;
    char *packet_type = "TCP";

    if (argc == 1) {
        print_usage(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            src_ip = argv[++i];
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            dst_ip = argv[++i];
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            dst_port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-P") == 0 && i + 1 < argc) {
            src_port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            packet_type = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            num_packets = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-l") == 0) {
            enable_logging = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!src_ip || !dst_ip || !dst_port) {
        fprintf(stderr, "Missing required arguments.\n");
        print_usage(argv[0]);
        return 1;
    }

    if (enable_logging) {
        init_logging();
    }

    if (init_spoof(src_ip, dst_ip, dst_port, src_port, packet_type) != 0) {
        fprintf(stderr, "Failed to initialize IP spoofing.\n");
        return 1;
    }

    for (int i = 0; i < num_packets; i++) {
        if (send_spoofed_packet() != 0) {
            fprintf(stderr, "Failed to send spoofed packet.\n");
            cleanup_spoof();
            return 1;
        }
        if (enable_logging) {
            log_packet_info(i + 1, src_ip, dst_ip, dst_port, packet_type);
        }
    }

    printf("Spoofed %d packet(s) successfully.\n", num_packets);
    cleanup_spoof();

    return 0;
}
