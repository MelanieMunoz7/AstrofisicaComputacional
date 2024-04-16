#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Punto 3: parcial 1 - astrofisica computacional
Nombre: Melanie Andre Munoz Chavarria*/

/*Realice un codigo para calcular el factorial de un numero. 
Luego, use este codigo como una funcion para calcular la funcion de Bessel de orden 
alpha, J_alpha(x) usando la definicion dada.
Haga una grafica con la funcion de Bessel de orden 0, 1, y 2 simular a la de la figura.*/

/*Primero calculemos el factorial de un numero*/

double factorialDeUnNumero(double NumeroLocal) 
{   //Definiendo las variables para acumular la multiplicacion y que nos permitiran iterar sobre el numero dado
    double factorial;
    double iterador;

    //Inicializando el factor para acumular la multiplicacion
    factorial = 1;
    
    // Usando un ciclo para calcular el facotiral, iniciando en uno e incrementando hasta llegar al numero dado
    for (iterador = 1; iterador <= NumeroLocal; iterador = iterador + 1) {
        factorial = factorial * iterador;
    }
    
    return factorial;
}

/*Ahora definiendo de forma global la funcion de Bessel*/

double FuncionBessel(int limiteSuperiorSumatoriaLocal,double xLocal, int alphaLocal)
{   
    //Definiendo los parametros que permiten acumular la sumatoria
    double SumaDeBessel; 
    int indiceSumatoria;

    //Definiendo el valor que se le suma en cada termino a la sumatoria y algunas operaciones que se hacen en la sumatoria
    double resultadoOperacionASumar;
    double primeraDivisionDeLaSumatoria;
    double segundaDivsionDeLaSumatoria;
    double sumaDeIndiceSumatoriaMasAlpha; 



    //Inicializandolo
    SumaDeBessel = 0.0;

    //En este ciclo se incia, finaliza y aumenta dadas las condiciones de la serie que define la funcion

    for (indiceSumatoria = 0; indiceSumatoria < limiteSuperiorSumatoriaLocal; indiceSumatoria = indiceSumatoria + 1)
    {   
        sumaDeIndiceSumatoriaMasAlpha = indiceSumatoria + alphaLocal;
        primeraDivisionDeLaSumatoria = pow(-1, indiceSumatoria)/(factorialDeUnNumero(indiceSumatoria)*factorialDeUnNumero(sumaDeIndiceSumatoriaMasAlpha));
        segundaDivsionDeLaSumatoria = pow(xLocal / 2,(2*indiceSumatoria + alphaLocal));

        resultadoOperacionASumar = primeraDivisionDeLaSumatoria * segundaDivsionDeLaSumatoria;

        SumaDeBessel = SumaDeBessel + resultadoOperacionASumar;
    }

    return SumaDeBessel;
}

/*Ahora Creando una funcion que me genere un archivo para alamanar los datos*/

//Esta funcion se basa en la creada en el codigo 7_rutinas_y_funciones.c
void imprimirDatosEnArchivo(FILE *archivo, double xLocal, double FuncionDeBesselEnXLocal)
{
    fprintf(archivo,"%16.8lf\t %16.8lf\t\n", xLocal, FuncionDeBesselEnXLocal);

}

int main(void)
{ 
    /*Probando que la funcion definida para el factorial funciona*/

    printf("El factorial de 0 = %lf, el facotorial de 10 = %lf y el facotorial de 1 = %lf\n", factorialDeUnNumero(0), factorialDeUnNumero(10), factorialDeUnNumero(1));

/*Definiendo las variables para graficar la funcion de Bessel*/

    double x; 
    double pasoDeX; //Como se va a iterar sobre x, entonces es necesario que su valor aumente cierto valor
    int alpha;
    int limiteSuperiorSumatoria; 
    double FuncionDeBesselEnX;

    //Definiendo algunos valores

    limiteSuperiorSumatoria = 150; //Para valores mucho mayores a este la serie diverge
    pasoDeX = 0.1; //Para lograr un grafica similar a la que se suministra

    //Para ingresar el valor de alpha
    printf("Ingrese el valor de alpha: \n");
    scanf("%d", &alpha);

    //Creando el archivo para guardar los resultados
    FILE *archivoSimulacion; //Para crear el archivo de texto
    archivoSimulacion = fopen("funcion_Bessel.dat","w");

    /*Calculando la funcion de Bessel para cada x de 0 a 20 con paso de 1.0*/

    for (x = 0.0; x <= 20.0; x = x + pasoDeX)
    {
        FuncionDeBesselEnX = FuncionBessel(limiteSuperiorSumatoria, x, alpha);
        imprimirDatosEnArchivo(archivoSimulacion,x,FuncionDeBesselEnX);
    }

    fclose(archivoSimulacion); //Cerrando el archivo creado

    return 0;
}
