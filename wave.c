#include<unistd.h>
#include<getopt.h>

#include "wave_list.h"

int wave_debug = 0;
/*target list head*/
struct list_head wave_target;


void usage(){
    printf("                              ___\n");
    printf("\     /\     /  /\  \     /  |\n");
    printf(" \   /  \   /  /--\  \   /   ————\n");
    printf("  \_/    \_/  /    \  \_/    |___\n");
    printf("\n");
    printf("  There are opeions:\n");
    printf("  -t, The scan target domain or ipaddress\n");
    printf("  -d, debug options.\n");

}

int wave(int argc, char * argv [])
{

    int opt;
    char *wave_options = "t:d";

    while ((opt = getopt(argc, argv, wave_options))!= -1){
        switch(opt){
            case 't':
                printf("target %s\n", optarg);
                break;
            case 'd':
                wave_debug = 1;
                break;
            default:
                printf("The option [%c] is not support!", opt);
                usage();
                exit(-1);
        }
        
    }

    //wave_icmp_scan(ICMP_ECHO);
    return 0;
}

