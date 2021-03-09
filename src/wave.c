#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

#include "wave.h"
#include "wave_types.h"

/*VERSION*/
#define VERSION "WAVE 1.0\n"

/*DEBUGi switch*/
int WAVE_DEBUG = 0;

/*option*/
static char *option_s = "t:p:dvh";
static struct option option_l[] = {
  {"target",   required_argument, NULL, 't'},
  {"port",     required_argument, NULL, 'p'},
  {"debug",    no_argument,       NULL, 'd'},
  {"version",  no_argument,       NULL, 'v'},
  {"help",     no_argument,       NULL, 'h'},
  {0, 0, 0, 0},
};


static unsigned char process_stop = 0;

static void ctrlc_handler() {
  process_stop = 1;
  /*exit*/
  exit(0);
}

static void signal_init() {
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, ctrlc_handler);
}

static void usage() {
  PRINT("There Are Options:\n");
  PRINT("  -t, --target , Scan Target Domain Or IPAddress.\n");
  PRINT("  -p, --port   , Scan Target Port Or Port Range.\n");
  PRINT("  -d, --debug  , Debug Module.\n");
  PRINT("  -v, --version, Wave Major Version.\n");
  PRINT("  -h, --help   , Help .\n");
}


int wave(int argc, char *argv[]) {

  if (argc < 2) {
    usage();
    exit(EXIT_FAILURE);
  }

  int opt;
  int opt_index = 0;

  char host_cache[WAVE_HOST_LEN] = {'\0'};
  
  while ( (opt = getopt_long(argc, argv, option_s, option_l, &opt_index)) != -1) {
    
    switch(opt) {

      case 'h': {
          usage();
          break;
        }

      case 't': {
          strncpy(host_cache, optarg, WAVE_HOST_LEN);       
          break;
        }

      case 'p': {
          break;
        }

      case 'd': {
          WAVE_DEBUG = 1;
          break;
        }
		
      case 'v': {
          PRINT(VERSION);
          break;
        }

      default:
        usage();
    }
  }
  
  /*parse addr */
  if (strlen(host_cache) <= 0)
    return -1;
  parse_addr(host_cache);


  return 0;
}


int main(int argc, char *argv[]) {

  signal_init();

  wave(argc, argv);

  return 0;
}
