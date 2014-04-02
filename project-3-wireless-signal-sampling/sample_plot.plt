set terminal pngcairo font "ariel,10"
set output "graph.png"
set datafile sep ','

set multiplot layout 3, 1

#4 - SSRI

set size 1,0.333
set title "SSRI versus Sample Number"
set xlabel "Sample Number (n)"
set ylabel "SSRI (dBm)"
set grid
plot "export_140321144244.csv" every::1::166 using 4 with lines title "Texas State Cell Network"

#20 - mobile rx

set size 1,0.333
set title "Mobile RX versus Sample Number"
set xlabel "Sample Number (n)"
set ylabel "Mobile RX (bytes)"
set grid
plot "export_140321144244.csv" every::1::166 using 20 with lines title "Texas State Cell Network"

#21 - mobile tx

set size 1,0.333
set title "Mobile TX versus Sample Number"
set xlabel "Sample Number (n)"
set ylabel "Mobile TX (bytes)"
set grid
plot "export_140321144244.csv" every::1::166 using 21 with lines title "Texas State Cell Network"

unset multiplot
