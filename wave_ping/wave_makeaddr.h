#ifndef _WAVE_MAKE_ADDR_
#define _WAVE_MAKE_ADDR_

#include <stdint.h>
#include "wave_list.h"

#define WAVE_HOSTLEN 128

typedef enum{
    IP_VER4 = 0,
    IP_VER6 = 1
}IP_VER_T;

typedef struct target{
    /*ipv4 , length 16*/
    char *   s_addr_4;
    /*ipv4, for s_addr*/
    uint32_t addr_4;
    /*ipv6, length 128*/
    char *   s_addr_6;
    /*ip type , ver 4 or ver 6*/
    IP_VER_T type;
    /*tcp or udp port*/
    uint16_t port;
    /*list node*/
    struct list_head list; 
}target_t;

typedef struct wave_host {
  char host[WAVE_HOSTLEN];
  IP_VER_T type;
} wave_host_t;

#endif /*end _WAVE_MAKE_ADDR_*/
