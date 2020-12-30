#include <string.h>
#include "wave_comm.h"

int raw_socket(char *type, int timeout)
{
    if (type == NULL)
        return -1;
    
    int sock = -1;
    int proto, ret;
    struct timeval tv;
    
    if(strcmp(type, "ICMP") == 0)
        proto = IPPROTO_ICMP;
    else if (strcmp(type, "") == 0)
        ;
    
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

int raw_ip4_send(int sock, u8 * msg)
{
    int n_send = -1;
    target_t target;
    target.addr_ver_4 = "172.18.253.193";
    target.port = 0;
    
    
    /*check msg and socket*/
    if (msg == NULL || sock == -1)
        return -1;
    
    /*fill up the ip v4*/
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = target.port;
    inet_aton(target.addr_ver_4, 
            (struct in_addr*)&addr.sin_addr.s_addr);
    
    n_send = sendto(sock, msg, sizeof(icmp), 0,
        (struct sockaddr*)addr, sizeof(*addr));
    
    if (n_send <= 0){
        printf("send failed, n_send:[%s].\n", n_send);
        return -1;
    }
    return n_send;
}





