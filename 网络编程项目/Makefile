CC = gcc
CFLAGS = -Wall -g -O0

SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}


all:$(OBJS)

$(OBJS):%:%.c
	$(CC) $(CFLAGS) -o $@ $^ json.c sql3.c  -lpthread  -ljson -lsqlite3


clean:
	$(RM) $(OBJS) .*.sw?

