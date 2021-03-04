/*
 copyright 2021
 authoer :crackww
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "wave_makeaddr.h"

extern struct list_head target;

int target_head_init(){
    INIT_LIST_HEAD(&target);
    return 0;
}

target_t *target_make(char *addr, int port, IP_VER_T type){
    if (addr == NULL)
        return NULL;
    
    target_t *new_target = NULL;
    new_target = (target_t*)malloc(sizeof(target_t));
    if (new_target == NULL){
        printf("[ERROR] new target create failed.\n");
        return NULL;
    }
    memset(new_target, 0 , sizeof(new_target));
    if(type == IP_VER4){
        new_target->s_addr_4 = strdup(addr);
    }
    else if(type == IP_VER6){
        new_target->s_addr_6 = strdup(addr);
    }
    else{
        printf("[WARNING] unknow addr type.\n");
    }
    new_target->port = port;
    new_target->type = type;
    
    return new_target;
}

int target_del(){
    
    target_t *new_target = NULL;
    struct list_head *pos = NULL, *next = NULL;
    list_for_each_safe(pos, next, &target){
        new_target = list_entry(pos, target_t, list);
        if(new_target){
            printf("free target [%s] [%s] [%d] [%d]\n", new_target->s_addr_4, 
                    new_target->s_addr_6, new_target->port, new_target->type);
            if (new_target->s_addr_4)
                free(new_target->s_addr_4);
            else if(new_target->s_addr_6)
                free(new_target->s_addr_6);
            list_del(pos);
            free(new_target);
        }
    }
    if (target)
        free(target);
    return 0;
}

void str_trim(char *str) {
  
  if (!str)
    return ;
  
  char *p_str = str;

  while(*p_str) {
    if (*p_str != 0x20)
      *p_str++ = *str;
    str++;
  }
  p_str = '\0';
}

int wave_makeaddr(char *wave_host)
{
    int i = 0 ;
    target_t *new_target = NULL;

    if (wave_host == NULL)
	    return -1;
    
    
    if (target_head_init() != 0)
        return -1;
    
    for (i = 0 ; i < 10; i++){
        new_target = target_make("172.18.0.1", 22, IP_VER4);
        if (new_target == NULL){
            continue;
        }
        list_add_tail(&new_target->list, &target);
    }
    target_del();
    return 0;
}
