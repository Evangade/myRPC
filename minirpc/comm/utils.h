#ifndef MINIRPC_COMM_UTILS_H
#define MINIRPC_COMM_UTILS_H

#include <sys/types.h>
#include <unistd.h>

namespace minirpc
{

    pid_t getPid();

    pid_t getThreadId();

    int64_t getNowMs();

    int32_t getInt32FromNetByte(const char *buf);

}

#endif