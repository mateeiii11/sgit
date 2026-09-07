CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = sgit
SRCS = main.c sgit.c objects.c hash.c status.c commands.c commit.c
OBJS = $(SRCS:.c=.o)

PREFIX ?= /usr/local

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)

.PHONY: all clean install uninstall
