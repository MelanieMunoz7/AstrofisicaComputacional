#include<stdio.h>
#include"funcion.h" //No estre brakets porque la funcion.h ya esta dentro de la carpeta

int main() 
{ 
    escribeHolaMundo (); 
    return 0;
}

/*
CFLAGS=-I../funcion2
export CLFAGS 
make HolaMundo, fallara porque tiene dos archivos .c
 */
// compilar con el Makefile
