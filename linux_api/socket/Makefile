CC := gcc
CFLAGS := -I../lib/

demo_us_xfr: us_xfr_sv us_xfr_cl
	./us_xfr_sv > b &
	ls -lF /tmp/us_xfr
	cat *.h > a
	./us_xfr_cl < a
	diff a b

us_xfr_sv: us_xfr_sv.c us_xfr.h
	$(CC) $(CFLAGS) ${@}.c -o $@

us_xfr_cl: us_xfr_cl.c us_xfr.h
	$(CC) $(CFLAGS) ${@}.c -o $@

demo_ud_ucase: ud_ucase_sv ud_ucase_cl
	./ud_ucase_sv &
	./ud_ucase_cl hello world
	./ud_ucase_cl 'long message'
	kill $%1

ud_ucase_sv: ud_ucase_sv.c ud_ucase.h
	$(CC) $(CFLAGS) ${@}.c -o $@

ud_ucase_cl: ud_ucase_cl.c ud_ucase.h
	$(CC) $(CFLAGS) ${@}.c -o $@

is_echo_sv: is_echo_sv.c inet_sockets.o
	$(CC) $(CFLAGS) is_echo_sv.c inet_sockets.o -o is_echo_sv

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(shell find . -maxdepth 1 -type f -executable)
