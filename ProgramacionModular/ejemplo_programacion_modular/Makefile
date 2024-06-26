
CC = gcc
CFLAGS = -Wall
LFLAGS = -lm
OBJS = main.o allvars.o funcion1.o funcion2.o
EXEC = proyecto_modular.out

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(EXEC)
	rm $(OBJS)

clean:
	rm *~ *.out
