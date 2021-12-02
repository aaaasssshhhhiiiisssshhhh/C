#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE 1024
#define LISTENQ 10

typedef struct sockaddr SA;

int main(int argc, char** argv) {
  int sockfd, n;
  char recvline[MAX_LINE+1];
  struct sockaddr_in serveraddr;
  int port;

  if(argc != 3) printf("usage: ./<program name> <ipaddress> <port>");
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) printf("socket error");

  port = atoi(argv[2]);
  bzero(&serveraddr, sizeof(serveraddr));

  
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port);

  if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0) printf("inet_pton error for %s\n", argv[1]);

  if (connect(sockfd, (SA*) &serveraddr, sizeof(serveraddr))) printf("connect error\n");

  while((n=read(sockfd, recvline, MAX_LINE)) > 0) {
    recvline[n] = 0;
    printf("Server Time: ");
    if (fputs(recvline, stdout) == EOF) printf("Read Error\n");
  }
  if (n < 0) printf("read error");
  exit(0);
}
    
