#pragma once
#ifndef _SPORADIC_H
#define _SPORADIC_H
#ifdef __cplusplus
extern "C"
{ 
#endif

int sporadic_setup();
ssize_t calloc_sporadic_test(int sock);
ssize_t stack_initalized_sporadic_test(int sock);
ssize_t malloc_sporadic_test(int sock);
ssize_t stack_sporadic_test(int sock);


#ifdef __cplusplus
}
#endif
#endif