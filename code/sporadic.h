#pragma once
#ifndef _SPORADIC_H
#define _SPORADIC_H
#ifdef __cplusplus
extern "C"
{ 
#endif

int sporadic_setup();
void calloc_sporadic_test(int sock);
void stack_initalized_sporadic_test(int sock);
void malloc_sporadic_test(int sock);
void stack_sporadic_test(int sock);


#ifdef __cplusplus
}
#endif
#endif