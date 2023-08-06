#ifndef MINIRPC_NET_EVENTLOOP_H
#define MINIRPC_NET_EVENTLOOP_H

#include <pthread.h>
#include <set>
#include <functional>
#include <queue>
#include "minirpc/comm/mutex.h"
#include "minirpc/net/timer_event.h"
namespace minirpc
{
    class EventLoop
    {
    public:
        EventLoop();

        ~EventLoop();

        void loop();

        void wakeup();

        void stop();

        void addTask(std::function<void()> cb, bool is_wake_up = false); // 添加任务队列

        void addTimerEvent(TimerEvent::s_ptr event); // 添加定时任务队列

        bool isLooping();

    public:
        static EventLoop *GetCurrentEventLoop();

        void addEpollEvent(class FdEvent *event);

        void deleteEpollEvent(class FdEvent *event);

        bool isInLoopThread();

    private:
        void dealWakeup();

        void initWakeUpFdEevent();

        void initTimer();

    private:
        pid_t m_thread_id{0};

        int m_epoll_fd{0};

        int m_wakeup_fd{0};

        class WakeUpFdEvent *m_wakeup_fd_event{NULL};

        bool m_stop_flag{false};

        std::set<int> m_listen_fds;

        std::queue<std::function<void()>> m_pending_tasks;
        Mutex m_mutex;

        bool m_is_looping{false};

        class Timer *m_timer{NULL};
    };
}
#endif