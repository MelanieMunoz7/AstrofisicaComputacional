#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Punto 1: epsilon de la maquina - parcial 1 de astrofisica computacional
Nombre: Melanie Munoz Chavarria*/


/*Consulte y programe un algoritmo para encontrar el epsilon 
de maquina del computador donde normalmente programa*/


int main(void)
{

/*Se crean las variables para almacenar cada epsilon*/
float epsilonFloat; 
double epsilonDouble;
long double epsilonLongDouble;

/*Se le asignan los valores a las variables*/

epsilonFloat = 1.0;
epsilonDouble = 1.0;
epsilonLongDouble = 1.0;


/*Se crean los cilos para dividir las varaibles entre dos, para 
en cada iteracion obtener la mitad del numero incial, reduciendolo
a la mitad*/

//Para el float

while ((float)1.0 + epsilonFloat != (float)1.0)
{
    epsilonFloat = epsilonFloat / (float) 2.0; //Se divide por dos, pero en particular un dos en float
}

//Para el double

while (1.0 + epsilonDouble != 1.0)
{
    epsilonDouble = epsilonDouble / 2.0; //Tanto en el condicional como en la divsion no es necesario especificar el tipo, C lo da por defecto
}

//Para el long double

while ((long double) 1.0 + epsilonLongDouble != (long double) 1.0)
{
    epsilonLongDouble = epsilonLongDouble / (long double) 2.0; //Nuevamente se estable la conversion de los valores a long double
}

//Imprimiendo los resultados de los epsilon

printf("El elpsilon de la maquina para el tipo de variable float es %.16f\n", epsilonFloat);
printf("El elpsilon de la maquina para el tipo de variable double es %.32lf\n", epsilonDouble);
printf("El elpsilon de la maquina para el tipo de variable long double es %.64Lf\n", epsilonLongDouble);

return 0;
}