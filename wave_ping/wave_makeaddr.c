/*
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "wave_makeaddr.h"

extern int wave_debug;

void str_trim(char *str) {
  
  if (!str)
    return ;
  
  char *p_str = str;

  while(*str) {
    if (*str != 0x20)
      *p_str++ = *str;
    str++;
  }
  *p_str = '\0';
}

static int str_chcnt(char *str, char ch) {

  int   count = 0;
  char *p_str = str;

  if (!str || ch == 0x00)
    return 0;

  while(*p_str) {
    if (*p_str == ch)
      count++;
    p_str++;
  }
  return count;
}

int wave_makeaddr(char *wave_host) {
  int i = 0 ,count = 0;
  char *p_tok = NULL, *q_tok = NULL;
  wave_host_t *host_arr = NULL;
  target_t *new_target = NULL;

  if (wave_host == NULL)
    return -1;
    
  str_trim(wave_host);
  
  if (wave_debug)
    printf("str_trim : %s\n", wave_host);


  /*at least one host*/
  count = str_chcnt(wave_host, ',');
  count++;

  host_arr = (wave_host_t*) malloc (sizeof(wave_host_t) * count);
  if (host_arr == NULL)
    return -1;

  memset(host_arr, 0, sizeof(host_arr));
 
  p_tok = strtok_r(wave_host, ",", &q_tok);
  while(p_tok) {
    strncpy(host_arr->host, p_tok, WAVE_HOSTLEN);
    p_tok = strtok_r(NULL, ",", &q_tok);
  }

  free(host_arr);
  return 0;
}
