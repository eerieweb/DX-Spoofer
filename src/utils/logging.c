#include "logging.h"

void init_logging() {
    FILE *log_file = fopen("spoofer_log.txt", "w");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "Starting spoofing session...\n");
    fclose(log_file);
}

void log_packet_info(int packet_number, const char *src_ip, const char *dst_ip, int dst_port, const char *packet_type) {
    FILE *log_file = fopen("spoofer_log.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "Packet %d: %s -> %s:%d [%s]\n", packet_number, src_ip, dst_ip, dst_port, packet_type);
    fclose(log_file);
}
