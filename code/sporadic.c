#define _GNU_SOURCE
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <sporadic.h>
#include <buffer_sizes.h>

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

MALLOC_NETWORK_TEST(malloc_network_huge_test, HUGE_BUFFER_SIZE);
STACK_NETWORK_TEST(stack_network_huge_test, HUGE_BUFFER_SIZE);
CALLOCK_NETWORK_TEST(calloc_network_huge_test, HUGE_BUFFER_SIZE);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_huge_test, HUGE_BUFFER_SIZE);

MALLOC_NETWORK_TEST(malloc_network_large_test, LARGE_BUFFER_SIZE);
STACK_NETWORK_TEST(stack_network_large_test, LARGE_BUFFER_SIZE);
CALLOCK_NETWORK_TEST(calloc_network_large_test, LARGE_BUFFER_SIZE);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_large_test, LARGE_BUFFER_SIZE);

MALLOC_NETWORK_TEST(malloc_network_medium_test, MEDIUM_BUFFER_SIZE);
STACK_NETWORK_TEST(stack_network_medium_test, MEDIUM_BUFFER_SIZE);
CALLOCK_NETWORK_TEST(calloc_network_medium_test, MEDIUM_BUFFER_SIZE);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_medium_test, MEDIUM_BUFFER_SIZE);

MALLOC_NETWORK_TEST(malloc_network_small_test, SMALL_BUFFER_SIZE);
STACK_NETWORK_TEST(stack_network_small_test, SMALL_BUFFER_SIZE);
CALLOCK_NETWORK_TEST(calloc_network_small_test, SMALL_BUFFER_SIZE);
STACK_INITIALIZED_NETWORK_TEST(stack_initialized_network_small_test, SMALL_BUFFER_SIZE);

// Sort tests *************************************************

// #ifndef INPUT_FILE
// #define INPUT_FILE "/usr/share/dict/words"
// #endif

// int sort_test_compare(const void * ptr1, const void * ptr2)
// {
// #ifdef SORT_REVERSED
//     return strcmp(ptr2, ptr1);
// #else
//     return strcmp(ptr1, ptr2);
// #endif
// }

// #define SORT_TEST_ALLOCATE(START, TOTAL, ALLOCATOR) \
//     size_t SORT_current_total = TOTAL;
//     while()
//     void * end = memmem(start, total, "\n", 1);

// #define MALLOC_SORT_TEST(NAME, SIZE)                   \
//     ssize_t NAME(void *data)                           \
//     {                                                  \
//         ssize_t byteCount = 0;                         \
//         uint8_t volatile *t = (uint8_t *)malloc(SIZE); \
//                                                        \
//         free((void *)t);                               \
//         return byteCount;                              \
//     }

// #define STACK_SORT_TEST(NAME, SIZE) \
//     ssize_t NAME(void *data)        \
//     {                               \
//         ssize_t byteCount = 0;      \
//         uint8_t volatile t[SIZE];   \
//                                     \
//         return byteCount;           \
//     }

// #define CALLOCK_SORT_TEST(NAME, SIZE)                                   \
//     ssize_t NAME(void *data)                                            \
//     {                                                                   \
//         ssize_t byteCount = 0;                                          \
//         uint8_t volatile *t = (uint8_t *)calloc(SIZE, sizeof(uint8_t)); \
//                                                                         \
//         free((void *)t);                                                \
//         return byteCount;                                               \
//     }

// #define STACK_INITIALIZED_SORT_TEST(NAME, SIZE) \
//     ssize_t NAME(void *data)                    \
//     {                                           \
//         ssize_t byteCount = 0;                  \
//         uint8_t volatile t[SIZE] = {0};         \
//                                                 \
//         return byteCount;                       \
//     }

// int setup_sort(void **addr, size_t *len)
// {
//     struct stat stats = {0};
//     int fd = open(INPUT_FILE, O_RDONLY);

//     fstat(fd, &stats);
//     *addr = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
//     close(fd);

//     return *addr == -1;
// }

// void cleanup_sort(void *addr, size_t len)
// {
//     munmap(addr, len);
//     return;
// }