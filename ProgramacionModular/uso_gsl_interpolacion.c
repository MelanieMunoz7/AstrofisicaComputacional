#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main()
{
    //Iterador y cantidad de datos en la tabla 
  int i , nDatos=91;
  double logT[nDatos], densidad[nDatos], logLambda[nDatos]; //Lambda es funciomn enfriamiento
  double lT, enfriamiento;
  
  FILE *fTabla =  fopen("filtrada_m-nil.dat","r");
  
  for( i=0; i<nDatos; i++ )
    fscanf(fTabla,"%lf %lf %lf", &logT[i], &densidad[i], &logLambda[i]);
  
  fclose(fTabla);
  
  // defino variables tipo gsl
  gsl_spline *interpolador;
  gsl_interp_accel *acelerador;
  
  // Aloco e inicializo las variable de gsl
  acelerador = gsl_interp_accel_alloc();
  interpolador = gsl_spline_alloc(gsl_interp_linear, nDatos);
  gsl_spline_init (interpolador, logT, logLambda, nDatos);
  
  // Evaluo el interpolador
  FILE *fInterpolacion = fopen("enfriamiento_interpolado.dat","w");
  for( lT=logT[0]; lT<logT[nDatos-1]; lT += 0.01 )
    {
      enfriamiento = gsl_spline_eval(interpolador, lT, acelerador);
      fprintf(fInterpolacion,"%lf %lf\n",lT,enfriamiento);
    }
  fclose(fInterpolacion);
  
  //libero las variables tipo gsl
  gsl_spline_free (interpolador);
  gsl_interp_accel_free (acelerador);
  
  
  return 0;
}
