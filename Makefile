CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS =  structure.c main.c construire_automate.c utiles.c
OBJS = $(SRCS:.c=.o)
HEADERS = structure.h main.h  construire_automate.h utiles.h
TARGET = AP

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
