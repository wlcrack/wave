#include <regex.h>
#include <string.h>
#include <stdlib.h>

#include "wave_types.h"


#define REG_CURRENT_SIZE 1024
#define REG_MATCH_COUNT  1 

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
  
  unsigned char *match_p = NULL;
  int status = 0, match_len = 0;
  regmatch_t pmatch[REG_MATCH_COUNT];
  char *ptr = text;
  regex_t  reg;
  regoff_t len;
  
  /*compile regex*/
  status = regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE); 
  if (status != 0)
    return NULL;
  
  unsigned char *match_text = (unsigned char *)malloc(REG_CURRENT_SIZE);
  if (!match_text) {
    regfree(&reg);
    return NULL;
  }

  memset(match_text, 0, REG_CURRENT_SIZE);

  for(;;) {
    /*regex match*/
    status = regexec(&reg, ptr, ARRAY_SIZE(pmatch), pmatch, 0);
    if (status != 0)
      break;
    len = pmatch[0].rm_eo - pmatch[0].rm_so;
    match_len = strlen(match_text);
    sprintf(match_text + match_len, "%.*s", len, ptr + pmatch[0].rm_so);
    ptr += pmatch[0].rm_eo;
  }
  
  regfree(&reg);

  if (strlen(match_text) == 0) {
    if (match_text)
      free(match_text);
    return NULL;
  }
  return match_text;
}

/*
 *date  :2021-3-10
 *desc  :list function
 * */

