CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
SRCDIR = UnixLab/src
OBJDIR = UnixLab/build
TESTDIR = UnixLab/test
TESTEXT = sh
SRCEXT = c

OBJFILES = cat0.o cp0.o cp1.o ln0.o ln1.o ls0.o mv0.o ps0.o rm0.o rm1.o stat0.o tee0.o touch0.o touch1.o
TESTS = $(shell find $(TESTDIR) -type f -name *-test.$(TESTEXT))

OBJS := $(addprefix $(OBJDIR)/,$(OBJFILES))

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(FLAGS) $< -o $(OBJDIR)/$*

default:  $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY:
	clean all default

clean:
	rm -r $(OBJDIR)
