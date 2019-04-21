CC=gcc

all:hello array

hello:
	$(CC) hello_thread.c -o hello.out -lpthread

array:
	$(CC) array_remove.c -o array.out -lpthread -lrt

clean:
	rm *.out || true
	rm *.o || true
	rm *.obj || true