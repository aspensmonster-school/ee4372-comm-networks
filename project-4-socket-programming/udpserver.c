/* a simple echo server using UDP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_UDP_PORT	5000
#define MAXLEN	4096

int main(int argc, char **argv)
{

int n, sd, client_len, port;
struct sockaddr_in server, client;
char buf[MAXLEN];

switch(argc) {
case 1:
	port = SERVER_UDP_PORT;
	break;
case 2:
	port = atoi(argv[1]);
	break;
default:
	fprintf(stderr, "Usage: %s [port]\n", argv[0]);
	exit(1);
}

/* Create a dgram socket */

if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
  fprintf(stderr, "Can't create a socket\n");
  exit(1);
}

/* Bind an address to the socket */

bzero((char *)&server, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
  fprintf(stderr, "Can't bind name to socket\n");
  exit(1);
}

/* Connect */

while(1) {
  client_len = sizeof(client);
  if ((n = recvfrom(sd, buf, MAXLEN, 0, (struct sockaddr *)&client, &client_len)) < 0) {
    fprintf(stderr, "Can't receive datagram\n");
    exit(1);
  }

  if (sendto(sd, buf, n, 0, (struct sockaddr *)&client, client_len) != n) {
    fprintf(stderr, "Can't send datagram\n");
    exit(1);
  }
}

/* Clean up and exit */

close(sd);
return(0);

}
