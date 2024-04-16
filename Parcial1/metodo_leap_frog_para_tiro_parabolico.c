#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*Punto 4: Parcial 1, astrofisica computacional, Melanie Andrea Munoz Chavarria*/

/*Consulte el metodo de integracion de  leap-frog y programarlo para repetir el 
experimento numerico de clase correspondiente a encontrar el numero de puntos  
optimo para hacer una simulacion confiable del tiro parabolico. Luego, compare 
los resultados del experimento usando los dos integradores y concluya acerca de 
cual es el mejor metodo de integracion para hacer la simulacion.*/

/*Variables globales*/
double aceleracionGravedad= 9.8; 
double velocidadEnXInicial;

/*Definiendo la funcion para almacenar los datos del tiro parabolico*/

void imprimirDatosEnArchivoTiro(FILE *archivo, double tiempoLocal, double velocidadEnYLocal, double posicionEnXLocal, double posicionEnYLocal)
{
    fprintf(archivo,"%16.8lf\t %16.8lf\t %16.8lf\t %16.8lf\t\n", 
    tiempoLocal, velocidadEnYLocal,posicionEnXLocal,posicionEnYLocal);
}

/*Definiendo la funcion para almacenar los datos de error de la energia*/
void imprimirDatosEnArchivoErrorEnergia(FILE *archivo, double tiempoLocal, double EnergiaParaCadaTiempoLocal, double errorRelativoEnergia)
{
    fprintf(archivo,"%16.10lf\t%16.10lf\t%16.10lf\t\n", 
    tiempoLocal, EnergiaParaCadaTiempoLocal,errorRelativoEnergia);
}

/*Definiendo una funcion para calcular la energia*/

double calcularEnergia(double masaLocal,double posicionEnYLocal, double velocidadEnYLocal)
{
    double energia, magnitudVelocidadAlCuadrado;

    magnitudVelocidadAlCuadrado = pow(velocidadEnXInicial,2) + velocidadEnYLocal * velocidadEnYLocal;
    energia= masaLocal * aceleracionGravedad * posicionEnYLocal + 0.5 * masaLocal * magnitudVelocidadAlCuadrado;
    return energia;
}

int main (void)
{
    //Condiciones inciales
    double posicionEnXInicial = 0.0; 
    double posicionEnYInicial = 10.0; 
    double velocidadEnYInicial=0.0;
    
    velocidadEnXInicial = 1.0;

    //Variables de tiempo y energia
    double tiempoMaximoDeSimulacion= sqrt(2.0*posicionEnYInicial/aceleracionGravedad);
    double tiempo, deltaT;
    double errorRelativoEnergia;
    double EnergiaParaCadaTiempo;
    int numeroDePuntos;

    double masa=1.0; //kg

    //Variables que van a evolucionar
    double velocidadEnYMedia; //La clave del metodo de leap frog
    double posicionEnX,posicionEnY,velocidadEnY;

    //Calculando la energia incial del sistema
    double EnergiaInicial; 
    EnergiaInicial = calcularEnergia(masa, posicionEnYInicial,velocidadEnYInicial);

   

//=============================================================================
/*Para el caso de Euler se llego a la conclusion que para 1000 puntos el error retativo
de energia que se queria, que era de 0.1%*/

    numeroDePuntos = 10000;
    deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;

    //Inicializando las variable
    posicionEnX = posicionEnXInicial;
    posicionEnY = posicionEnYInicial;
    velocidadEnY = velocidadEnYInicial;

    //Creando el archivo para guardar los datos del tiro y de la energia
    FILE *archivoSimulacionTiro; //Para crear el archivo de texto
    archivoSimulacionTiro = fopen("parabolicoLeapFrog.dat","w");

    FILE *archivoSimulacionEnergia; //Para crear el archivo de texto
    archivoSimulacionEnergia = fopen("conservacionEnergiaLeapFrog.dat","w");

    //Guardando los primeros datos inciales del tiro y la energia
    imprimirDatosEnArchivoTiro(archivoSimulacionTiro, tiempo, velocidadEnY,posicionEnX,posicionEnY);
    imprimirDatosEnArchivoErrorEnergia(archivoSimulacionEnergia,0.0, EnergiaInicial,0.0);

    //Este ciclo itera desde un tiempo superior al incial y menor o igual al tiempo de maxima simulacion, con un paso de deltaT
    for (tiempo = deltaT; tiempo <= tiempoMaximoDeSimulacion; tiempo = tiempo+deltaT)
    {   
        //Para medio paso
        velocidadEnYMedia = velocidadEnY - aceleracionGravedad * deltaT * 0.5;
        //Actualizacion en las posiciones
        posicionEnY = posicionEnY + velocidadEnYMedia * deltaT; 
        posicionEnX = posicionEnX + velocidadEnXInicial * deltaT;

        //Actualizar velocidad en y
        velocidadEnY = velocidadEnYMedia- aceleracionGravedad * deltaT *0.5;

        //Ahora calculando la energia
        EnergiaParaCadaTiempo = calcularEnergia(masa, posicionEnY ,velocidadEnY);
        errorRelativoEnergia = fabs(EnergiaInicial-EnergiaParaCadaTiempo)/EnergiaInicial;


        //Guardando los valores de energia y del tiro
        if (posicionEnY >= 0.0)
        { 
            imprimirDatosEnArchivoTiro(archivoSimulacionTiro, tiempo, velocidadEnY,posicionEnX,posicionEnY); 
            imprimirDatosEnArchivoErrorEnergia(archivoSimulacionEnergia, tiempo, EnergiaParaCadaTiempo, errorRelativoEnergia); 
        }
    
        else
            break;
    }

    //Cerrando los archivos
    fclose(archivoSimulacionTiro);
    fclose(archivoSimulacionEnergia);

    return 0;
}