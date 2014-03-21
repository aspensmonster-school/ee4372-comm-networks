The project is to give examples of using each of the following utilities:

  * ping
  * traceroute
  * ifconfig
  * netstat

ping
====

`ping` option details:

  * -D : Mark each ping with a timestamp in form of unixtime + microseconds.
  * -i $someNum : Delay $someNum seconds between each ping.


    $ ping -D -i 5 synergy.txstate.edu
    [1395407774.856520] 64 bytes from excharray.txstate.edu (147.26.57.35): icmp_seq=1 ttl=61 time=2.46 ms
    [1395407779.854714] 64 bytes from excharray.txstate.edu (147.26.57.35): icmp_seq=2 ttl=61 time=1.94 ms
    [1395407784.862757] 64 bytes from excharray.txstate.edu (147.26.57.35): icmp_seq=3 ttl=61 time=4.84 ms
    [1395407789.866250] 64 bytes from excharray.txstate.edu (147.26.57.35): icmp_seq=4 ttl=61 time=4.02 ms
    [1395407794.865991] 64 bytes from excharray.txstate.edu (147.26.57.35): icmp_seq=5 ttl=61 time=3.35 ms
    ^C
    --- synergy.txstate.edu ping statistics ---
    5 packets transmitted, 5 received, 0% packet loss, time 20015ms
    rtt min/avg/max/mdev = 1.940/3.327/4.849/1.045 ms

As one can see here, pinging txstate's mailserver --synergy.txstate.edu-- 
shows that it is responding to queries. This is a good indication that the host 
is at least visible to the network. The timestamps between each ping also 
match the 5 second delay requested.

traceroute
==========

`traceroute` option details:

  * -m $someNum : $someNum specifies the maximum number of hops (max ttl value)
    that traceroute will probe. Default is 30, we chose 60 for the hell of 
it. 
  * -N $someNum : This option specifies the number of concurrent probe requests
    for traceroute to use. By default it is 16. However, nearly all network
hardware places ICMP traffic inthe absolute lowest priority and throttles it to
hell. So, we only go on at a time to try and avoid losing responses from nodes
along the path. This, combined with the default delay of 5 seconds between
queries, does a decent job of addressing the throttling issue, but isn't enough
on its own. Which is where the next option comes in.
  * -q $someNum : This option specifies the number of times to attempt to get 
a response from a node along the path. The default is three, but this 
typically is too low a number.
  * -T : Use TCP SYN packets as opposed to ICMP ECHO packets for probes.

ICMP ECHO probing:

    $ traceroute -m 60 -N 1 -q 2 synergy.txstate.edu
    traceroute to synergy.txstate.edu (147.26.57.35), 60 hops max, 60 byte packets
     1  * *
     2  147.26.251.6 (147.26.251.6)  3.279 ms  5.221 ms
     3  bobcatmail.txstate.edu (147.26.57.35)  1.039 ms  3.661 ms

    $ traceroute -m 60 -N 1 -q 5 synergy.txstate.edu
    traceroute to synergy.txstate.edu (147.26.57.35), 60 hops max, 60 byte packets
     1  10.36.1.254 (10.36.1.254)  1.469 ms * * * *
     2  147.26.251.6 (147.26.251.6)  8.676 ms  5.613 ms  2.984 ms  5.783 ms  7.539 ms
     3  bobcatmail.txstate.edu (147.26.57.35)  3.730 ms  1.223 ms *  4.647 ms  1.088 ms

TCP SYN probing:

    # traceroute -m 60 -T -N 1 -q 5 synergy.txstate.edu
    traceroute to synergy.txstate.edu (147.26.57.35), 60 hops max, 60 byte packets
     1  * * * * *
     2  147.26.251.6 (147.26.251.6)  8.560 ms  7.940 ms  3.109 ms  6.003 ms  4.174 ms
     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)  1.051 ms  1.043 ms  1.000 ms  1.093 ms  2.047 ms
     4  synergy.txstate.edu (147.26.57.35)  0.976 ms  0.913 ms  2.624 ms  1.178 ms  1.260 ms

    # traceroute -m 60 -T -N 1 -q 5 synergy.txstate.edu
    traceroute to synergy.txstate.edu (147.26.57.35), 60 hops max, 60 byte packets
     1  * * 10.36.1.254 (10.36.1.254)  1.217 ms  3.450 ms  7.184 ms
     2  147.26.251.6 (147.26.251.6)  19.542 ms  4.074 ms  3.117 ms  5.285 ms  3.050 ms
     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)  1.325 ms  1.367 ms  1.857 ms  1.274 ms  1.270 ms
     4  bobcatmail.txstate.edu (147.26.57.35)  1.221 ms  1.213 ms  4.708 ms  2.102 ms  1.577 ms


    # traceroute -m 60 -T -N 1 -q 5 synergy.txstate.edu
    traceroute to synergy.txstate.edu (147.26.57.35), 60 hops max, 60 byte packets
     1  * * * * *
     2  147.26.251.6 (147.26.251.6)  2.790 ms  4.269 ms  9.643 ms  3.065 ms  4.600 ms
     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)  1.225 ms  1.948 ms  1.236 ms  1.337 ms  1.255 ms
     4  excharray.txstate.edu (147.26.57.35)  1.215 ms  1.184 ms  2.022 ms  3.500 ms  2.380 ms


