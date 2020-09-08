CC := gcc

is_echo_sv: is_echo_sv.c inet_sockets.o
	$(CC) is_echo_sv.c inet_sockets.o -o is_echo_sv

inet_sockets.o: inet_sockets.c inet_sockets.h
	$(CC) -c inet_sockets.c -o inet_sockets.o

clean:
	rm -rf *.o $(shell find . -maxdepth 1 -type f -executable)
