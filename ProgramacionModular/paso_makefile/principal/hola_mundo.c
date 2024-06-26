#include <stdio.h> 
#include <texto.h>

int main() 
{
  printf ("%s\n", TEXTO); 
  return 0; 
}

// compilar con make hola_mundo, fallara
// luego compilar con:
/*
CFLAGS=-I../funcion1
export CFLAGS
make hola_mundo , funcionara
 */
