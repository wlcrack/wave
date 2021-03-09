#ifndef _WAVE_TYPES_H_
#define _WAVE_TYPES_H_

#include <stdio.h>

/*REG Functions*/

int   str_chcnt(char *str , char ch); 
void  str_trim(char *str); 
unsigned char *re_check(char *parttern, char *text);

#define PRINT(x...) printf(x)

#endif