Observe how, on our first run, we were unable to identify the IP address of the
first hop when using two queries with ICMP ECHO probing. However, upon using
five, we were able to identify the IP address as 10.36.1.254. Now, we could
still just be dealing with throttling issues, and might intermittently get the
IP with 2 queries. But using 5 seems to be a good number to consistently
(usually, anyway) get an IP.  Notice that this isn't always enough though.
Using TCP SYN packets, we only intermittently got the IP address.

As well, notice that the path --as well as IP<->Hostname resolution-- seems 
to differ with each type of probing. The first two hops seem consistent 
across each type of probing:

     1  10.36.1.254 (10.36.1.254)
     2  147.26.251.6 (147.26.251.6)

For ICMP probing we find that the rest of the trip stops here for both of our
runs:

     3  bobcatmail.txstate.edu (147.26.57.35)

However, for TCP SYN probing, the trip continues like so in each of our 
three runs:

     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)
     4  synergy.txstate.edu (147.26.57.35)

     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)
     4  bobcatmail.txstate.edu (147.26.57.35)

     3  jck-slb3-ve57.tr.txstate.edu (147.26.57.100)
     4  excharray.txstate.edu (147.26.57.35)


Notice that TCP SYN probing shows a third hop through another host. As well, 
the IP address-host resolution seems conflicting. On one run, the server is 
called bobcatmail.tyxstate.edu while on another, it is called 
synergy.txstate.edu. And yet on a third, it is called excharray.txstate.edu.

### Sidenote:

The inconsistiency across runs with the traceroute tool can be mitigated by 
utilizing a tool called "mtr" that combines the capabilities of traceroute and 
ping, and provides some additional analysis. Consider:

`mtr` with ICMP ECHO probing:

    $ mtr -w -c 30 -b -i 5 --timeout 5 synergy.txstate.edu
    Start: Fri Mar 21 08:57:15 2014
    HOST: morpheus     Loss%   Snt   Last   Avg  Best  Wrst StDev
      1.|-- 10.36.1.254  76.7%    30   16.0   8.4   2.1  16.0   5.8
      2.|-- 147.26.251.6 33.3%    30   10.3  15.3   3.3  94.7  20.2
      3.|-- bobcatmail.txstate.edu (147.26.57.35) 23.3%    30    2.4   6.5   1.3  30.7   6.2

`mtr` with TCP SYN probing:

    $ mtr -w -c 30 -b -i 5 --timeout 5 -T synergy.txstate.edu
    Start: Fri Mar 21 09:01:36 2014
    HOST: morpheus                                     Loss%   Snt   Last   Avg  Best  Wrst StDev
      1.|-- 10.36.1.254                                  33.3%    30    1.6 1102.   1.2 3008. 1211.3
      2.|-- 147.26.251.6                                  0.0%    30    6.2   4.8   2.6  10.4   1.7
      3.|-- jck-slb3-ve57.tr.txstate.edu (147.26.57.100)  0.0%    30    1.1   3.1   1.0  52.4   9.3
      4.|-- bobcatmail.txstate.edu (147.26.57.35)         3.3%    30  1255. 2056. 1003. 2505. 576.2


Observe how the loss rate on the first node (10.36.1.254) is typically higher
than the others.  The fact that the D part of the address is 254 is good
indication that the first node is a router or switch of some sort. While not a
requirement of the networking protocol, most administrators will put specific
hardware on the beginning or end of a subnet (e.g., X.X.X.1, X.X.X.2,
X.X.X.253, X.X.X.254) as a matter of convention.

Also notice that `mtr` seems to regard the final hop with TCP SYN probing as 
bobcatmail.txstate.edu.

And since the differing hostnames were bothering me, here's `dig`'s report on 
the IP address:

    $ dig -x 147.26.57.35 +short
    excharray.txstate.edu.
    bobcatmail.txstate.edu.
    synergy.txstate.edu.

Ok, so it does look like all three hosts are bound to that same IP.

ifconfig
========

`ifconfig` is a legacy tool that has been deprecated in favor of the newer `ip`
tool. However, it was ubiquitous in its heyday and will probably continue to be
used for decades to come. It is used for managing network interfaces.

