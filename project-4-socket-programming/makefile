# compiler variables
CC = gcc
#SEARCHDIR = -I.
#CFLAGS = -O2 -Wall $(SEARCHDIR)
CFLAGS = 
CSETUP = echo "  Compiling: " $*

# compile command
%.o : %.c
	$(CSETUP) ; $(CC) $(CFLAGS) -c -o $@ $<

# linker dependencies
udpclient : udpclient.o
udpserver : udpserver.o
tcpclient : tcpclient.o
tcpserver : tcpserver.o

# everything
all : udpclient udpserver tcpclient tcpserver

# cleanup
clean : 
	- rm -f *.o
