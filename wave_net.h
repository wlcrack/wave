#ifndef _WAVE_COMM_H_
#define _WAVE_COMM_H_

#include "wave_util.h"

int raw_socket(char *type, int timeout);
int raw_ip4_send(int sock, u8 * msg, int len);
void raw_sock_close(int sock);

#endif