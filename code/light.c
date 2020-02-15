#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <netinet/in.h>
#include "light.h"

#define LARGE_BUFFER_SIZE 65445
#define SMALL_BUFFER_SIZE 64
// #define STRUCT_TYPE struct sockaddr_in

void __attribute__((optimize("O0"))) do_nothing(volatile void * buff )
{
    // This function is used to trick the compiler into thinking that the buffer
    // is being used by something else in a way it doesn't understand.
    // This forces the compiler to not optimize code dealing with the buffer
    return;
}

// LARGE tests *********************************************************************

void malloc_light_large_test()
{
    uint8_t volatile * t = (uint8_t *)malloc(LARGE_BUFFER_SIZE * sizeof(uint8_t));
    do_nothing(t);
    t[LARGE_BUFFER_SIZE-1] = (uint8_t)51;
    free((void*)t);
}

void stack_light_large_test()
{
    uint8_t volatile t[LARGE_BUFFER_SIZE];
    do_nothing(t);
    t[LARGE_BUFFER_SIZE-1] = (uint8_t)51;
}

void calloc_light_large_test()
{
    uint8_t volatile * t = (uint8_t *)calloc(LARGE_BUFFER_SIZE, sizeof(uint8_t));
    do_nothing(t);
    t[LARGE_BUFFER_SIZE-1] = (uint8_t)51;
    free((void*)t);
}

void stack_initialized_light_large_test()
{
    uint8_t volatile t[LARGE_BUFFER_SIZE] = {0};
    do_nothing(t);
    t[LARGE_BUFFER_SIZE-1] = (uint8_t)51;
}

// SMALL tests *********************************************************************

void malloc_light_small_test()
{
    uint8_t volatile * t = (uint8_t *)malloc(SMALL_BUFFER_SIZE * sizeof(uint8_t));
    do_nothing(t);
    t[SMALL_BUFFER_SIZE-1] = (uint8_t)51;
    free((void*)t);
}

void stack_light_small_test()
{
    uint8_t volatile t[SMALL_BUFFER_SIZE];
    do_nothing(t);
    t[SMALL_BUFFER_SIZE-1] = (uint8_t)51;
}

void calloc_light_small_test()
{
    uint8_t volatile * t = (uint8_t *)calloc(SMALL_BUFFER_SIZE, sizeof(uint8_t));
    do_nothing(t);
    t[SMALL_BUFFER_SIZE-1] = (uint8_t)51;
    free((void*)t);
}

void stack_initialized_light_small_test()
{
    uint8_t volatile t[SMALL_BUFFER_SIZE] = {0};
    do_nothing(t);
    t[SMALL_BUFFER_SIZE-1] = (uint8_t)51;
}

// struct tests *********************************************************************

void malloc_struct_test()
{
    struct sockaddr_in volatile * t = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    t->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t->sin_port = htons(5555);
    t->sin_family = AF_INET;
    memset((void*)(t->sin_zero), 0, sizeof(t->sin_zero));
    do_nothing((void*)t);
    free((void*)t);
}

void stack_struct_test()
{
    struct sockaddr_in volatile t;
    t.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t.sin_port = htons(5555);
    t.sin_family = AF_INET;
    memset((void*)(t.sin_zero), 0, sizeof(t.sin_zero));
    do_nothing((void*)&t);
}

void calloc_struct_test()
{
    struct sockaddr_in volatile * t = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in));
    t->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    t->sin_port = htons(5555);
    t->sin_family = AF_INET;
    do_nothing((void*)t);
    free((void*)t);
}

void stack_initialized_struct_test()
{
    struct sockaddr_in volatile t = {
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
        .sin_port = htons(5555),
        .sin_family = AF_INET,
    };
    do_nothing((void*)&t);
}