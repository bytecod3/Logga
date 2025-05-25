CC = GCC
CFLAGS = -I.inc
SRC = examples/basic.c src/logga.c

#basic: logga.o
#	$(CC) examples/basic.c -o basic
#
#logga.o:
#	$(CC) $(CFLAGS) -c logga.c
#

basic: basic.c logga.c
	gcc -o basic basic.c logga.c $(CFLAGS)
