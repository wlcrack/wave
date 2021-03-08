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
static char *option_s = "h:p:dv";
static struct option option_l[] = {
  {"host",     required_argument, NULL, 'h'},
  {"port",     required_argument, NULL, 'p'},
  {"debug",    no_argument,       NULL, 'd'},
  {"version",  no_argument,       NULL, 'v'},
  {0, 0, 0, 0},
};


static unsigned char process_stop = 0;

static void ctrlc_handler() {
  process_stop = 1;
}

static void signal_init() {
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, ctrlc_handler);
}

static void usage() {
  PRINT("There Are Options:\n");
  PRINT("  -h, Scan Target Domain Or IPAddress.\n");
  PRINT("  -p, Scan Target Port Or Port Range.\n");
  PRINT("  -d, Debug Module.\n");
  PRINT("  -v, Wave Major Version.\n");
}


int wave(int argc, char *argv[]) {

  if (argc < 2)
    exit(EXIT_FAILURE);

  int opt;
  int opt_index = 0;

  char host_cache[WAVE_HOST_LEN] = {'\0'};
  
  while ( (opt = getopt_long(argc, argv, option_s, option_l, &opt_index)) != -1) {
    
    switch(opt) {

      case 'h': {
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

  return 0;
}


int main(int argc, char *argv[]) {
  signal_init();

  wave(argc, argv);

  return 0;
}
