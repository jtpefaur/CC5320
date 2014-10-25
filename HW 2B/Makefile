 
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all: test-trans tracegen
#	 Generate a handin tar file each time you compile
#	-tar -cvf ${USER}-handin.tar  trans.c 

test-trans: test-trans.c trans.o cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o test-trans test-trans.c cachelab.c trans.o 

tracegen: tracegen.c trans.o cachelab.c
	$(CC) $(CFLAGS) -O0 -o tracegen tracegen.c trans.o cachelab.c

trans.o: trans.c
	$(CC) $(CFLAGS) -O0 -c trans.c

#
# Clean the src dirctory
#
clean:
	rm -rf *.o
	rm -f test-trans tracegen
	rm -f trace.all trace.f*
