#ifndef _WAVE_COMM_H_
#define _WAVE_COMM_H_

#include "wave_util.h"

typedef enum
{
    ICMP = 0,
    TCP_SYN     = 1,
    TCP_FIN     = 2,
    TCP_ACK     = 3,
    TCP_WINDOWN = 4,
    UDP         = 5
}SOCK_TYPE;

int raw_socket(char *type, int timeout);
int raw_ip4_send(int sock, u8 * msg, int len);
void raw_sock_close(int sock);

#endif