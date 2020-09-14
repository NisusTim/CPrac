CC := gcc

%.o: %.c
	$(CC) -c $^ -o $@

epoll_prac: epoll_prac.c
	$(CC) epoll_prac.c -o $@

select_server: select_server.c
	$(CC) select_server.c -o $@

clean:
	rm -rf *.o $(shell find . -maxdepth 1 -type f -executable)
