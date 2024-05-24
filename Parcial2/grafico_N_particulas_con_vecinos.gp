set terminal pdf
set output "Particula_seleccionada_con_vecinos.pdf"
set grid

set xlabel "x" font ",10"
set ylabel "y" font ",10"
set title "Vecinos para una particula de una distribucion de 1000 particulas" font ",14"
set border


plot "posiciones_puntos.dat" u 2:3 w p ps 0.5 pt 7 lc rgb "black" not, \
    "puntos_vecinos.dat" u 2:3 w  p ps 0.5 pt 7 lc rgb  "red" not, \
    "posiciones_puntos.dat" every ::4::4 u 2:3 w p ps 0.5 pt 7 lc rgb "web-green" not
