#ifndef _WAVE_DISCOVERY_H_
#define _WAVE_DISCOVERY_H_

#include "wave_util.h"

#define ICMP_DATA_LEN 1500


typedef enum 
{
    ICMP_ECHO      = 0,
    ICMP_TIMESTAMP = 1,
    ICMP_MASK      = 2
}ICMP_TYPE;

typedef struct icmp_pkg 
{
    // header
    u8 type;
    u8 code;
    u16 checksum;
    u16 ident;
    u16 seq;
    u8 data[ICMP_DATA_LEN];
    u32 offset;
}icmp_pack_t;


typedef struct target
{
    char *addr_ver_4;
    short port;
    char *addr_ver_6;
}target_t;

/*pack build func*/
u8 * build_icmp_pack(ICMP_TYPE type);

/*scan func*/
int wave_icmp_scan(ICMP_TYPE type);

#endif

