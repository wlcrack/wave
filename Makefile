
CC=gcc
CXX=g++
CFLAGS +=  -g3 -O

INCLUDE= -I.

wave:main.o wave.o
	$(CC) $(CFLAGS) $(INCLUDE)  main.o wave.o -o wave
    
main.o:main.c
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c

wave.o:wave.c wave_list.h
	$(CC) $(CFLAGS) $(INCLUDE) -c wave.c wave_list.h


.PHONY:clean
clean:
	rm -rf *.o *.h.gch

