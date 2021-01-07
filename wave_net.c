#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "wave_net.h"
#include "wave_discovery.h"

int raw_socket(SOCK_TYPE type, int timeout)
{
    if (type == NULL)
        return -1;
    
    int sock = -1;
    int proto, ret;
    struct timeval tv;
    
    if(type == ICMP)
        proto = IPPROTO_ICMP;
    else
        proto = IPPROTO_ICMP;
    sock = socket(AF_INET, SOCK_RAW, proto);
    if (sock == -1) {
        printf("socket create failed, type:[%s]\n", type);
        return -1;
    }
    /*set socket timeout*/
    if (timeout == 0 || timeout < 1000000)
        timeout = 3000000; //3sec
    
    /*set socket revice timeout*/
    tv.tv_sec = 0;
    tv.tv_usec = timeout;
    
    ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    if(ret == -1){
        printf("sock option set failed.\n");
        return -1;
    }
    return sock;
}

int raw_ip4_send(int sock, u8 * msg, int len)
{
    int n_send = -1;
    target_t target;
    target.addr_ver_4 = "172.18.253.193";
    target.port = 0;
    
    
    /*check msg and socket*/
    if (msg == NULL || sock == -1)
        return -1;
    
    /*fill up the ip v4*/
    /*
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = target.port;
    inet_aton(target.addr_ver_4, 
            (struct in_addr*)&addr.sin_addr.s_addr);
    
    sendto(sock, msg, len, 0,(struct sockaddr*)addr, sizeof(addr));*/
    
    return n_send;
}


void raw_sock_close(int sock)
{
    close(sock);
}


