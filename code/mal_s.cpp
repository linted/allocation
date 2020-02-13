#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <benchmark/benchmark.h>

void do_malloc(int sock)
{
  uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
  recv(sock, (void *)t, 65445, MSG_DONTWAIT);
  free((void*)t);
}

void  do_test(benchmark::State& state)
{
  // setup
  struct sockaddr_in host = { 0 };
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

  for (auto _ : state)
  {
    // code that is timed
    do_malloc(sock);
  }

  // cleanup
  close(sock);

}


// Register the function as a benchmark
BENCHMARK(do_test);
// Run the benchmark
BENCHMARK_MAIN();