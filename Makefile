CC=gcc
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS=$(shell pkg-config --libs gtk+-3.0)


gtk_cairo_test: gtk_cairo_test.o


.PHONY: clean

clean:
	rm -f *.o
	rm -f gtk_cairo_test
