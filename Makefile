
CFLAGS ?= -g -O3
OBJECTS ?= test.o darray.o

test: $(OBJECTS)
	gcc $(CFLAGS) -o test $(OBJECTS)

$(OBJECTS): %.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm $(OBJECTS) test
