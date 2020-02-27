#include "light.h"
#include <netinet/in.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <light.h>
#include <buffer_sizes.h>

// #define STRUCT_TYPE struct sockaddr_in

void __attribute__((optimize("O0"))) do_nothing(volatile void *buff)
{
    // This function is used to trick the compiler into thinking that the buffer
    // is being used by something else in a way it doesn't understand.
    // This forces the compiler to not optimize code dealing with the buffer
    return;
}

// Light tests *********************************************************************

#define LIGHT_MALLOC_TEST(NAME, SIZE)                                    \
    void NAME()                                                          \
    {                                                                    \
        uint8_t volatile *t = (uint8_t *)malloc(SIZE * sizeof(uint8_t)); \
        do_nothing(t);                                                   \
        t[SIZE - 1] = (uint8_t)51;                                       \
        free((void *)t);                                                 \
    }

#define LIGHT_STACK_TEST(NAME, SIZE) \
    void NAME()                      \
    {                                \
        uint8_t volatile t[SIZE];    \
        do_nothing(t);               \
        t[SIZE - 1] = (uint8_t)51;   \
    }

#define LIGHT_CALLOC_TEST(NAME, SIZE)                                   \
    void NAME()                                                         \
    {                                                                   \
        uint8_t volatile *t = (uint8_t *)calloc(SIZE, sizeof(uint8_t)); \
        do_nothing(t);                                                  \
        t[SIZE - 1] = (uint8_t)51;                                      \
        free((void *)t);                                                \
    }

#define LIGHT_STACK_INITIALIZED_TEST(NAME, SIZE) \
    void NAME()                                  \
    {                                            \
        uint8_t volatile t[SIZE] = {0};          \
        do_nothing(t);                           \
        t[SIZE - 1] = (uint8_t)51;               \
    }

// Light extra large tests *********************************************************************
LIGHT_MALLOC_TEST(malloc_light_huge_test, HUGE_BUFFER_SIZE)
LIGHT_STACK_TEST(stack_light_huge_test, HUGE_BUFFER_SIZE)
LIGHT_CALLOC_TEST(calloc_light_huge_test, HUGE_BUFFER_SIZE)
LIGHT_STACK_INITIALIZED_TEST(stack_initialized_light_huge_test, HUGE_BUFFER_SIZE)
// Light large tests *********************************************************************
LIGHT_MALLOC_TEST(malloc_light_large_test, LARGE_BUFFER_SIZE)
LIGHT_STACK_TEST(stack_light_large_test, LARGE_BUFFER_SIZE)
LIGHT_CALLOC_TEST(calloc_light_large_test, LARGE_BUFFER_SIZE)
LIGHT_STACK_INITIALIZED_TEST(stack_initialized_light_large_test, LARGE_BUFFER_SIZE)
// Light medium tests *********************************************************************
LIGHT_MALLOC_TEST(malloc_light_medium_test, MEDIUM_BUFFER_SIZE)
LIGHT_STACK_TEST(stack_light_medium_test, MEDIUM_BUFFER_SIZE)
LIGHT_CALLOC_TEST(calloc_light_medium_test, MEDIUM_BUFFER_SIZE)
LIGHT_STACK_INITIALIZED_TEST(stack_initialized_light_medium_test, MEDIUM_BUFFER_SIZE)
// Light small tests *********************************************************************
LIGHT_MALLOC_TEST(malloc_light_small_test, SMALL_BUFFER_SIZE)
LIGHT_STACK_TEST(stack_light_small_test, SMALL_BUFFER_SIZE)
LIGHT_CALLOC_TEST(calloc_light_small_test, SMALL_BUFFER_SIZE)
LIGHT_STACK_INITIALIZED_TEST(stack_initialized_light_small_test, SMALL_BUFFER_SIZE)

// struct tests *********************************************************************

void malloc_struct_test()
{
    struct sockaddr_in volatile *t = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    t->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t->sin_port = htons(5555);
    t->sin_family = AF_INET;
    memset((void *)(t->sin_zero), 0, sizeof(t->sin_zero));
    do_nothing((void *)t);
    free((void *)t);
}

void stack_struct_test()
{
    struct sockaddr_in volatile t;
    t.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t.sin_port = htons(5555);
    t.sin_family = AF_INET;
    memset((void *)(t.sin_zero), 0, sizeof(t.sin_zero));
    do_nothing((void *)&t);
}

void calloc_struct_test()
{
    struct sockaddr_in volatile *t = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in));
    t->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t->sin_port = htons(5555);
    t->sin_family = AF_INET;
    do_nothing((void *)t);
    free((void *)t);
}

void stack_initialized_struct_test()
{
    struct sockaddr_in volatile t = {
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
        .sin_port = htons(5555),
        .sin_family = AF_INET,
    };
    do_nothing((void *)&t);
}

// multi allocations *************************************************

void malloc_multi_test()
{
    uint8_t volatile *t1 = (uint8_t *)malloc(SMALL_BUFFER_SIZE);
    uint8_t volatile *t2 = (uint8_t *)malloc(SMALL_BUFFER_SIZE);
    uint8_t volatile *t3 = (uint8_t *)malloc(SMALL_BUFFER_SIZE);
    do_nothing(t1);
    do_nothing(t2);
    do_nothing(t3);
    t1[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t2[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t3[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    free((void *)t1);
    free((void *)t2);
    free((void *)t3);
}

void stack_multi_test()
{
    uint8_t volatile t1[SMALL_BUFFER_SIZE];
    uint8_t volatile t2[SMALL_BUFFER_SIZE];
    uint8_t volatile t3[SMALL_BUFFER_SIZE];
    do_nothing(t1);
    do_nothing(t2);
    do_nothing(t3);
    t1[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t2[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t3[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
}

void calloc_multi_test()
{
    uint8_t volatile *t1 = (uint8_t *)calloc(SMALL_BUFFER_SIZE, sizeof(uint8_t));
    uint8_t volatile *t2 = (uint8_t *)calloc(SMALL_BUFFER_SIZE, sizeof(uint8_t));
    uint8_t volatile *t3 = (uint8_t *)calloc(SMALL_BUFFER_SIZE, sizeof(uint8_t));
    do_nothing(t1);
    do_nothing(t2);
    do_nothing(t3);
    t1[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t2[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t3[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    free((void *)t1);
    free((void *)t2);
    free((void *)t3);
}

void stack_initialized_multi_test()
{
    uint8_t volatile t1[SMALL_BUFFER_SIZE] = {0};
    uint8_t volatile t2[SMALL_BUFFER_SIZE] = {0};
    uint8_t volatile t3[SMALL_BUFFER_SIZE] = {0};
    do_nothing(t1);
    do_nothing(t2);
    do_nothing(t3);
    t1[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t2[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
    t3[SMALL_BUFFER_SIZE - 1] = (uint8_t)51;
}