#pragma once
#ifndef _SPORADIC_H
#define _SPORADIC_H
#ifdef __cplusplus
extern "C"
{
#endif

int network_setup();

ssize_t calloc_network_large_test(int sock);
ssize_t stack_initialized_network_large_test(int sock);
ssize_t malloc_network_large_test(int sock);
ssize_t stack_network_large_test(int sock);

ssize_t calloc_network_small_test(int sock);
ssize_t stack_initialized_network_small_test(int sock);
ssize_t malloc_network_small_test(int sock);
ssize_t stack_network_small_test(int sock);

#ifdef __cplusplus
}
#endif
#endif