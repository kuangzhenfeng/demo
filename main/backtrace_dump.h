#ifndef __BACKTRACE_DUMP_H__
#define __BACKTRACE_DUMP_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>

static const int BACKTRACE_SIZE = 16;

void do_backtrace()
{
    void *array[BACKTRACE_SIZE];
    size_t size, i;
    char **strings;

    size = backtrace(array, BACKTRACE_SIZE);
    strings = backtrace_symbols(array, size);

    printf("---------------------------------------------------------\n");
    for (i = 0; i < size; ++i) {
        printf("%p : %s\n", array[i], strings[i]);
    }
    printf("---------------------------------------------------------\n");
    free(strings);
}

static void backtrace_dump()
{
#if 1
    printf("Dump map start...\n");
    char buff[64] = {0x00};
    snprintf(buff, sizeof(buff), "cat /proc/%d/maps", getpid());
    system((const char*) buff);
    printf("Dump map end...\n");
#endif

    printf("Dump stack start...\n");
    int j, nptrs;
    void *buffer[BACKTRACE_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BACKTRACE_SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        printf("  [%02d] %s\n", j, strings[j]);

    free(strings);
    printf("Dump stack end...\n");
}

static void signal_handler(int signo)
{
    printf("signo=%d, backtrace_dump\n", signo);
    backtrace_dump();
    signal(signo, SIG_DFL); /* 恢复信号默认处理 */
    raise(signo);           /* 重新发送信号 */
}

void backtrace_init()
{
    signal(SIGINT, signal_handler);
}

#endif