#pragma once
#ifndef _LIGHT_H
#define _LIGHT_H
#ifdef __cplusplus
extern "C"
{ 
#endif

// Exta Large buffer tests
void malloc_light_huge_test();
void stack_light_huge_test();
void calloc_light_huge_test();
void stack_initialized_light_huge_test();

// Large buffer tests
void malloc_light_large_test();
void stack_light_large_test();
void calloc_light_large_test();
void stack_initialized_light_large_test();

// Medium buffer tests
void malloc_light_medium_test();
void stack_light_medium_test();
void calloc_light_medium_test();
void stack_initialized_light_medium_test();

// Small buffer tests
void malloc_light_small_test();
void stack_light_small_test();
void calloc_light_small_test();
void stack_initialized_light_small_test();

// Struct tests
void malloc_struct_test();
void stack_struct_test();
void calloc_struct_test();
void stack_initialized_struct_test();

// multi allocation tests
void malloc_multi_test();
void stack_multi_test();
void calloc_multi_test();
void stack_initialized_multi_test();

#ifdef __cplusplus
}
#endif
#endif