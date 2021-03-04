#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "wave.h"
#include "wave_list.h"

#define WAVE_HOSTLEN 128

/*VERSION*/
static char *wave_version = "wave version - 0.1";
/*DEBUG*/
int wave_debug = 0;
/*TARGET HEADER*/
struct list_head wave_target;



static void usage(){
    const char *usege = "                          ___\n"
                  "\\    /\\    /  /\\  \\    /  |\n"
                  " \\  /  \\  /  /--\\  \\  /   ———\n"
                  "  \\/    \\/  /    \\  \\/    |__\n";
    printf("%s\n", usege);
    printf("There Are Options:\n");
    printf("  -t, Scan Target Domain Or IPAddress.\n");
    printf("  -d, Debug Module.\n");
    printf("  -v, Wave Major Version.\n");

}

int wave(int argc, char * argv [])
{

    int opt;
    static char wave_host[WAVE_HOSTLEN] = {0};

    /*wave command options*/
    static char *wave_options = "t:dv";
    
    if(argc < 2){
        usage();
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, wave_options))!= -1){
        switch(opt){
            case 't':
                strncpy(wave_host, optarg, WAVE_HOSTLEN);
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


    return 0;
}

