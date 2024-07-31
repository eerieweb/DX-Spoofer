#include "network.h"
#include "utils.h"

libnet_ptag_t build_tcp_packet(libnet_t *libnet_ctx, uint16_t src_port, uint16_t dst_port) {
    return libnet_build_tcp(
        src_port,                       // source port
        dst_port,                       // destination port
        libnet_get_prand(LIBNET_PRu32), // sequence number
        0,                              // acknowledgement number
        TH_SYN,                         // control flags
        32767,                          // window size
        0,                              // checksum (0 for libnet to autofill)
        0,                              // urgent pointer
        LIBNET_TCP_H,                   // TCP packet size
        NULL,                           // payload (NULL for none)
        0,                              // payload size
        libnet_ctx,                     // libnet context
        0                               // protocol tag (0 to create a new one)
    );
}

libnet_ptag_t build_udp_packet(libnet_t *libnet_ctx, uint16_t src_port, uint16_t dst_port) {
    return libnet_build_udp(
        src_port,                       // source port
        dst_port,                       // destination port
        LIBNET_UDP_H,                   // length of UDP packet (header + data)
        0,                              // checksum (0 for libnet to autofill)
        NULL,                           // payload (NULL for none)
        0,                              // payload size
        libnet_ctx,                     // libnet context
        0                               // protocol tag (0 to create a new one)
    );
}

libnet_ptag_t build_icmp_packet(libnet_t *libnet_ctx) {
    return libnet_build_icmpv4_echo(
        ICMP_ECHO,                      // type
        0,                              // code
        0,                              // checksum (0 for libnet to autofill)
        libnet_get_prand(LIBNET_PRu16), // identifier
        libnet_get_prand(LIBNET_PRu16), // sequence number
        NULL,                           // payload (NULL for none)
                0,                              // payload size
        libnet_ctx,                     // libnet context
        0                               // protocol tag (0 to create a new one)
    );
}

int build_and_send_tcp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip, uint16_t src_port, uint16_t dst_port) {
    libnet_ptag_t tcp_tag = build_tcp_packet(libnet_ctx, src_port, dst_port);
    if (tcp_tag == -1) {
        fprintf(stderr, "libnet_build_tcp() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H,   // length of IP packet (header + data)
        0,                              // TOS
        libnet_get_prand(LIBNET_PRu16), // IP ID
        0,                              // fragmentation
        64,                             // TTL
        IPPROTO_TCP,                    // upper layer protocol
        0,                              // checksum (0 for libnet to autofill)
        src_ip,                         // source IP
        dst_ip,                         // destination IP
        NULL,                           // payload (NULL for none)
        0,                              // payload size
        libnet_ctx,                     // libnet context
        0                               // protocol tag (0 to create a new one)
    );

    if (ip_tag == -1) {
        fprintf(stderr, "libnet_build_ipv4() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    int bytes_written = libnet_write(libnet_ctx);
    if (bytes_written == -1) {
        fprintf(stderr, "libnet_write() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    return 0;
}

int build_and_send_udp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip, uint16_t src_port, uint16_t dst_port) {
    libnet_ptag_t udp_tag = build_udp_packet(libnet_ctx, src_port, dst_port);
    if (udp_tag == -1) {
        fprintf(stderr, "libnet_build_udp() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_UDP_H,   
        0,                              
        libnet_get_prand(LIBNET_PRu16), 
        0,                              
        64,                             
        IPPROTO_UDP,                    
        0,                              
        src_ip,                         
        dst_ip,                         
        NULL,                           
        0,                              
        libnet_ctx,                     
        0                               
    );

    if (ip_tag == -1) {
        fprintf(stderr, "libnet_build_ipv4() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    int bytes_written = libnet_write(libnet_ctx);
    if (bytes_written == -1) {
        fprintf(stderr, "libnet_write() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    return 0;
}

int build_and_send_icmp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip) {
    libnet_ptag_t icmp_tag = build_icmp_packet(libnet_ctx);
    if (icmp_tag == -1) {
        fprintf(stderr, "libnet_build_icmpv4_echo() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H, 
        0,                                    
        libnet_get_prand(LIBNET_PRu16),       
        0,                                    
        64,                                   
        IPPROTO_ICMP,                         
        0,                                    
        src_ip,                               
        dst_ip,                               
        NULL,                                
        0,                                    
        libnet_ctx,                         
        0                                     
    );

    if (ip_tag == -1) {
        fprintf(stderr, "libnet_build_ipv4() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    int bytes_written = libnet_write(libnet_ctx);
    if (bytes_written == -1) {
        fprintf(stderr, "libnet_write() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    return 0;
}

