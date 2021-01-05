#include "wave.h"
#include "wave_discovery.h"

int wave(int argc, char * argv [])
{
    wave_icmp_scan(ICMP_ECHO);
    return 0;
}

