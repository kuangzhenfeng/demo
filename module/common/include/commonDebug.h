#ifndef __COMMON_DEBUG_H__
#define __COMMON_DEBUG_H__

#include <stdio.h>

#define DEBUG(fmt, ...) do {printf("\e[1;32m" "[DEBUG]<%s>(%d): " fmt "\e[0m\n", __FUNCTION__,  __LINE__, ##__VA_ARGS__); fflush(stdout);} while(0)
#define DEBUG_PERROR(fmt, ...) do {printf("\e[1;32m" "[DEBUG_PERROR]<%s>(%d): " fmt "\e[0m\n", __FUNCTION__,  __LINE__, ##__VA_ARGS__); perror("perror"); fflush(stdout);} while(0)

#endif