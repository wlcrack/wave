#include <regex.h>
#include <string.h>
#include <stdlib.h>

#include "wave_types.h"


#define REG_CURRENT_SIZE 1024
#define REG_MATCH_COUNT  2

extern int WAVE_DEBUG;

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

/*
 *date   :2021-3-9
 *desc   :regex match
 *input  :reg parttern and match text
 *return :match string, need free
 * */

unsigned char *re_check(char *pattern, char *text) {
  
  if (!pattern || !text)
    return NULL;
  
  if (WAVE_DEBUG)
    printf("pattern:[%s] text:[%s] \n", pattern, text);

  int status = 0;
  int current_size = REG_CURRENT_SIZE;
  const size_t nmatch = REG_MATCH_COUNT; 
  regmatch_t pmatch[nmatch];
  char *ptr = text;
  regex_t reg;
  
  /*compile regex*/
  status = regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE); 
  if (status != 0)
    return NULL;
  
  unsigned char *match_text = (unsigned char *)malloc(current_size);
  if (!match_text) {
    regfree(&reg);
    return NULL;
  }

  memset(match_text, 0, current_size);

  for(;;) {
    /*regex match*/
    status = regexec(&reg, ptr, nmatch, pmatch, 0);
    if (status != 0)
      break;
    sprintf(match_text + strlen(match_text), "%.*s", 
           pmatch[1].rm_eo - pmatch[1].rm_so
          ,ptr + pmatch[1].rm_so);
    ptr += pmatch[0].rm_eo;
  
  }
  regfree(&reg);
  return match_text;
}
