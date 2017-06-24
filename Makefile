CC=gcc
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS=$(shell pkg-config --libs gtk+-3.0)

SRCDIR=src
OBJDIR=obj
BINDIR=bin

# Collect all sources in SRCDIR
SRCS=$(wildcard $(SRCDIR)/*.c)
# Translate to object names in OBJDIR
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BINS=$(patsubst $(OBJDIR)/%.o, $(BINDIR)/$(basename %.o), $(OBJS))


# Build all binaries
all: $(BINS)

$(BINS): $(BINDIR)/% : $(OBJDIR)/%.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c PRINT
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

.PHONY: PRINT
PRINT:
	@printf "Making objects\n"


.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o
	rm -f gtk_cairo_test
