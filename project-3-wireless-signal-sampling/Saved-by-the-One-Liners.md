Useful One-Liners
=================

Replace "Mar 2014" with "March 2014" so that gnuplot doesn't throw a hissy fit.

    $ for i in $(ls) ; do sed -i 's/Mar 2014/March 2014/g' $i ; done

Sort the data in each file by the id token, since apparently, gnuplot can 
recognize time, but plots it in the order you give it, rather than, you know, 
chronologically. Juststupidthings.

    $ for i in $(ls) ; do sort -t, -n -k 1 $i -o $i ; done

This will actually come in handy for my technical interview tomorrow for 
that system administration gig. Talk about killing two birds with one stone.
