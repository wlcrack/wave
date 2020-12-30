#ifndef _WAVE_COMM_H_
#define _WAVE_COMM_H_

int raw_socket(char *type, int timeout);
int raw_ip4_send(int sock, char *ip, 
                    short port, u8 * msg);

#endif