#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Variables globales*/
double aceleracionGravedad= 9.8; 
double velocidadEnXInicial; 

/*Creando una rutina que imprima el archivo con los Datos de Energia*/

void imprimirDatosEnArchivo(FILE *archivo, double tiempoLocal, double EnergiaParaCadaTiempoLocal, double errorRelativoEnergia)
{
    fprintf(archivo,"%10.8lf\t%10.8lf\t%10.8lf\t\n", 
    tiempoLocal, EnergiaParaCadaTiempoLocal,errorRelativoEnergia);
}

/*Funcion para calcular la energia*/
double calcularEnergia(double masaLocal,double posicionEnYLocal, double velocidadEnYLocal)
{
    double energia, magnitudVelocidadAlCuadrado;

    magnitudVelocidadAlCuadrado = pow(velocidadEnXInicial,2) + velocidadEnYLocal*velocidadEnYLocal;

    energia= masaLocal*aceleracionGravedad*posicionEnYLocal+ 0.5*masaLocal*magnitudVelocidadAlCuadrado;

    return energia;
}

int main (void)
{
        //Condiciones inciales
    double posicionEnXInicial = 0.0; 
    double posicionEnYInicial = 10.0; 
    double velocidadEnYInicial=0.0;

    double tiempoMaximoDeSimulacion= sqrt(2.0*posicionEnYInicial/aceleracionGravedad);
    double tiempo, deltaT;
    double errorRelativoEnergia;
    double EnergiaParaCadaTiempo;

    double masa=1.0; //kg

    //Variables que van a evolucionar
    double posicionEnX,posicionEnY,velocidadEnY;

    printf("Condiciones inciales: \n\n"); 
    printf("(x_0,y_0)= (%lf, %lf)\n", posicionEnXInicial, posicionEnYInicial);
    printf("(v_0_x,v_0_y)=(%lf, %lf)\n", velocidadEnXInicial, velocidadEnYInicial);
    printf("g= %lf (m/s²)\n",aceleracionGravedad);

    velocidadEnXInicial=1.0; 

    velocidadEnY = velocidadEnYInicial;
    posicionEnX = posicionEnXInicial;
    posicionEnY = posicionEnYInicial;

    printf("Ingrese el numero de puntos para la simulacion\n->");
    int numeroDePuntos;
    scanf("%d", &numeroDePuntos);

    deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;

    switch (numeroDePuntos) /*Esta estructura esta disenada para comparar enteros y cadenas de caracteres*/
    {
        case 20:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 100:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 10000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 100000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 1000000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 10000000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        
        default: //En caso de que el usuario no ingrese algunos de los valores anteriores
            numeroDePuntos=1000;
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
  
    }

    /*Creando la energia inicial*/

    double EnergiaInicial; 
    EnergiaInicial = calcularEnergia(masa, posicionEnYInicial,velocidadEnYInicial);
    printf("Energia inicial = %lf J\n",EnergiaInicial);

    /*Creando el archivo para analizar la consrvacion de la energia*/

    FILE *archivoSimulacion; //Para crear el archivo de texto
    archivoSimulacion = fopen("conservacion_energia.dat","w");

    imprimirDatosEnArchivo(archivoSimulacion,0.0, EnergiaInicial,0.0);
    for(tiempo =deltaT; tiempo <= tiempoMaximoDeSimulacion; tiempo = tiempo+deltaT)
{
        velocidadEnY = velocidadEnY - aceleracionGravedad*deltaT;
        posicionEnX = posicionEnX + velocidadEnXInicial*deltaT;
        posicionEnY = posicionEnY + velocidadEnY*deltaT;
        EnergiaParaCadaTiempo = calcularEnergia(masa, posicionEnY ,velocidadEnY);
        errorRelativoEnergia = fabs(EnergiaInicial-EnergiaParaCadaTiempo)/EnergiaInicial;


        //De una forma mas inteligente
        if (posicionEnY >= 0.0)
            imprimirDatosEnArchivo(archivoSimulacion, tiempo, EnergiaParaCadaTiempo, errorRelativoEnergia); 
    
        else
            break;
}
fclose(archivoSimulacion);

return 0;
}