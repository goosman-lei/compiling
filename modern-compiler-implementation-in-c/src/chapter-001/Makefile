CC=gcc

COMPILE_CFLAGS=-O0 -g -c
LINK_CFLAGS=-g

LINK_COMMAND=$(CC) $(LINK_CFLAGS)
COMPILE_COMMAND=$(CC) $(COMPILE_CFLAGS)

a.out: main.o prog.o slp.o util.o func.o
	$(LINK_COMMAND) main.o prog.o slp.o util.o func.o

main.o: main.c slp.h util.h func.h
	$(COMPILE_COMMAND) main.c

func.o: func.c func.h
	$(COMPILE_COMMAND) func.c

prog.o: prog.c prog.h
	$(COMPILE_COMMAND) prog.c

slp.o: slp.c slp.h
	$(COMPILE_COMMAND) slp.c

util.o: util.c util.h
	$(COMPILE_COMMAND) util.c

clean:
	rm -f a.out util.o prog.o slp.o main.o func.o
