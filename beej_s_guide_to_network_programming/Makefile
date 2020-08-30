CC := gcc

all: p19 p20 p22

p19: p19_get_addr_info.c
	$(CC) p19_get_addr_info.c -o p19_get_addr_info

p20: p20_show_ip.c
	$(CC) p20_show_ip.c -o p20_show_ip

p22: p22_first_sock.c
	$(CC) p22_first_sock.c -o p22_first_sock

p22_2: p22_bind.c
	$(CC) p22_bind.c -o p22_bind

p24: p24_connect.c
	$(CC) p24_connect.c -o p24_connect

p26: p26_listen_accept.c
	$(CC) p26_listen_accept.c -o p26_listen_accept

clean:
	rm -rf *.o $(shell find . -maxdepth 1 -type f -executable)
