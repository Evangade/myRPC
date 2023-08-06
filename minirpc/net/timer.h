#ifndef MINIRPC_NET_TIMER_H
#define MINIRPC_NET_TIMER_H

#include <map>
#include "minirpc/comm/mutex.h"
#include "minirpc/net/fd_event.h"
#include "minirpc/net/timer_event.h"

namespace minirpc
{

    class Timer : public FdEvent
    {
    public:
        Timer();

        ~Timer();

        void addTimerEvent(TimerEvent::s_ptr event);

        void deleteTimerEvent(TimerEvent::s_ptr event);

        void onTimer(); // 当发送了 IO 事件后，eventloop 会执行这个回调函数

    private:
        void resetArriveTime();

    private:
        std::multimap<int64_t, TimerEvent::s_ptr> m_pending_events;
        Mutex m_mutex;
    };

}

#endif