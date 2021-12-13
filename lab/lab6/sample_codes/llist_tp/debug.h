#ifndef _DEBUG_H
#define _DEBUG_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define LOGE(M, ...) fprintf(stderr, "\033[31;1m[ERROR]\033[0m (%s:%d: errno: %d) " M "\n", __FILE__, __LINE__, errno, ##__VA_ARGS__)
#define LOGI(M, ...) fprintf(stderr, "\033[32;1m[INFO]\033[0m (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(exp, M, ...) \
        if(!(exp)) { LOGE(M, ##__VA_ARGS__); errno=0; goto error; }

#endif