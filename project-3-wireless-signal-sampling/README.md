You Can't Stop The Signal
=========================

This project focused on wireless communications technologies. We were
responsible for sampling GPS co-ordinates, cell phone signals (including UMTS
and any other data channels like HSPA+), and WiFi signals at various sites. We
were then to plot this data in a variety of ways that we would consider
interesting.

Our group sampled all of these signals along a path. That path is detailed in
the path-data directory of this repository. The path was taken by a person with
an android phone utilizing the "RF Signal Tracker" application to sample all
available wireless signals, and the average speed of the individual was
relatively constant. Due to this mostly constant speed, all data was plotted
against time, with major landmarks demarcated in terms of the time that they
were first encountered and then left.

Then, utilizing a common time scale as the basis for comparison, cell phone
data was plotted. The plot can be found in the cell-data directory of this
repository. It details the strength of the signal over time, and whether the
signal was UMTS or HSPA+ (the sampling device operated on the T-Mobile network,
so HSPA+ was the 4G data protocol).

WiFi data was also collected. It can all be found in the wifi-data directory of
this repository. 118 distinct broadcasters were detected along the sampling
path. When plotted against the common time scale, it becomes apparent where the
sampler was at any given time. For example, numerous printing devices are found
when the sampler is near the Mitte building, and again as he traverses near the
student center building and dorms. Then, the printing traffic dies off until
the sampler is once again near the dorms near the Rec Center. As the sampler 
approaches the parking lot, the signals again die off.

A good baseline wireless signal is the official WiFi provided by Texas State 
University, available on SSIDs "TexasStateUniversity" and "TexasStateWPA". Of
all the signals, these were the most available. Detailed examination of the
data reveals the nature of the WiFi deployment at Texas State: numerous "access
points," each with a unique BSSID, are found along the sampling path. Each AP
provides coverage for a certain area of campus, but they all report the same
SSID for consistency. A fun side note: one can see the WiFi aboard the Bobcat
Tram service briefly during the sampling as well, before the Tram drove out of
distance of the sampler.

Overall, the WiFi spectrum appeared quite congested. This congestion seemed
amplified by the presence of over 50 unidentified devices that were
broadcasting a BSSID, but did not provide an SSID. The uniqueness of the BSSID
and SSID both serve to underscore the reality that each of us carries with us
an imminently unique and trackable (yet invisible) heat score.
