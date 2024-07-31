#include "ip_utils.h"

uint32_t ip_to_uint32(libnet_t *libnet_ctx, const char *ip_str) {
    return libnet_name2addr4(libnet_ctx, ip_str, LIBNET_RESOLVE);
}