Seeing as I don't want to torch my own network interfaces by monkeying around 
too much with `ifconfig`, you're going to have to be content with a simple 
report of the network interfaces.

    # ifconfig -a
    eth0      Link encap:Ethernet  HWaddr XX:XX:XX:XX:XX:XX
              UP BROADCAST MULTICAST  MTU:1500  Metric:1
              RX packets:0 errors:0 dropped:0 overruns:0 frame:0
              TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
              collisions:0 txqueuelen:1000 
              RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
              Interrupt:20 Memory:fe200000-fe220000 
    
    lo        Link encap:Local Loopback  
              inet addr:127.0.0.1  Mask:255.0.0.0
              UP LOOPBACK RUNNING  MTU:65536  Metric:1
              RX packets:3199 errors:0 dropped:0 overruns:0 frame:0
              TX packets:3199 errors:0 dropped:0 overruns:0 carrier:0
              collisions:0 txqueuelen:0 
              RX bytes:641610 (626.5 KiB)  TX bytes:641610 (626.5 KiB)
    
    wlan0     Link encap:Ethernet  HWaddr XX:XX:XX:XX:XX:XX
              inet addr:10.36.27.156  Bcast:10.36.255.255  Mask:255.255.0.0
              UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
              RX packets:454778 errors:0 dropped:0 overruns:0 frame:0
              TX packets:206803 errors:0 dropped:0 overruns:0 carrier:0
              collisions:0 txqueuelen:1000 
              RX bytes:159627762 (152.2 MiB)  TX bytes:36698701 (34.9 MiB)

As you can see, at the time I completed this assignment, I was on a wireless 
network. The `wlan0` wireless interface holds the details of the interface. 
The address that was given to me by the TexasStateWPA wireless network was 
10.36.27.156. I have redacted the hardware addresses (MAC addresses), as they 
are intended to serve as unique identifiers for the specific hardware in my 
system. The are several status words as well for the `wlan0` interface, such 
as `UP` and `RUNNING`. Observe how, while the `eth0` interface is `UP`, it is 
not currently `RUNNING`.

netstat
=======

`netstat` is sort of like a swiss army knife of network statistics. It can 
show connections, routing tables, interface statistics, and perform all sorts 
of other fun networking tasks, like figuring out multicast memberships. I'll 
show a few handy examples.

### List all active network traffic on port 80:

Options:

  * -p : print the pid and name of program to which the socket belongs.
  * -n : only show numeric addresses. Do not attempt to resolve. If you leave
    this off, netstat will drop any line that it couldn't resolve. Seeing as
every connection is local (10.\*.\*.\*.), you won't ever see anything.
  * -t : Show only TCP sockets.
  * grep ":80" : This filters the list that netstat spits out for connections
that are speaking over port 80.


    $ netstat -pnt | grep ":80"
    (Not all processes could be identified, non-owned process info
     will not be shown, you would have to be root to see it all.)
    tcp        0      0 10.36.27.156:60494      23.35.171.27:80         ESTABLISHED 30923/firefox   
    tcp        0      0 10.36.27.156:48358      108.160.163.100:80      ESTABLISHED 3951/dropbox    


Notice how there are two processes with established connections on port 80, 
firefox and dropbox. Firefox is a web-browser and dropbox is a file-sync 
client.

It is important to note that netstat only shows what sockets and ports are 
being used at the moment it checks. Running the command again after not 
using the firefox web-browser for a few minutes yields:

    $ netstat -pnt | grep ":80"
    (Not all processes could be identified, non-owned process info
     will not be shown, you would have to be root to see it all.)
    tcp        0      0 10.36.27.156:48358      108.160.163.100:80      ESTABLISHED 3951/dropbox    

### List all listening sockets that have an associated pid:

Options:

  * -l : Show only listening sockets. That is, sockets that are actively
    listening for incoming connections, even if no connection is actually
established yet.
  * grep -v "-" : Filters out results that are not associated with a PID or 
process name.


    $ netstat -plnt | grep -v "-"
    (Not all processes could be identified, non-owned process info
     will not be shown, you would have to be root to see it all.)
    Active Internet connections (only servers)
    tcp        0      0 127.0.0.1:60885         0.0.0.0:*               LISTEN      31015/cli       
    tcp        0      0 0.0.0.0:17500           0.0.0.0:*               LISTEN      3951/dropbox    

Notice how dropbox is always listening for connections. This is to be 
expected; it is a file sync client that is always catching pings from remote 
servers that keep track of changes for a given fileset across different 
hosts. 

`cli` is a part of the Mono project. It is Mono's ECMA-CLI native 
code generator. Long story short, it tries to take applications written in 
.NET, and spit out native code that GNU/Linux can understand. In this case, 
it's keepass2, a password manager. The keepass2 binary is listening from 
127.0.0.1 --localhost, the local machine-- on port 60885 for connections from 
anywhere. Which actually sounds like a bad idea. And now I'm a little 
paranoid. But looking at active connections, it seems like this is just 
local network traffic between two sockets --namely, keepass2 and cli.

    $ netstat -taucp | grep 31015
    (Not all processes could be identified, non-owned process info
     will not be shown, you would have to be root to see it all.)
    tcp        0      0 localhost:60885         *:*                     LISTEN      31015/cli       
    tcp        0      0 localhost:37270         localhost:60885         ESTABLISHED 31015/cli       
    tcp        0      0 localhost:60885         localhost:37270         ESTABLISHED 31015/cli       

Still. I don't think it should be listening to ANY connection. It should be 
bound to localhost. I'll look into that later.
