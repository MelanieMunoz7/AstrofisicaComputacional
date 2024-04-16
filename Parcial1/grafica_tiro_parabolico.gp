
set terminal pdf
set output "tiro_parabolico.pdf"
set grid

set xlabel "x (t) [m]" font ",16"
set ylabel "y (t) [m]" font ",16"
set title "Tiro parabólico" font ",20"
set border
set zeroaxis

plot "parabolico_analitico10000.dat" u 3:4 w l lc rgb "red" lw 2 t "Solucion analitica",\
"parabolico_10000.dat" u 3:4 w l lc rgb "green" lw 2 t "Solucion Euler",\
"parabolicoLeapFrog.dat" u 3:4 w l lc rgb "blue" lw 2 t "Solucion Leap-Frog"
