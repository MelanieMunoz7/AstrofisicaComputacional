/*Parcial 2 - Astrofisica Computacional
Punto 1: codigo con errores 
Melanie A. Munoz Chavarria*/
/*
Ultima modificacion :
Este programa lee un archivo de parametros que
contine comentarios y nombres de las variables

compile con : gcc 1_programa_basico_en_c_11.c -o 1_programa_basico_en_c_11.out
Ejecute con : ./1_programa_basico_en_c_11.out <archivo de parametos a leer> <
simbolo de determina un comentario>

Entrada : nombre archivo de parametros (string), caracter que simboliza un
comentario

Salida : Lectura del archivo de parametros en pantalla
*/

// librerias de C
#include<stdio.h>
#include<stdlib.h> /*Error de sintaxis, la libreria deberia ser stdlib.h*/
#include<string.h>

// variables globales
int nLineasArchivo;
int tamanoString = 1000;

//Se define la estructura de los parametros del archivo
struct Parametros
{
char Infile[200]; //Nombre del archivo de entrada
char Outfile[200]; //Nombre del archivo de salida
int Ncuerpos; //Numero de cuerpos en la simulacion
double tIntegracion; //Tiempo de la integracion
} parametros; /*Error de sintaxis; se debe usar ";" despues de definir la variable de estructura*/

// Inicializa rutinas y funciones
int contador_de_lineas(char *infile);
int lee_linea_archivos(char *infile, char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo]);
int extrae_valores_parametros(char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo]);

//Funcion principal
int main(int argc, char *argv[]) /*Error de sintaxis; [] tiene que ser la direccion de un punteros a caracteres*/
{
    // recibe por linea de comandos el nombre del archivo de parametros
    char *infile, *simboloComentario, comentario; 
    infile = argv[1]; //Tiene el nombre del documento
    simboloComentario = argv[2]; //Tiene los comentario que agregue el usuario

    printf("Esta es la fila 0 de argv: %s\n",argv[0]); //Tiene el nombre del ejecutable
    printf("Leyendo archivo : %s\n",infile);
    printf("Comentarios definidos por : %s\n",simboloComentario);
    comentario = simboloComentario[0]; //Asigna el primer caracter de simboloComentario a comentario
    printf("Comentarios : %c\n",comentario); /*Error logico; es necesario que sea %c*/


    // calculo el numero de lineas que contiene el archivo
    nLineasArchivo = contador_de_lineas(infile); /*Error logico; no se necesita el operador de direccion*/


    printf("el archivo contiene %d lineas\n\n",nLineasArchivo);
    char lineas[nLineasArchivo][tamanoString]; // matriz de lineas
    //Las finlas de la matriz tiene la cantidad de lineas del archivo 
    //Las columnas van a quedar del tamano de la variable gobal
    int ignorar[nLineasArchivo]; // vector que controla si una linea es ignorada

    // lee todas las lineas del archivo de parametros
    lee_linea_archivos(infile, lineas, comentario, ignorar);

        // extrae los valores de los parametros desde las lineas leidas
    extrae_valores_parametros( lineas, comentario, ignorar);

    // Imprime los parametros
    printf("\n\nParametros :\n");
    printf("======================\n");
    printf("parametros.Infile = %s\n",parametros.Infile);
    printf("parametros.Outfile = %s\n",parametros.Outfile);
    printf("parametros.Ncuerpos = %d\n",parametros.Ncuerpos);
    printf("parametros.tIntegracion = %lf\n",parametros.tIntegracion);
    printf("======================\n");

    return 0;
} //Fin funcion principal

// Esta funcion returna de lineas que tiene un archivo
// contando la cantidad de saltos de linea almacenados en el archivo
// hasta que encuentra el final del archivo.

