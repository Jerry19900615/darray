
CFLAGS ?= -g

main: main.o darray.o
	gcc $(CLFAGS) -o main main.o darray.o
main.o: main.c darray.h
	gcc $(CFLAGS) -c main.c -o main.o

darray.o: darray.c darray.h
	gcc $(CFLAGS) -c darray.c -o darray.o

.PHONY: clean
clean:
	rm *.o main
