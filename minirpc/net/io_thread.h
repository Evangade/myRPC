#ifndef MINIRPC_NET_IO_THREAD_H
#define MINIRPC_NET_IO_THREAD_H

#include <pthread.h>
#include <semaphore.h>

namespace minirpc
{

    class IOThread
    {
    public:
        IOThread();

        ~IOThread();

        class EventLoop *getEventLoop();

        void start();

        void join();

    public:
        // 必须是静态函数
        static void *Main(void *arg);

    private:
        pid_t m_thread_id{-1}; // 线程号
        pthread_t m_thread{0}; // 线程句柄

        class EventLoop *m_event_loop{NULL}; // 当前 io 线程的 loop 对象
        // 使用信号量进行同步
        sem_t m_init_semaphore;

        sem_t m_start_semaphore;
    };

}

#endif