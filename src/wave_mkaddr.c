#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "wave_types.h"

#define WAVE_MAX_IP_LEN 128

extern int WAVE_DEBUG;

typedef enum {
  IP_UNKNOW = 0,
  IP_V4     = 1,
  IP_V6     = 2,
  IP_DOMAIN = 3
}IP_E;

typedef struct {
  char    *domain;
  char    *ip; 
  IP_E    type;
}IP_T;

static void cidrl4(char *str) {
  
  if (!str)
    return ;
  
  struct in_addr addr;
  char buf[WAVE_MAX_IP_LEN] = {'\0'};
  strncpy(buf, str, WAVE_MAX_IP_LEN);
  char *range_p = strchr(buf, '-');
  char *mask_p  = strchr(buf, '/');
  char *start_ip = NULL, *end_ip = NULL;
  int  mask = 0, bit = 0;
  unsigned long hladdr = 0, si_ip = 0, ei_ip = 0;

  /*ip range*/
  if (range_p != NULL) {
    end_ip = range_p+1;
    *range_p = '\0';
    start_ip = buf;
    si_ip = inet_addr(start_ip);
    ei_ip = inet_addr(end_ip);
  }  
  /*mask*/
  else if (mask_p != NULL) {
    bit = atoi(mask_p+1);
    *mask_p = '\0';
    start_ip = buf;

    if(inet_aton(start_ip, &addr) == 0)
      return;
    if (bit > 32)
      return;
    else if (bit == 32) {
      si_ip = inet_addr(start_ip);
    }
    else {
      mask = ~(0xFFFFFFFF >> bit);
      hladdr = ntohl(addr.s_addr);
      si_ip = hladdr & mask;
      ei_ip = (hladdr & mask) | ~mask;
    }
  }

  if (WAVE_DEBUG)
    printf("startip :%lu, endip:%lu\n", si_ip, ei_ip);
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
  else if((match = re_check("*.[a-zA-Z]+$", str)) != NULL) {
    free(match);
    return IP_DOMAIN;
  }
  return IP_UNKNOW;
}



int parse_addr(char *all_host) {
  
  if (!all_host)
    return -1;

  int cnt = 0, i = 0, validcnt = 0;
  char *ptr_ret  = NULL;
  char *ptr_save = NULL;

  str_trim(all_host);
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
      printf("domain #######\n");
    }

    ptr_ret = strtok_r(NULL, ",", &ptr_save);
  }
  validcnt = i;

  for (i = 0 ; i < validcnt; i++) {
    if (host[i].type == IP_V4)
      cidrl4(host[i].ip);
    else if (host[i].type == IP_V6)
      cidrl6(host[i].ip);
  }

  /*delete host*/
  for (i = 0; i < cnt; i++) {
    
    if (WAVE_DEBUG)
      printf("host : %s type:%d.\n", host[i].ip, host[i].type);

    if (host[i].ip) 
      free(host[i].ip);
  }
  free(host);
  return 0;
}
