#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>

int volatile keep_going = 1;

void signalHandler(int sig)
{
  keep_going = 0;
}

void do_malloc(uint64_t * c)
{
  uint32_t volatile * t = (uint32_t *)calloc(65445, sizeof(uint32_t));
  if (t[100] == 51)
    exit(1);
  //for(size_t i = 0; i < 65445; i++)
  t[100] = 51;
  (*c)++;
  free(t);
//  printf("Here\n");
}

int main()
{
  struct sigaction sigactionStruct = {
        .sa_handler = signalHandler,
  };
  sigset_t signals = {0};

  sigaction(SIGINT, &sigactionStruct, NULL);

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
