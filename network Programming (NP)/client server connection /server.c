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
  int listenfd, connfd;
  struct sockaddr_in serveraddr, clientaddr;
  char buff[MAX_LINE];
  time_t ticks;
  socklen_t len;
  int port;

  listenfd = socket(AF_INET, SOCK_STREAM,0);
  port = atoi(argv[1]);
  bzero(&serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(port);

  bind(listenfd, (SA*) &serveraddr, sizeof(serveraddr));
  printf("Server is waiting connection at port %d\n", port);
  listen(listenfd, LISTENQ);

  while(1) {
    len = sizeof(clientaddr);
    connfd = accept(listenfd, (SA*) &clientaddr, &len);
    printf("Connection from %s, port %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)), ntohs(clientaddr.sin_port));
    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    write(connfd, buff, strlen(buff));
    close(connfd);
  }
}
    
