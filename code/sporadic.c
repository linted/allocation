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


void malloc_sporadic_test(int sock)
{
    uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
    recv(sock, (void *)t, 65445, MSG_DONTWAIT);
    free((void*)t);
}


void stack_sporadic_test(int sock)
{
    uint8_t volatile t[65445] = {0};
    recv(sock, (void*)t, 65445, MSG_DONTWAIT);
}