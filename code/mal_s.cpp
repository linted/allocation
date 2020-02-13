#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <benchmark/benchmark.h>

int setup()
{

  struct sockaddr_in host;
  host.sin_family = AF_INET;
  host.sin_port = htons(4000);
  host.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int sock = -1;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(0 > sock)
  {
    std::cout << "Unable to retreive socket" << std::endl;
    return;
  }

  if (0 != connect(sock, (struct sockaddr *)&host, sizeof(struct sockaddr_in)))
  {
    perror("");
    std::cout << "Unable to connect to server" << std::endl;
    close(sock);
    return;
  }

  return sock;
}


void  do_stack(benchmark::State& state)
{
  // setup
  int sock = setup();
  for (auto _ : state)
  {
    // code that is timed
    uint8_t volatile t[65445] = {0};
    recv(sock, (void*)t, 65445, MSG_DONTWAIT);
  }

  // cleanup
  close(sock);
}

void  do_malloc(benchmark::State& state)
{
  // setup
  int sock = setup();
  for (auto _ : state)
  {
    // code that is timed
    uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
    recv(sock, (void *)t, 65445, MSG_DONTWAIT);
    free((void*)t);
  }

  // cleanup
  close(sock);

}

// Register the function as a benchmark
BENCHMARK(do_stack);
// Register the function as a benchmark
BENCHMARK(do_malloc);
// Run the benchmark
BENCHMARK_MAIN();