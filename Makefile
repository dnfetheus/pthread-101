CC=gcc

all: hello array

hello:
	$(CC) src/hello_thread.c -o hello_thread -lpthread

array:
	$(CC) src/array_remove.c -o array_remove -lpthread -lrt

clean:
	rm -rf *.out || true
	rm -rf *.o || true
	rm -rf *.obj || true