
CFLAGS ?= -g -O3
OBJECTS ?= test.o darray.o

test: $(OBJECTS)
	gcc $(CFLAGS) -o test $(OBJECTS)

$(OBJECTS): %.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

tags:
	gtags 

.PHONY: clean test tags
clean:
	rm $(OBJECTS) test
