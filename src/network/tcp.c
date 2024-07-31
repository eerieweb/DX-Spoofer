#include "network_utils.h"

libnet_ptag_t build_tcp_packet(libnet_t *libnet_ctx, uint16_t src_port, uint16_t dst_port) {
    return libnet_build_tcp(
        src_port,                       
        dst_port,                       
        libnet_get_prand(LIBNET_PRu32), 
        0,                              
        TH_SYN,                         
        32767,                          
        0,                              
        0,                              
        LIBNET_TCP_H,                   
        NULL,                           
        0,                              
        libnet_ctx,                     
        0                               
    );
}

int build_and_send_tcp_packet(libnet_t *libnet_ctx, uint32_t src_ip, uint32_t dst_ip, uint16_t src_port, uint16_t dst_port) {
    libnet_ptag_t tcp_tag = build_tcp_packet(libnet_ctx, src_port, dst_port);
    if (tcp_tag == -1) {
        fprintf(stderr, "libnet_build_tcp() failed: %s\n", libnet_geterror(libnet_ctx));
        return -1;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H,   
        0,                              
        libnet_get_prand(LIBNET_PRu16), 
        0,                              
        64,                             
        IPPROTO_TCP,                    
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
