#pragma once
#ifndef _LIGHT_H
#define _LIGHT_H
#ifdef __cplusplus
extern "C"
{ 
#endif

void malloc_light_large_test();
void stack_light_large_test();
void calloc_light_large_test();
void stack_initialized_light_large_test();
void malloc_light_small_test();
void stack_light_small_test();
void calloc_light_small_test();
void stack_initialized_light_small_test();

#ifdef __cplusplus
}
#endif
#endif