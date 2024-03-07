#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Solcuion analitica tiro parabolico*/
/*Formulas*/

//espacio recorrido en x

double espacioRecorridoEnX(double tiempoLocal, double velocidadEnXInicialLocal, double posicionEnXInicialLocal)
{
    double desplazamientoEnX; 

    desplazamientoEnX = posicionEnXInicialLocal + velocidadEnXInicialLocal * tiempoLocal;

    return desplazamientoEnX;
}

//Espacio recocorrido en Y
double espacioRecorridoenY(double tiempoLocal, double velocidadEnYInicialLocal,double aceleracionGravedadLocal, double posicionEnYInicialLocal)
{
    double desplazamientoEnY,tiempoAlCuadradoPorGravedad;

    tiempoAlCuadradoPorGravedad = 0.5 * aceleracionGravedadLocal * tiempoLocal * tiempoLocal;

    desplazamientoEnY = posicionEnYInicialLocal + (velocidadEnYInicialLocal * tiempoLocal) - tiempoAlCuadradoPorGravedad;

    return desplazamientoEnY;
}

//Velcidad en Y
double VelocidadEnY(double tiempoLocal, double velocidadEnYInicialLocal, double aceleracionGravedadLocal)
{
    double velocidadY; 
    velocidadY = velocidadEnYInicialLocal - aceleracionGravedadLocal*tiempoLocal;

    return velocidadY;
}

//Para crear el archivo
void imprimirDatosEnArchivo(FILE *archivo, double tiempoLocal, double velocidadEnYLocal, double posicionEnXLocal, double posicionEnYLocal)
{
    fprintf(archivo,"%16.8lf\t %16.8lf\t %16.8lf\t %16.8lf\t\n", 
    tiempoLocal, velocidadEnYLocal,posicionEnXLocal,posicionEnYLocal);
}


int main(void)
{
    double velocidadEnXInicial;
    double posicionEnXInicial; 
    double aceleracionGravedad = 9.8;

    double posicionEnYInicial; 
    double velocidadEnYInicial; 

    double tiempo;

    //Condiciones inciales
    posicionEnXInicial = 0.0; 
    posicionEnYInicial = 10.0; 
    velocidadEnYInicial = 0.0;
    velocidadEnXInicial=1.0;

    double tiempoMaximoDeSimulacion= sqrt(2.0*posicionEnYInicial/aceleracionGravedad);
    double deltaT = tiempoMaximoDeSimulacion/10000; //Ya que se tomo este como el numero optimo para el calculo

    printf("Condiciones inciales: \n\n"); 
    printf("(x_0,y_0)= (%lf, %lf)\n", posicionEnXInicial, posicionEnYInicial);
    printf("(v_0_x,v_0_y)=(%lf, %lf)\n", velocidadEnXInicial, velocidadEnYInicial);
    printf("g= %lf (m/s²)\n",aceleracionGravedad);

    FILE *archivoSimulacion; //Para crear el archivo de texto
    archivoSimulacion = fopen("parabolico_analitico.dat","w");

    //Primera fila
    imprimirDatosEnArchivo(archivoSimulacion, tiempo, velocidadEnYInicial,posicionEnXInicial,posicionEnYInicial);

    //Variables para que se alamcene el calculo
    double posicionEnX,posicionEnY,velocidadEnY;

    for(tiempo = deltaT; tiempo <= tiempoMaximoDeSimulacion; tiempo = tiempo + deltaT)

    {
        velocidadEnY = VelocidadEnY(tiempo,velocidadEnYInicial,aceleracionGravedad);
        posicionEnX = espacioRecorridoEnX(tiempo,velocidadEnXInicial,posicionEnXInicial);
        posicionEnY = espacioRecorridoenY(tiempo,velocidadEnYInicial,aceleracionGravedad,posicionEnYInicial);
        imprimirDatosEnArchivo(archivoSimulacion, tiempo, velocidadEnY,posicionEnX,posicionEnY); 
    
    }

fclose(archivoSimulacion);

    return 0; 
}