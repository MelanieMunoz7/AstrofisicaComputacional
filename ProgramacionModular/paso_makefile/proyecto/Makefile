
CC = gcc
CFLAGS = -Wall
OBJS = hola_mundo.o funcion.o
EXEC = hola.x

compile: hola_mundo.o funcion.o 
	gcc -Wall hola_mundo.o funcion.o -o hola_mundo.out
	rm *.o

variables: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	rm $(OBJS)

clean:
	rm *.o *~ *.out
