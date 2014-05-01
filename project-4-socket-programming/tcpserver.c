/* a simple echo server using TCP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_TCP_PORT	3000
#define BUFLEN	256

int main(int argc, char **argv)
{

int n, bytes_to_read;
int sd, new_sd, client_len, port;
struct sockaddr_in server, client;
char *bp, buf[BUFLEN], tbuf[BUFLEN]="hello";

switch(argc) {
case 1:
	port = SERVER_TCP_PORT;
	break;
case 2:
	port = atoi(argv[1]);
	break;
default:
	fprintf(stderr, "Usage: %s [port]\n", argv[0]);
	exit(1);
}

/* Create a stream socket */

if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
  fprintf(stderr, "Can't create a socket\n");
  exit(1);
}

/* Bind an address to the socket */

bzero((char *)&server, sizeof(struct sockaddr_in));
server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
  fprintf(stderr, "Can't bind name to socket\n");
  exit(1);
}

/* Queue connect requests */

listen(sd,5);

while(1) {
  client_len = sizeof(client);
  if ((new_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1) {
    fprintf(stderr, "Can't accept client\n");
    exit(1);
  }

  printf("Got connection from client: %s\n", (char *)inet_ntoa(client.sin_addr));

  //  bp = buf;
  //  bytes_to_read = BUFLEN;
  //  while((n = read(new_sd, bp, bytes_to_read)) > 0) {
  //    bp += n;
  //    bytes_to_read -=n;
  //  }

  printf("Reading data from socket ...\n");
  bzero(buf,BUFLEN);
  n = read(new_sd,buf,BUFLEN-1);
  if (n<0) error("ERROR reading from socket");

  printf(".. received [%s] (%d bytes) from client\n", buf,strlen(buf));

  printf("Sending data to client ...\n");
  printf(".. hit <CR> to send [%s] (%d bytes) to client",buf,strlen(buf));
  fgetc(stdin);
  n = write(new_sd, buf, strlen(buf));
  if (n<0) error("ERROR writing to socket");
  printf(".. sent %d bytes\n",n);
  close(new_sd);
}

/* Clean up and exit */

close(sd);
return(0);

}
