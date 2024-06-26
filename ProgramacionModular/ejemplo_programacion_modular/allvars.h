// aca de invocan cabeceras, definen macros y se definen las variables globales
// para todos los modulos

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "funcion1.h"
#include "funcion2.h"

//Extern lo que hace es guardar memoria para una variable que se define en otro 
extern double variable_global2; // la unica bien definida (orden)
extern double variable_global3; //debe ser declarada aca por orden en el codigo

#define TEXTO "¿como estuvo el curso?"



