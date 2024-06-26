#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

int main (void)
{
  double x = 5.0;
  double y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);
  return 0;
}

// compilar con: gcc -Wall -I/home/melanie/local/include/ uso_gsl.c -L/home/melanie/local/lib -lgsl -lgslcblas -o uso_gsl.out

// export PATH=$PATH:/home/melanie/local/bin
// LD_LIBRARY_PATH=/home/melanie/local/lib
// export LD_LIBRARY_PATH
