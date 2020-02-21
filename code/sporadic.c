#include <netinet/in.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sporadic.h"

#define LARGE_BUFFER 65445
#define SMALL_BUFFER 1024

int network_setup()
{
    struct sockaddr_in host = {
        .sin_family = AF_INET,
        .sin_port = htons(4000),
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
    };

    int sock = -1;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sock)
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

// Network tests *************************************************
#ifdef DONT_WAIT
#define RECV_FLAGS MSG_DONTWAIT
#else
#define RECV_FLAGS 0
#endif

#define MALLOC_NETWORK_TEST(NAME, SIZE)                      \
    ssize_t NAME(int sock)                                   \
    {                                                        \
        ssize_t byteCount = 0;                               \
        uint8_t volatile *t = (uint8_t *)malloc(SIZE);       \
        byteCount = recv(sock, (void *)t, SIZE, RECV_FLAGS); \
        free((void *)t);                                     \
        return byteCount;                                    \
    }

#define STACK_NETWORK_TEST(NAME, SIZE)                       \
    ssize_t NAME(int sock)                                   \
    {                                                        \
        ssize_t byteCount = 0;                               \
        uint8_t volatile t[SIZE];                            \
        byteCount = recv(sock, (void *)t, SIZE, RECV_FLAGS); \
        return byteCount;                                    \
    }

#define CALLOCK_NETWORK_TEST(NAME, SIZE)                                \
    ssize_t NAME(int sock)                                              \
    {                                                                   \
        ssize_t byteCount = 0;                                          \
        uint8_t volatile *t = (uint8_t *)calloc(SIZE, sizeof(uint8_t)); \
        byteCount = recv(sock, (void *)t, SIZE, RECV_FLAGS);            \
        free((void *)t);                                                \
        return byteCount;                                               \
    }

#define STACK_INITIALIZED_NETWORK_TEST(NAME, SIZE)           \
    ssize_t NAME(int sock)                                   \
    {                                                        \
        ssize_t byteCount = 0;                               \
        uint8_t volatile t[SIZE] = {0};                      \
        byteCount = recv(sock, (void *)t, SIZE, RECV_FLAGS); \
        return byteCount;                                    \
    }

MALLOC_NETWORK_TEST(malloc_network_large_test, LARGE_BUFFER);
STACK_NETWORK_TEST(stack_network_large_test, LARGE_BUFFER);
CALLOCK_NETWORK_TEST(calloc_network_large_test, LARGE_BUFFER);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_large_test, LARGE_BUFFER);

MALLOC_NETWORK_TEST(malloc_network_small_test, SMALL_BUFFER);
STACK_NETWORK_TEST(stack_network_small_test, SMALL_BUFFER);
CALLOCK_NETWORK_TEST(calloc_network_small_test, SMALL_BUFFER);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_small_test, SMALL_BUFFER);
