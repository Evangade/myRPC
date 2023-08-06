#include "minirpc/net/io_thread_group.h"
#include "minirpc/comm/log.h"

namespace minirpc
{

    IOThreadGroup::IOThreadGroup(int size) : m_size(size)
    {
        m_io_thread_groups.resize(size);
        for (size_t i = 0; (int)i < size; ++i)
        {
            m_io_thread_groups[i] = new IOThread();
        }
    }

    IOThreadGroup::~IOThreadGroup()
    {
    }

    void IOThreadGroup::start()
    {
        for (size_t i = 0; i < m_io_thread_groups.size(); ++i)
        {
            m_io_thread_groups[i]->start();
        }
    }

    void IOThreadGroup::join()
    {
        for (size_t i = 0; i < m_io_thread_groups.size(); ++i)
        {
            m_io_thread_groups[i]->join();
        }
    }

    IOThread *IOThreadGroup::getIOThread() // 只在主线程调用，每调用一次，索引递增一次
    {
        if (m_index == (int)m_io_thread_groups.size() || m_index == -1)
        {
            m_index = 0;
        }
        return m_io_thread_groups[m_index++];
    }

}