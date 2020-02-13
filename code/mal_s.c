#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


int volatile keep_going = 1;
int sock = -1;

void signalHandler(int sig)
{
  keep_going = 0;
}

void do_malloc(uint64_t * c)
{
  uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
  if (0 < recv(sock, t, 65445, MSG_DONTWAIT))
      (*c)++;
  free(t);
//  printf("Here\n");
}

int main()
{
  struct sigaction sigactionStruct = {
        .sa_handler = signalHandler,
  };

  sigaction(SIGINT, &sigactionStruct, NULL);

  struct sockaddr_in host = {
    .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
    .sin_family = AF_INET,
    .sin_port = htons(4000),
  };

  sock = socket(AF_INET, SOCK_STREAM, 0);

  connect(sock, (struct sockaddr *)&host, sizeof(struct sockaddr_in));


  uint64_t count = 0;
  while(keep_going)
  {
    do_malloc(&count);
    if(count == UINT64_MAX)
    {
      break;
    }
  }

  printf("%lu\n",count);
  return 0;
}
