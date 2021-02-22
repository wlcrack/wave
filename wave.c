#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>

#include "wave_list.h"

static char *wave_version = "wave version - 0.1";

int wave_debug = 0;
/*target list head*/
struct list_head wave_target;


static void usage(){
    const char *usege = "                          ___\n"
                  "\\    /\\    /  /\\  \\    /  |\n"
                  " \\  /  \\  /  /--\\  \\  /   ———\n"
                  "  \\/    \\/  /    \\  \\/    |__\n";
    printf("%s\n", usege);
    printf("  There are opeions:\n");
    printf("  -t, The scan target domain or ipaddress\n");
    printf("  -d, debug options.\n");

}

int wave(int argc, char * argv [])
{

    int opt;
    static char *wave_options = "t:dv";
    
    if(argc < 2){
        usage();
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, wave_options))!= -1){
        switch(opt){
            case 't':
                printf("target %s\n", optarg);
                break;
            case 'd':
                wave_debug = 1;
                break;
            case 'v':
                printf("%s\n", wave_version);
                break;
            default:
                printf("The option [%c] is not support!\n", opt);
                usage();
                exit(EXIT_FAILURE);
        }
        
    }

    //wave_icmp_scan(ICMP_ECHO);
    return 0;
}

