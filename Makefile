
CCFLAGS := -g -Wall -ansi -pedantic


all: test1

lineread.o: lineread.c lineread.h types.h
	gcc $(CCFLAGS) -c lineread.c -o lineread.o


space.o: space.c space.h types.h
	gcc $(CCFLAGS) -c space.c -o space.o

test1: test1.c space.o lineread.o
	gcc $(CCFLAGS) test1.c space.o lineread.o -o test1
	
	
clean:
	rm -f *.o test1
