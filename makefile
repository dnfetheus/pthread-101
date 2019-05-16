CC=gcc

all: hello array

hello:
	$(CC) src/hello_thread.c -o hello.out -lpthread

array:
	$(CC) src/array_remove.c -o array.out -lpthread -lrt

clean:
	rm -rf *.out || true
	rm -rf *.o || true
	rm -rf *.obj || true