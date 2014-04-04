set terminal pngcairo font "ariel,10"
set output "rssi.png"
set datafile sep ','

set title "RSSI versus Sample Number"
set xlabel "Sample Number (n)"
set ylabel "RSSI (dBm)"
set grid
plot "export_140321144244.csv" every::1::166 using 4 with lines title "Texas State Cell Network"
