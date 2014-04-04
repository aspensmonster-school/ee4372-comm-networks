set terminal pngcairo font "ariel,10"
set output "wifi.png"
set datafile sep ','

# gotta set the timfmt right. In our data, it's like this:
# 21 Mar 2014 14:29:00
set timefmt '%d %B %Y %H:%M:%S'
set xdata time
set format x "%M:%S"

set title "RSSI of Various WiFi Networks Over Time"
set xlabel "Time"
set ylabel "RSSI (dBm)"
set grid
plot "wifi_140403220558.csv" using 5:6:4 with lines title $6
