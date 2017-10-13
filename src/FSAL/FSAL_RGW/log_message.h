#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

#define LOG_MESSAGE(format, ...)                                                                \
    do {                                                                                        \
        FILE* ffff = fopen("/tmp/debug.log", "a");                                              \
        if (ffff == NULL) {                                                                     \
            break;                                                                              \
        }                                                                                       \
        struct timeval tv = {0};                                                                \
        struct tm tm = {0};                                                                     \
        gettimeofday(&tv, NULL);                                                                \
        localtime_r(&(tv.tv_sec), &tm);                                                         \
        fprintf(ffff, "[%d-%02d-%02d %02d:%02d:%02d.%03d][%d:%d][%s:%d] " format,               \
                1900 + tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, \
                (int)(tv.tv_usec / 1000),                                                       \
                (int)(getpid()), (int)(syscall(SYS_gettid)),                                    \
                __FILE__, __LINE__,                                                             \
                ##__VA_ARGS__);                                                                 \
        fclose(ffff);                                                                           \
    } while (false)

#endif // LOG_MESSAGE_H
