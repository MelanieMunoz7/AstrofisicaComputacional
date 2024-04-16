
set terminal pdf
set output "funcion_bessel_para_diferentes_alphas.pdf"
set grid

set xlabel "x" font ",16"
set ylabel "J_α(x)" font ",16"
set title "Funcion de Bessel para distintos valores de α" font ",20"
set border
set zeroaxis

plot "funcion_Bessel_alpha0.dat" w l lc rgb "red" lw 2 t "J_0(x)",\
"funcion_Bessel_alpha1.dat" w l lc rgb "green" lw 2 t "J_1(x)",\
"funcion_Bessel_alpha2.dat" w l lc rgb "blue" lw 2 t "J_2(x)"




