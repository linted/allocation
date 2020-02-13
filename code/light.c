#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include "light.h"

void malloc_light_test()
{
    uint32_t volatile * t = (uint32_t *)calloc(65445, sizeof(uint32_t));
    if (t[100] == 51)
    {
        return;
    }
    t[100] = 51;
    free((void*)t);
}

void stack_light_test()
{
    uint32_t volatile t[65445] = {0};
    if (t[100] == 51)
    {
      return;
    }
    t[100] = 51;
}