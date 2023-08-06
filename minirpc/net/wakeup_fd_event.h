#ifndef MINIRPC_NET_WAKEUP_FDEVENT_H
#define MINIRPC_NET_WAKEUP_FDEVENT_H

#include "minirpc/net/fd_event.h"

namespace minirpc
{

    class WakeUpFdEvent : public FdEvent
    {
    public:
        WakeUpFdEvent(int fd);

        ~WakeUpFdEvent();

        void init();
        
        void wakeup();

    private:
    };

}

#endif