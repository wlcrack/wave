
#include "wave_types.h"

/*
 * date  :2021-3-8
 * desc  :delete the space in string
 * input :string
 * output:
 * return:return None
 * */

void str_trim(char *str) {
  
  if (!str) {
    return;
  }

  char *str_p = str;

  while(*str_p) {
    
    if (*str_p != 0x20) {
      *str++ = *str_p;
    }
    str_p++;
  }
  *str = '\0';
}

/*
 *date  :2021-3-8
 *desc  :get the count of ch in the string
 *input :str, ch
 *return:the count of the ch
 * */

int str_chcnt(char *str , char ch) {
  
  if (!str)
    return 0;

  int count = 0;
  char *str_p = str;

  while(*str_p) {
    if (*str_p == ch)
      count++; 
    str_p++;
  }
  return count;
}
