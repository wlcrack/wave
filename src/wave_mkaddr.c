#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "wave_types.h"

#define WAVE_MAX_IP_LEN 128

/*debug option*/
extern int WAVE_DEBUG;
/*host list head*/
extern LIST_HEAD_T HOST_HEAD;

typedef struct {
  char    *domain;
  char    *ip; 
  IP_E    type;
}IP_T;

static void addr_lprint() {

  HOST_T *t = NULL;
  LIST_HEAD_T *pos = NULL, *next = NULL;
  struct in_addr in;

  list_for_each_safe(pos, next, &HOST_HEAD) {
    t = list_entry(pos, HOST_T, list);
    in.s_addr = ntohl(t->ipv4);
    printf("ipv4addr:%s ipv4:%lu  ipv6:%s type:%d\n",\
          inet_ntoa(in),  t->ipv4, t->ipv6, t->type); 
  }
}

static void cidrl4(char *str) {
  
  if (!str)
    return ;
  
  struct in_addr addr;
  char buf[WAVE_MAX_IP_LEN] = {'\0'};
  char *start_ip = NULL, *end_ip = NULL;
  int  mask = 0, bit = 0;
  HOST_T *nhost = NULL;
  char *mask_p = NULL, *range_p = NULL;
  /*unsigned */
  unsigned long i = 0;
  unsigned long hladdr = 0, si_ip = 0, ei_ip = 0;

  strncpy(buf, str, WAVE_MAX_IP_LEN);
  /*ip range*/
  if ((range_p = strchr(buf, '-')) != NULL) {
    end_ip = range_p+1;
    *range_p = '\0';
    start_ip = buf;
    si_ip = htonl(inet_addr(start_ip));
    ei_ip = htonl(inet_addr(end_ip));
  }  
  /*mask*/
  else if ((mask_p = strchr(buf, '/')) != NULL) {
    bit = atoi(mask_p+1);
    *mask_p = '\0';
    start_ip = buf;

    if(inet_aton(start_ip, &addr) == 0) 
      return;
    
    if (bit > 32) 
      return;
    
    else if (bit == 32) {
      ei_ip = si_ip = htonl(inet_addr(start_ip));
    }
    else {
      mask = ~(0xFFFFFFFF >> bit);
      hladdr = htonl(addr.s_addr);
      si_ip = hladdr & mask;
      ei_ip = (hladdr & mask) | ~mask;
    }
  } 
  else {
    ei_ip = si_ip = htonl(inet_addr(str));
  }

  /*host insert into hlist*/
  for (i = si_ip; i <= ei_ip; i++) {
    nhost = (HOST_T *) malloc (sizeof(HOST_T));
    if (!nhost) 
      continue;
    
    memset(nhost, 0, sizeof(HOST_T));
    nhost->ipv4 = i;
    nhost->type = IP_V4;
    list_add_tail(&nhost->list, &HOST_HEAD);
  }
  if (WAVE_DEBUG) {
    addr_lprint();
  }
}

static void cidrl6(char *str) {

  if (!str)
    return ;
}

static inline int  _iptyp_check(char *str) {

  unsigned char *match = NULL;
  
  if (!str)
    return IP_UNKNOW;
  if (str_chcnt(str, ':') >= 1 && str_chcnt(str, '.') > 2)
    return IP_V6;
  else if (str_chcnt(str, '.') >= 3)
    return IP_V4;
  else if (str_chcnt(str, ':') >= 1)
    return IP_V6;
  else if((match = re_check(".([a-zA-Z]+$)", str)) != NULL) {
    free(match);
    return IP_DOMAIN;
  }
  return IP_UNKNOW;
}

int addr_lpush(char *all_host) {
  
  if (!all_host)
    return -1;

  int cnt = 0, i = 0, validcnt = 0;
  char *ptr_ret  = NULL;
  char *ptr_save = NULL;
  struct hostent *host_ent = NULL;

  str_trim(all_host);

  /*host string , each host split by cahr ','*/
  cnt = str_chcnt(all_host, ',');
  /*at least one host*/
  cnt++;
  
  /*assign host*/
  IP_E tp;
  IP_T *host = (IP_T*) malloc (sizeof(IP_T) * cnt);
  if (!host)
    return -1;

  ptr_ret = strtok_r(all_host, ",", &ptr_save);

  while(ptr_ret) {
    
    tp =  _iptyp_check(ptr_ret);

    if (tp != IP_UNKNOW && tp != IP_DOMAIN && strlen(ptr_ret) <= WAVE_MAX_IP_LEN) {
      host[i].ip = strdup(ptr_ret);
      host[i].type = tp;
      i++;
    }
    else if (tp == IP_DOMAIN) {
      host_ent = gethostbyname(ptr_ret);
      if (host_ent) {
        for (i = 0; host_ent->h_aliases[i]; i++) {
          ptr_ret = inet_ntoa(*(struct in_addr*)host_ent->h_addr_list[i]);
          tp =  _iptyp_check(ptr_ret);
          host[i].ip = strdup(ptr_ret);
          host[i].type = tp;
	}
      }
    }

    ptr_ret = strtok_r(NULL, ",", &ptr_save);
  }
  validcnt = i;

  /*IP INFO Insert Into LIST*/
  INIT_LIST_HEAD(&HOST_HEAD);
  for (i = 0 ; i < validcnt; i++) {
    if (host[i].type == IP_V4)
      cidrl4(host[i].ip);
    else if (host[i].type == IP_V6)
      cidrl6(host[i].ip);
  }

  /*insert host to  and delete host*/
  for (i = 0; i < cnt; i++) {
    
    if (WAVE_DEBUG)
      printf("host : %s type:%d.\n", host[i].ip, host[i].type);

    if (host[i].ip) 
      free(host[i].ip);
  }
  free(host);
  return 0;
}


void addr_ldel() {
  
  HOST_T *t = NULL;
  LIST_HEAD_T *pos = NULL, *next = NULL;
  struct in_addr in;

  list_for_each_safe(pos, next, &HOST_HEAD) {
    t = list_entry(pos, HOST_T, list);
    if (t->ipv6)
      free(t->ipv6);
    list_del(pos);
    free(t);
  }
}
