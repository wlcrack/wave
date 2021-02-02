
CC=gcc
CXX=g++
CFLAGS +=  -g3 -O2
OBJ=main.o  wave.o

wave:$(OBJ)
    $(CC) $(CFLAGS) -c main.c
    
main.o:main.c wave.h
    $(CC) $(CFLAGS) -c main.c

wave.o:wave.c wave.h wave_discovery.h wave_makeaddr.h
	$(CC) $(CFLAGS) -c wave.c

