#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wave_net.h"
#include "wave_discovery.h"

u8 *build_icmp_echo_pack(void)
{
    icmp_pack_t *icmp_echo = NULL;
    
    icmp_echo = (icmp_pack_t *) malloc(sizeof(icmp_pack_t));
    if(icmp_echo == NULL)
    {
        printf("build icmp echo pack failed , out of memory.\n");
        return NULL;
    }
    icmp_echo->offset = sizeof(icmp_pack_t);
    icmp_echo->type = '\x08';
    icmp_echo->code = '\x00';
    icmp_echo->seq  = '\x02';
    icmp_echo->ident= '\x03';
    /*caculte checksum*/
    icmp_echo->checksum = '\x00';
    
    return (u8 *)icmp_echo;
}

u8 *build_icmp_timestamp_pack(void)
{
    return NULL;
}

u8 *build_icmp_mask_pack(void)
{

    return NULL;
}

/*
*
*return:icmp pack
*/
u8 * build_icmp_pack(ICMP_TYPE type)
{
    if (type == ICMP_ECHO)
        return build_icmp_echo_pack();
    else if (type == ICMP_TIMESTAMP)
        return build_icmp_timestamp_pack();
    else if (type == ICMP_MASK)
        return build_icmp_mask_pack();
    else
        printf("build icmp packet failed , type error:[%d]\n", type);
    return NULL;
}

int wave_icmp_scan(ICMP_TYPE type)
{
    u8 * icmp_pack = NULL;
    int sock = -1, n_send = -1;
    icmp_pack_t *icmp_echo = NULL;
    icmp_pack = build_icmp_pack(type);
    if (icmp_pack == NULL){
        return -1;
    }
    icmp_echo = (icmp_pack_t *)icmp_pack;
    sock = raw_socket(ICMP_ECHO, 10);
    if (sock == -1)
        return -1;
    
    raw_ip4_send(sock, icmp_pack, icmp_echo->offset);
    raw_sock_close(sock);
    
}