int contador_de_lineas(char *infile)
{

    int nLineas = 0; //Inicializa el contador en 0
    char c; //Almacenara las lineas en cada iteracion
    FILE *pf; //archivo

    //Por si ocurre un error al abrir el archivo y que sus datos no se hayan 
    //guardado en memoria RAM
    if( (pf=fopen(infile,"r")) == NULL )
        {
            printf("no puedo abrir archivo %s\n",infile);
            exit(0);
        }

    //*Se realiza la lectura del archivo con el contador, usando una funcion que lee 
    //los carcateres del archivo, hasta llegar al \0 (EOF en codigo ascii), 
    //pero note que no se incluye este ultimo caracter
    //por la forma en que se le suma a nLines incrementando e imprimiendo lo que incrementa
    while( (c=fgetc(pf)) != EOF ) /*Error sintaxis: se debe usar fgetc en vez de getc*/
        if( c=='\n' ) 
        ++nLineas;
    
    fclose(pf);
    return nLineas;

}

// Esta funcion lee todas las lineas del archivo de parametros y la almacena
// en la matriz de linea, cada una es un string.
int lee_linea_archivos(char *infile, char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo])
{
    int i, j; //Contadores para filas y columnas
    char c; /*Error 6 de sintaxis; string es una variable de python*/
    //Almacenara los valores en cada interacion
    FILE *fInfile = fopen(infile,"r");/*Error; error logico puede que no lea en algunos compiladores*/

    printf("Archivo leido:\n");
    printf("===============================\n");
    for( i=0; i<nLineasArchivo; i++ ) /*Error de sintaxis; el inicio-parada-paso deben estar sepadaras por ;*/
    {
        //Inicializa el ignorar[i] y el valor de j en 0
        j = ignorar[i] = 0;

        // detecta lineas en blanco y debe ignorarse
        if( (c = fgetc(fInfile)) == '\n' ) //Se leen los caracteres del archivo
            {
                ignorar[i] = 1; //La componente i del vector cambia 
                L[i][j] = c; /*Error de sintaxis; note que esta igualando un array de caracteres a un caracter*/
                    //Asi asigna el valor de '/n' a esa entrada de la matriz
                printf(" - ignorar %d\n",ignorar[i]);
               continue; //Pasa a la siguiente iteracion, sin ejecutar el resto
           }
        else
            {
                L[i][j++] = c; //almacena el primer caracter de la matriz
                    // se debe ignorar las lineas que inicien con el simbolo de comentario y el EOF
                if( (c == comentario) || (c == EOF) ) /*Error 8 sintaxis; se debe usar ||*/
                ignorar[i] = 1;

                while( (c = fgetc(fInfile)) != '\n' ) /*Error 9 sintaxis, comparacion con caracter*/
                    L[i][j++] = c; //Continua recorriendo la fila y almacenando los caracteres
            }

        L[i][j] = '\0'; //Termina la linea
        printf("%s - ignorar %d\n",L[i],ignorar[i]);  /*Error sintaxis, imprimer 1 variable tipo char y otra tipo entero*/
    }
    printf("===============================\n");

    fclose(fInfile);
    return 0;
}

