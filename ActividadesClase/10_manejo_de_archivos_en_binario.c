/*Manejo de datos en binario - con datos de AM2229-735_925_HR_000.2*/

/*Librerias*/
#include<stdio.h>
#include<stdlib.h>

/*Macros y variables globales - permite que se hagan operaciones 
con 0,1,2 usando variables mas familiares */
#define X 0
#define Y 1
#define Z 2

/*Estructura de datos de la particula (seleccionando los datos con los que que queremos trabajar)*/
typedef struct
{
    int id;
    double pos[3];
    double vel[3];
    double masa; 
    double potencial;
}Particulas;

//Inilicializando los punteros 
Particulas *part, *part2;

//rutinas y funciones 
int contador_de_lineas(char *infile);

//funcion principal
int main(int argc, char *argv[]) 
{
    int i, nParticulas; 
    double dummy; //Se almacena basura
    char *infile, outfiles[200];
    infile = argv[1];

    printf("\narg[0]: %s\n", argv[0]);
    printf("\nargv[1]: %s\n",argv[1]);
    //Esto permite almacernar el nombre del archivo a trabjar en el argv[1], esto evita el renombrar compilando y compilando una y otra vez
    printf("\nLeyendo el archivo: %s\n", infile);
    
    /*Calculando el numero de lineas que contiene el archivo y este sera el numero de particulas
    Note que cambia para cada archivo*/
    nParticulas = contador_de_lineas(infile);
    printf("\nEl archivo contiene contine %d particulas\n", nParticulas);
 
    /*Alocacion dinamica de un arreglo tipo de Particulas*/

    part = (Particulas *) malloc((size_t)nParticulas * sizeof(Particulas)); //Mirar explicacion detallada en cuaderno

    //Si el codigo se cae o pasa algo en memoria
    if (part == NULL)
    {
        printf("Alocacion de part fallo\n");
        exit(0);
    }

    //uso de fscanf para leer archivos de datos en ascii
    printf("usando fscanf ...\n"); 
    FILE *fInfile = fopen(infile, "r");

  for( i=0; i<nParticulas; i++ )
    fscanf(fInfile,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
	   &part[i].id,
	   &part[i].pos[X],&part[i].pos[Y],&part[i].pos[Z],
	   &part[i].vel[X],&part[i].vel[Y],&part[i].vel[Z],
	   &part[i].masa,&part[i].potencial,
	   &dummy,&dummy,&dummy,&dummy,
	   &dummy,&dummy,&dummy,&dummy);
  fclose(fInfile);
  
  /*
  // uso de fscanf para leer archivos de datos en ascii
  printf("usando fscanf...\n");
  fInfile = fopen(infile,"r");
  for( i=0; i<nParticulas; i++ )
    fscanf(fInfile,"%d %lf %lf %lf %lf %lf %lf %lf %lf %*lf %*lf %*lf %*lf %*lf %*lf %*lf %*lf",
	   &part[i].id,
	   &part[i].pos[X],&part[i].pos[Y],&part[i].pos[Z],
	   &part[i].vel[X],&part[i].vel[Y],&part[i].vel[Z],
	   &part[i].masa,&part[i].potencial);
  fclose(fInfile);
  */
  // uso de fprintf para escribir archivos de datos en ascii
  printf("usando fprintf...\n");
  sprintf(outfiles,"%s_ascii_fprintf",infile);
  FILE *fOutfile = fopen(outfiles,"w");
  for( i=0; i<nParticulas; i++ )
    fprintf(fOutfile,"%d %lf %lf %lf %lf %lf %lf %lf %lf\n",
	    part[i].id,
	    part[i].pos[X],part[i].pos[Y],part[i].pos[Z],
	    part[i].vel[X],part[i].vel[Y],part[i].vel[Z],
	    part[i].masa,part[i].potencial);
  fclose(fOutfile);

  // uso de fwrite para escribir archivos de datos en binario
  printf("usando fwrite...\n");
  sprintf(outfiles,"%s_bin_fwrite",infile);
  FILE *fOutfile2 = fopen(outfiles,"wb");
  for( i=0; i<nParticulas; i++ )
    {
      fwrite( &part[i].id, sizeof(int), 1, fOutfile2);
      fwrite( &part[i].pos, sizeof(double), 3, fOutfile2);
      fwrite( &part[i].vel, sizeof(double), 3, fOutfile2);
      fwrite( &part[i].masa, sizeof(double), 1, fOutfile2);
      fwrite( &part[i].potencial, sizeof(double), 1, fOutfile2);
    }
  fclose(fOutfile2);
  free(part); // libero la memoria de part

  part2 = (Particulas *)malloc((size_t)nParticulas*sizeof(Particulas));
  if(part2 == NULL){
    printf("Alocacion de part2 fallo\n");
    exit(0);
  }

  // uso de fread para leer archivos de datos en binario
  printf("usando fread...\n");
  sprintf(outfiles,"%s_bin_fwrite",infile);
  FILE *fOutfile3 = fopen(outfiles,"rb");
  for( i=0; i<nParticulas; i++ )
    {
      fread( &part2[i].id, sizeof(int), 1, fOutfile3);
      fread( &part2[i].pos[X], sizeof(double), 3, fOutfile3);
      fread( &part2[i].vel[X], sizeof(double), 3, fOutfile3);
      fread( &part2[i].masa, sizeof(double), 1, fOutfile3);
      fread( &part2[i].potencial, sizeof(double), 1, fOutfile3);
    }
  fclose(fOutfile3);


  printf("usando fprintf...\n");
  sprintf(outfiles,"%s_ascii_fprintf2",infile);
  FILE *fOutfile4 = fopen(outfiles,"w");
  for( i=0; i<nParticulas; i++ )
    fprintf(fOutfile4,"%d %lf %lf %lf %lf %lf %lf %lf %lf\n",
	    part2[i].id,
	    part2[i].pos[X],part2[i].pos[Y],part2[i].pos[Z],
	    part2[i].vel[X],part2[i].vel[Y],part2[i].vel[Z],
	    part2[i].masa,part2[i].potencial);
  fclose(fOutfile4);
  
  return 0;
} // fin funcion principal 
// Esta funcion returna de lineas que tiene un archivo
// contando la cantidad de saltos de linea almacenados en el archivo
// hasta que encuentra el final del archivo. 

