


GCC=/usr/bin/gcc
CFLAGS=-Wall
IFLAGS=$(shell pkg-config --cflags --libs cairo)
CAIRO_TEST=cairo_test
LDFLAGS=-lcairo


SRCDIR=./src
OBJDIR=./obj
BINDIR=./bin

CAIRO_TEST_SRCDIR=$(SRCDIR)/cairo_test
CAIRO_TEST_OBJDIR=$(OBJDIR)/cairo_test
CAIRO_TEST_BINDIR=$(BINDIR)
CAIRO_TEST_SRCS=$(shell find $(CAIRO_TEST_SRCDIR) -type f -name "*.c")
CAIRO_TEST_OBJS=$(patsubst $(CAIRO_TEST_SRCDIR)/%.c, $(CAIRO_TEST_OBJDIR)/%.o, $(CAIRO_TEST_SRCS))
CAIRO_TEST_BIN=cairo_test


EX_1_PNG_SRCDIR=$(SRCDIR)/examples/example_1_png
EX_1_PNG_OBJDIR=$(OBJDIR)/examples/example_1_png
EX_1_PNG_BINDIR=$(BINDIR)/examples/
EX_1_PNG_SRCS=$(shell find $(EX_1_PNG_SRCDIR) -type f -name "*.c")
EX_1_PNG_OBJS=$(patsubst $(EX_1_PNG_SRCDIR)/%.c, $(EX_1_PNG_OBJDIR)/%.o, $(EX_1_PNG_SRCS))
EX_1_PNG_BIN=example_1_png


all: $(CAIRO_TEST_BIN) $(EX_1_PNG_BIN)



$(EX_1_PNG_BIN): $(EX_1_PNG_OBJS)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(EX_1_PNG_BINDIR)/$(EX_1_PNG_BIN)

$(EX_1_PNG_OBJDIR)/%.o : $(EX_1_PNG_SRCDIR)/%.c
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@


# Make the cairo test

$(CAIRO_TEST_BIN): $(CAIRO_TEST_OBJS)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(CAIRO_TEST_BINDIR)/$(CAIRO_TEST_BIN)

$(CAIRO_TEST_OBJDIR)/%.o : $(CAIRO_TEST_SRCDIR)/%.c
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@


.PHONY: PRINT

PRINT:
	@printf "\nMaking $(CAIRO_TEST)...\n"

.PHONY: clean

clean:
	find $(OBJDIR) -type f -name "*.o" -delete
	find $(BINDIR) -type f -delete

