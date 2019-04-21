CC=gcc

all:part1 part2

part1:
		$(CC) part1.c -o part1.out -lpthread

part2:
		$(CC) part2.c -o part2.out -lpthread -lrt

clean:
	rm *.o
	rm *.out