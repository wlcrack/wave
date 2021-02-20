
CC=gcc
CXX=g++
CFLAGS +=  -g3 -O2

wave:main.o wave.o
	$(CC) $(CFLAGS)  main.o wave.o -o wave
    
main.o:main.c
	$(CC) $(CFLAGS) -c main.c

wave.o:wave.c wave_list.h
	$(CC) $(CFLAGS) -c wave.c wave_list.h


.PHONY:clean
clean:
	rm -rf *.o wave *.h.gch