int contador_de_lineas(char *infile)
{
    int nLines = 0; //Inicializa el contador
    char c;
    FILE *pf;
    /*Si ocurre un error al abrir el archivo y que sus datos no se hayan 
    guardado en memoria RAM*/
    if ((pf=fopen(infile,"r")) == NULL) 
        {
            printf("no puedo abrir archivo %s\n",infile);
            exit(0);
        }
    
    /*Se realiza la lectura del archivo con el contador, usando una funcion que lee los carcateres del 
    archivo, hasta llegar al \0 (EOF en codigo ascii), pero note que no se incluye este ultimo caracter
    por la forma en que se le suma a nLines*/
    while ((c=fgetc(pf)) != EOF) //fgetc funciona similar a getchar, solo que se usa en lectura de archivos
        if (c=='\n')
        ++nLines;
    fclose(pf);

    return nLines;
}

// NOTA: grafique en gnuplot con:
// plot "AM2229-735_925_HR_000.2_ascii_fprintf" every 100 u 2:3,"AM2229-735_925_HR_000.2_ascii_fprintf2" every 100 u 2:3,"AM2229-735_925_HR_000.2_bin_fwrite" binary format="%d%lf%lplot "AM2229-735_925_HR_000.2_ascii_fprintf" every 100 u 2:3,"AM2229-735_925_HR_000.2_ascii_fprintf2" every 100 u 2:3,"AM2229-735_925_HR_000.2_bin_fwrite" binary format="%d%lf%lf%lf%lf%lf%lf%lf%lf" every 100 u 2:3f%lf%lf%lf%lf%lf%lf" every 100 u 2:3