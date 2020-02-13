#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include "light.h"

void malloc_light_test()
{
    uint8_t volatile * t = (uint8_t *)malloc(65445 * sizeof(uint8_t));
    t[100] = 51;
    free((void*)t);
}

void stack_light_test()
{
    uint8_t volatile t[65445];
    t[100] = 51;
}

void calloc_light_test()
{
    uint8_t volatile * t = (uint8_t *)calloc(65445, sizeof(uint8_t));
    t[100] = 51;
    free((void*)t);
}

void stack_initialized_light_test()
{
    uint8_t volatile t[65445] = {0};
    t[100] = 51;
}