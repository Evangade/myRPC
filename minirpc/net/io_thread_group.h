#ifndef MINIRPC_NET_IO_THREAD_GROUP_H
#define MINIRPC_NET_IO_THREAD_GROUP_H

#include <vector>
#include "minirpc/comm/log.h"
#include "minirpc/net/io_thread.h"

namespace minirpc
{

    class IOThreadGroup
    {

    public:
        IOThreadGroup(int size);

        ~IOThreadGroup();

        void start();

        void join();

        IOThread *getIOThread();

    private:
        int m_size{0};
        std::vector<IOThread *> m_io_thread_groups;

        int m_index{0};
    };

}

#endif