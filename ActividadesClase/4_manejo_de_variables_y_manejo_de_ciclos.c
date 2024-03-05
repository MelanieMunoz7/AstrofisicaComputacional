#include <stdio.h>
#include <stdlib.h>

int main(void)

{   size_t tamanoDeVariable; 

    int variableEntera;
    int variableEntera2, variableEntera3;
    tamanoDeVariable = sizeof(variableEntera);
    printf("El tamano de una variable entera es: %lu bytes\n", tamanoDeVariable);

    float variableFlotante;
    tamanoDeVariable = sizeof(variableFlotante);
    printf("El tamano de una variable flotante es: %lu bytes\n", tamanoDeVariable);

    double variableFlotanteDoblePrecision= 9.8;
    tamanoDeVariable = sizeof(variableFlotanteDoblePrecision);
    printf("El tamano de una varaible doble es: %lu bytes\n", tamanoDeVariable);


    //**Explicacion de la entrada de datos por parte del usuario usando scanf**

    double altura;
    printf("Ingrese la altura inicial en metros: ");
    scanf("%lf",&altura); //Operador de conversion
    printf("altura= %lf\n", altura);

    int numeroDeCuerpos;
    double masaEnKg, velocidadInicial, energia;

    printf("\nIngrese el numero de cuerpos (entero), la masa (kg) y la velocidad incial (m/s):\n"); 
    scanf("%d %lf %lf", &numeroDeCuerpos,&masaEnKg,&velocidadInicial); //Especificamente en la salida muestra el tipo de datos que le asigno
    printf("numero de cuerpos: %d\n masa= %lf kg\n velcidad inicial = %lf m/s\n", numeroDeCuerpos, masaEnKg,velocidadInicial); //la terminal lee cada los valores y al darle espacio, el espacio  le indica cada valor correspondiente
    
    energia = masaEnKg*altura*9.8;

    printf("%lf\n", energia);


    // **Estructuras de repeticion**
    //Para 

    int i;
    printf("\nCiclo para:\n");

    //El ciclo tiene un inicio, un valor hasta el que va y el salto
    for (i=0; i<=10; i=i+1) //Para que se deasarolle mas de una accion es necesario que las acciones esten entre llaves, se puede colocar i++ para incrementar de a uno (pero solo de a uno)
    {
        printf("%d\n",i);
        printf("Hola\n");
    }

    //While 
    // Este while evalua la condicion y luego ejecuta las instruacciones

    printf("\nCiclo while: \n");

    i=0;
    while(i++<10)
    {
        printf("%d\n",i);
        i++;
    }

    //Do while 
    // Este while ejecuta las acciones y luego evalua la que la condicion se cumpla
    printf("\nCiclo do while:\n");

    i=0;
    do
    {
        printf("%d\n",i);
        i++;

    } while(i++<10);

    return 0;
}