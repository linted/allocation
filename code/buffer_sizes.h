#pragma once
#ifndef _BUFFER_SIZES_H
#define _BUFFER_SIZES_H
#ifdef __cplusplus
extern "C"
{ 
#endif

#define GIANT_BUFFER_SIZE 65536     // 2^16
#define HUGE_BUFFER_SIZE 32768      // 2^15
#define LARGE_BUFFER_SIZE 4096      // 2^12
#define MEDIUM_BUFFER_SIZE 256      // 2^8
#define SMALL_BUFFER_SIZE 32        // 2^5
#define MINI_BUFFER_SIZE 16         // 2^4

#ifdef __cplusplus
}
#endif
#endif