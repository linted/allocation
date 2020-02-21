#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include "sporadic.h"


int sporadic_setup()
{

  struct sockaddr_in host = {
    .sin_family = AF_INET,
    .sin_port = htons(4000),
    .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
  };

  int sock = -1;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(0 > sock)
  {
    perror("");
    return -1;
  }

  if (0 != connect(sock, (struct sockaddr *)&host, sizeof(struct sockaddr_in)))
  {
    perror("");
    close(sock);
    return -1;
  }

  return sock;
}


ssize_t malloc_sporadic_test(int sock)
{
    ssize_t byteCount = 0;
    uint8_t volatile * t = (uint8_t *)malloc(65445);
    byteCount = recv(sock, (void *)t, 65445, MSG_DONTWAIT);
    free((void*)t);
    return byteCount;
}


ssize_t stack_sporadic_test(int sock)
{
    ssize_t byteCount = 0;
    uint8_t volatile t[65445];
    byteCount = recv(sock, (void*)t, 65445, MSG_DONTWAIT);
    return byteCount;
}

ssize_t calloc_sporadic_test(int sock)
{
    ssize_t byteCount = 0;
    uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
    byteCount = recv(sock, (void *)t, 65445, MSG_DONTWAIT);
    free((void*)t);
    return byteCount;
}

ssize_t stack_initalized_sporadic_test(int sock)
{
    ssize_t byteCount = 0;
    uint8_t volatile t[65445] = {0};
    byteCount = recv(sock, (void*)t, 65445, MSG_DONTWAIT);
    return byteCount;
}