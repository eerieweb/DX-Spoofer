#include "network_utils.h"

libnet_ptag_t build_icmp_packet(libnet_t *libnet_ctx) {
    return libnet_build_icmpv4_echo(
        ICMP_ECHO,                 
        0,                           
        0,                            
        libnet_get_prand(LIBNET_PRu16), 
        1,                             
        NULL,                       
        0,                            
        libnet_ctx,                    
        0                               
    );
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

    int bytes_written
