

set terminal pdf
set output "grafico_para_cada_energia.pdf"
set grid

set xlabel "t [s]" font ",16"
set ylabel "E(t) [J]" font ",16"
set title "Energía Tiro Parabólico" font ",20"
set border
set zeroaxis
set yrange [98.4:98.6]

plot "conservacion_energia10000.dat" u 1:2 w l lc rgb "red" lw 2 t "Energia mecanica Euler",\
"conservacionEnergiaLeapFrog.dat" u 1:2 w l lc rgb "green" lw 2 t "Energia mecanica Leap-Frog"