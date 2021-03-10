#ifndef _WAVE_TYPES_H_
#define _WAVE_TYPES_H_

#include <stdio.h>

#include "wave_list.h"


typedef enum {
  IP_UNKNOW = 0,
  IP_V4     = 1,
  IP_V6     = 2,
  IP_DOMAIN = 3
}IP_E;

typedef struct {
  char         *ipv6;
  unsigned long ipv4;
  IP_E          type; 
  LIST_HEAD_T   list; 
}HOST_T;

typedef enum REG_FLAG{
  RE_EXTENDED = 1,
  RE_ICASE    = 2,
  RE_NOSUB    = 3,
  RE_NEWLINE  = 4 
}RE_GLAG_E;

/*REG Functions*/

int   str_chcnt(char *str , char ch); 
void  str_trim(char *str); 
unsigned char *re_check(char *parttern, char *text);

/*mcor*/
#define PRINT(x...) printf(x)
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

#endif
