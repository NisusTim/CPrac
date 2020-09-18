CC := gcc

%.o: %.c
	$(CC) -c $^ -o $@

epoll_prac: epoll_prac.c
	$(CC) $^ -o $@

select_server: select_server.c
	$(CC) $^ -o $@

console: console.c console_cmd.c console_cmd.h
	$(CC) $^ -o $@

clean:
	rm -rf *.o $(shell find . -maxdepth 1 -type f -executable)
