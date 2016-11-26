


GCC=/usr/bin/gcc
CFLAGS=-Wall
IFLAGS=$(shell pkg-config --cflags --libs cairo)
CAIRO_TEST=cairo_test
LDFLAGS=-lcairo

SRCDIR=./src
OBJDIR=./obj
BINDIR=./bin


SRCS=$(shell find $(SRCDIR) -maxdepth 1 -type f -name "*.c")
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(CAIRO_TEST)

$(CAIRO_TEST): $(OBJS)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(BINDIR)/$(CAIRO_TEST)

$(OBJDIR)/%.o : $(SRCDIR)/%.c PRINT
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: PRINT

PRINT:
	@printf "\nMaking $(CAIRO_TEST)...\n"

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*

