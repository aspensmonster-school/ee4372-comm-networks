#include <stdio.h> /* printf(), fprintf(), perror() */
#include <sys/socket.h> /* socket(), connect(), send(), recv() */
#include <arpa/inet.h> /* sockaddr_in, inet_addr() */
#include <stdlib.h> /* atoi(), exit() */
#include <string.h> /* memset() */
#include <unistd.h> /* close() */

#define rcvBufSize 32

void DieWithError(char *errorMessage) {
  perror(errorMessage);
  exit(1);
}

int main(int argc, char *argv[]) {

  int sock; /* socket descriptor */
  struct sockaddr_in serverAddress; /*server address */
  unsigned short serverPort; /* server port */
  char *serverIP; /*server IP address */
  char *echoString; /* string that will be sent to server */
  char echoStringBuffer[rcvBufSize]; /* buffer for the string */
  unsigned int echoStringLength; /* length of string */
  int bytesReceived, totalBytesReceived; /* bytes in a single read(), and
                                            total bytes received */

  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
      argv[0]);
    exit(1);
  }

  serverIP = argv[1];
  echoString = argv[2];

  /* Use port if supplied */
  if (argc == 4) {
    serverPort = atoi(argv[3]);
  }
  else {
    serverPort = 7;
  }

  /* create stream socket */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    DieWithError("socket() failed.");
  }

  /* Fill out the serverAddress struct */ 
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr(serverIP);
  serverAddress.sin_port = htons(serverPort);

  /* Establish connection to server*/
  if (connect(sock, (struct sockaddr *) &serverAddress,
     sizeof(serverAddress)) < 0) {
    DieWithError("connect() failed.");
  }

  /* get length of input */
  echoStringLength = strlen(echoString);

  /* Send string to server */
  if (send(sock, echoString, echoStringLength, 0) != echoStringLength) {
    DieWithError("send() sent unexpected length of data");
  }

  /* Get response from server */
  totalBytesReceived = 0;
  printf("Received: ");
  while (totalBytesReceived < echoStringLength) {
    if ((bytesReceived = recv(sock, echoStringBuffer, 
    rcvBufSize - 1, 0)) <= 0) {
      DieWithError("recv() failed or connection closed prematurely");
    }
    totalBytesReceived += bytesReceived;
    echoStringBuffer[bytesReceived] = '\0';
    printf(echoStringBuffer);
  }

  printf("\n");
  close(sock);
  exit(0);

}
