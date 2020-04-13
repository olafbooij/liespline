#!/home/obooij/linux/bin/gnuplot -persist
set terminal svg size 600,480 fixed enhanced fname 'Arial'  fsize 12 butt dashlength 1.0 
set output 'show_se3_interpolation.svg'
set view equal xyz
set view 54, 326, 1.6, 1
set xlabel "x"
set ylabel "y"
set zlabel "z"
unset key
splot "<./a.out" with lines lc rgb variable
#    EOF
