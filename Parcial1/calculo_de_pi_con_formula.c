#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*Punto 2: calculo de pi - parcial 1 de astrofisica computacional
Nombre: Melanie Munoz Chavarria*/

/*Elabore un programa que calcule pi a partir de la la formula dada,
Encuentre el valor de N minimo que da como resultado un valor de pi 
con una precision de 10 cifrasdecimales. Con el resultado del literal anterior, 
encuentre el numero maximo de cifras decimales con el que su computador puede calcular pi.*/

int main(void)
{
    /*Creando las varaibles para almecenar el valor de N, el valor de la suma total de pi 
    y el numero pi con 10 variables*/

    int valorDeN;
    double sumaDePi; 
    double piDiezCifras;
    double epsilonDouble;
    double cantidadMaximaDeDecimales;

    //Definiendo los valores

    piDiezCifras = 3.1415926535;
    epsilonDouble = 1.1102230246e-16;

    //Inicializando las variables que aumentaran en cada calculo

    valorDeN = 0;
    sumaDePi = 0.0;

    //Se usa el espsilon de la maquina como condicion de parada
    
    while (fabs(piDiezCifras - 4.0*sumaDePi)>= epsilonDouble)
    {
        sumaDePi = sumaDePi + pow(-1,valorDeN)/(2*valorDeN+1);
        valorDeN = valorDeN + 1;
    }

    printf("El valor de pi para 10 cifras decimales es %.10lf y la cantidad de N para llevar el calulo a cabo es %d\n", 4*sumaDePi, valorDeN);
    
    /*Como la candidad maxima de decimales del numero pi calculado
    depende el epsilon de la maquina, entonces para conocer la cantidad de decimales que tiene 
    el epsilon de la maquina basta con aplicar logaritmo en base 10*/

    cantidadMaximaDeDecimales = abs(round(log10(epsilonDouble)));
    printf("\nEl numero maximo de decimales para el calculo de pi es %lf\n", cantidadMaximaDeDecimales);
    return 0; 
}
