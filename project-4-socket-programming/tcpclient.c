/* a simple echo client using TCP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_TCP_PORT	3000
#define BUFLEN	256

int main(int argc, char **argv)
{

 int n, bytes_to_read;
 int sd, port;
 struct hostent *hp;
 struct sockaddr_in server;
 char *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];

 switch(argc) {
 case 2:
	host = argv[1];
	port = SERVER_TCP_PORT;
	break;
 case 3:
	host = argv[1];
	port = atoi(argv[2]);
	break;
 default:
	fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
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
 if ((hp = gethostbyname(host)) == NULL) {
   fprintf(stderr, "Can't get server address\n");
   exit(1);
 }
 bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

 /* Connect to server */

 if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
   fprintf(stderr, "Can't connect to server\n");
   exit(1);
 }

 printf("Connected: server address is %s\n", (char *)inet_ntoa(server.sin_addr));

 /* Transmit */

 printf("Getting data to send to server ...\n");
 printf(".. enter some data: ");
 fgets(sbuf,BUFLEN-1,stdin);
 printf(".. got %d bytes from user (incl newline)\n",strlen(sbuf));
 printf(".. hit <CR> to send %d bytes to server (wo newline)",strlen(sbuf)-1);
 fgetc(stdin);
 n = write(sd, sbuf, strlen(sbuf)-1);
 if (n<0) error("ERROR writing to socket");
 printf(".. sent %d bytes\n",n);

 /* Receive */

//bp = rbuf;
//bytes_to_read = BUFLEN;
//while((n = read(sd, bp, bytes_to_read)) > 0) {
//  bp += n;
//  bytes_to_read -=n;
//}

 printf("Receiving data from server ...\n");

 bzero(rbuf,BUFLEN);
 n = read(sd, rbuf, BUFLEN-1);
 if (n<0) error("ERROR reading from socket");

 printf(".. received [%s] (%d bytes)\n", rbuf,strlen(rbuf));

 /* Clean up and exit */

 close(sd);
 return(0);
}
