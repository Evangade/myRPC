#ifndef MINIRPC_NET_FD_EVENT_GROUP_H
#define MINIRPC_NET_FD_EVENT_GROUP_H

#include <vector>
#include <mutex>
#include "minirpc/comm/mutex.h"
#include "minirpc/net/fd_event.h"

namespace minirpc
{

    class FdEventGroup
    {

    public:
        FdEventGroup(int size);

        ~FdEventGroup();
        FdEvent *getFdEvent(int fd); // 获取关联的FdEvent

    public:
        static FdEventGroup *GetFdEventGroup();

    private:
        int m_size{0};
        std::vector<FdEvent *> m_fd_group;
        std::mutex m_mut;
    };

}

#endif