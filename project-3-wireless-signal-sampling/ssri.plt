set terminal pngcairo font "ariel,10"
set output "ssri.png"
set datafile sep ','

set title "SSRI versus Sample Number"
set xlabel "Sample Number (n)"
set ylabel "SSRI (dBm)"
set grid
plot "export_140321144244.csv" every::1::166 using 4 with lines title "Texas State Cell Network"