// Esta funcion extrae los valores de los parametros desde las lineas leidas
int extrae_valores_parametros( char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo])
{
    //Valores a iterar en en el ciclo y cantidad de parametros que se extraen del documento
    int i, j, totalParametros = 4;
    //Itera sobre los parametros
    int nParametro; /*Error logico, al ser constante no puede variar*/
    //Arreglos de caracteres con que alamacenan 299 caracteres,
    //Para almacenar las lineas en cada ciclo
    char string1[300], string2[300], string3[300];
    //Almacena los valores de los parametos
    char nombreParametros[totalParametros][200];
    //Almacena las direcciones de memoria de las componentes de Parametros
    void *apuntadorParametro[totalParametros];
    //Almacena el tipo de parametro
    int tipoParametro[totalParametros];

    // Macros, esto lo veremos despues
    #define INT 1 /*Error de sintaxis, no son necesarios los puntos y coma*/
    #define DOUBLE 2
    #define STRING 3

    // asocia los nombres de los parametros con las variables que los va a almacenar
    nParametro = 0; /*Error logico, == es para comparar, no igualar*/

    //Asigna a la componente de nombreParametro[nParametro] el nombre "Infile"
    strcpy(nombreParametros[nParametro], "Infile");
    //Asigna a la componente apuntadorParametro[nParametro] la direccion de el acceso
    //a la componente Infile de la estructura Parametros.
    apuntadorParametro[nParametro] = &parametros.Infile;
    //Aumenta nParametro y le asigna el macro al valor a tipoParametro[nParametro++]
    tipoParametro[nParametro++] = STRING;

    //Asigna a la componente de nombreParametro[nParametro] el nombre "Outfile"
    strcpy(nombreParametros[nParametro], "Outfile");
    //Asigna a la componente apuntadorParametro[nParametro] la direccion de el acceso
    //a la componente Outfile de la estructura Parametros.
    apuntadorParametro[nParametro] = &parametros.Outfile;
    //Aumenta nParametro y le asigna el macro al valor a tipoParametro[nParametro++]
    tipoParametro[nParametro++] = STRING;

    //Asigna a la componente de nombreParametro[nParametro] el nombre "Ncuerpos"
    strcpy(nombreParametros[nParametro], "Ncuerpos");
    //Asigna a la componente apuntadorParametro[nParametro] la direccion de el acceso
    //a la componente Ncuerpos de la estructura Parametros.
    apuntadorParametro[nParametro] = &parametros.Ncuerpos;
    //Aumenta nParametro y le asigna el macro al valor a tipoParametro[nParametro++]
    tipoParametro[nParametro++] = INT;

    //Asigna a la componente de nombreParametro[nParametro] el nombre "Ncuerpos"
    strcpy(nombreParametros[nParametro], "tIntegracion");
    //Asigna a la componente apuntadorParametro[nParametro] la direccion de el acceso
    //a la componente Ncuerpos de la estructura Parametros.
    apuntadorParametro[nParametro] = &parametros.tIntegracion;
    //Aumenta nParametro y le asigna el macro al valor a tipoParametro[nParametro++]
    tipoParametro[nParametro++] = DOUBLE;


    printf("\n\nLineas leidas a tramos\n");
    printf("=============================\n");
    for( i=0; i<nLineasArchivo; i++ )
    {
        //Para evitar lineas en blanco
        if( ignorar[i] == 0 )
    {   
        //Lee las lineas y les asigna a los char *
        sscanf(L[i],"%s%s%s", string1, string2, string3); /*Error de sintaxis, sobra un elemento %s*/
        printf("string1 = %s - string2 = %s - string3 = %s\n",string1, string2,string3);

        // encuentra el parametro en la lista de parametros
        //Note que sirve para que si se encuentra el parametro ya no sea necesario continuar
        for( j=0; j<totalParametros; j++ )
            //La funcion strcmp comparara los arreglos de caracteres y si son iguales retorna 0
            if( strcmp(string1,nombreParametros[j]) == 0 ) /*Error de sintaxis, el operador es ==*/
                break;

        // asigna el parametro a la variable correspondiente
        switch ( tipoParametro[j] )
            {   
                case INT:
                //Se hace el casting del puntero a un entero,
                // luego se le asigna al valor guardado en la memoria
                //a la variable tipo char * que pasa a ser entero
                    *((int *) apuntadorParametro[j]) = atoi(string2); /*Error logico, se iguala un entero a un double*/
                    break;
                case DOUBLE:
                //Se hace el casting del puntero a un double,
                // luego se le asigna al valor guardado en la memoria
                //a la variable tipo char * que pasa a ser double
                    *((double *) apuntadorParametro[j]) = atof(string2);
                    break;
                case STRING:
                    //Asigna el contenido de string2 a la direccion de memoria de apuntadorParametro[j]
                    strcpy(apuntadorParametro[j], string2);
                    break; /*Error: falta un break*/

            }
    
    }
    }
printf("=============================\n");
return 0;
}