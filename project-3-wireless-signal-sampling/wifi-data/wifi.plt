set terminal pngcairo size 1600,800 font "ariel,10"
set output "wifi.png"
set datafile sep ','
set key below

# gotta set the timfmt right. In our data, it's like this:
# 21 Mar 2014 14:29:00
set timefmt '%d %B %Y %H:%M:%S'
set xdata time
set format x "%M:%S"

set title "RSSI of Various WiFi Networks Over Time"
set xlabel "Time"
set ylabel "RSSI (dBm)"
set grid

#plot "segregated-by-ssid/wifi-1001.csv" using 5:4 with lines title "1001", \
#     "segregated-by-ssid/wifi-TexasStateWPA.csv" using 5:4 with lines title "TexasStateWPA", \
#     "segregated-by-ssid/wifi-TexasStateUniversity.csv" using 5:4 with lines title "TexasStateUniversity",\
#     "segregated-by-ssid/wifi-HP-Print-1B-Officejet-6700.csv" using 5:4 with lines title "A fucking printer"

plot for [fn in system("ls segregated-by-ssid/ | grep wifi- | grep -v unknown ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn
