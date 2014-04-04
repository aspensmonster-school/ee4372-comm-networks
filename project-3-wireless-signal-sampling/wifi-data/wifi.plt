# pngcairo is pretty. Graph needs to be big, so 1600x800 will work.
set terminal pngcairo size 1600,800 font "ariel,10"

# we're gonna set the output file with the '>' operator on the command line.
# set output "wifi.png"

# Data files are CSV. So comma-delimited
set datafile sep ','

# Put the key/legend below the graph, rather than inside the graph.
set key below

# gotta set the timfmt right. In our data, it's like this:
# 21 Mar 2014 14:29:00
set timefmt '%d %B %Y %H:%M:%S'

# Tell gnuplot that xdata is time
set xdata time

# Tell gnuplot to only use minutes and seconds for labels.
# We don't want the full timestamp polluting the axis.
set format x "%M:%S"

# Our data might have different ranges depending on what we plot. 
# We want all of our plots to line up though. So be sure to manually 
# specify the xrange. We would normally use multiplot for this purpose, 
# but there's just too much data and the resulting plot would be entirely
# too unwieldy. Well, more unwieldy that it already is.
set xrange [ "21 March 2014 14:28:00":"21 March 2014 14:44:00" ]

# set the plot title
set title "RSSI of EVERYTHING"

# x-axis label
set xlabel "Time"

# y-axis label
set ylabel "RSSI (dBm)"

# turn on the grid so that it's easier to read the plot
set grid

# Old way of plotting.
#plot "segregated-by-ssid/wifi-1001.csv" using 5:4 with lines title "1001", \
#     "segregated-by-ssid/wifi-TexasStateWPA.csv" using 5:4 with lines title "TexasStateWPA", \
#     "segregated-by-ssid/wifi-TexasStateUniversity.csv" using 5:4 with lines title "TexasStateUniversity",\
#     "segregated-by-ssid/wifi-HP-Print-1B-Officejet-6700.csv" using 5:4 with lines title "A fucking printer"

# Now apparently gnuplot has a fancy schmancy new way to iterate over lots of 
# data files. Awesome!

################################################################################

# Everything
plot for [fn in system("ls segregated-by-ssid/ | grep wifi- ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

# Everything except the unknowns
#plot for [fn in system("ls segregated-by-ssid/ | grep wifi- | grep -v unknown ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

# Just TexasState wireless
#plot for [fn in system("ls segregated-by-ssid/ | grep wifi- | grep Texas ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

# Just the Unknowns
#plot for [fn in system("ls segregated-by-ssid/ | grep wifi- | grep unknown ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

# Just the printers.
#plot for [fn in system("ls segregated-by-ssid/ | grep wifi- | grep HP ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

# Just the Tram and other official texas state signals
#plot for [fn in system("ls segregated-by-ssid/just-txstate-stuff/ ")] 'segregated-by-ssid/'.fn using 5:4 with linespoints title fn

