#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <memory>
#include "minirpc/comm/log.h"
#include "minirpc/comm/config.h"
#include "minirpc/net/fd_event.h"
#include "minirpc/net/eventloop.h"
#include "minirpc/net/timer_event.h"
#include "minirpc/net/io_thread.h"
#include "minirpc/net/io_thread_group.h"

void test_io_thread()
{

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        ERRORLOG("listenfd = -1");
        exit(0);
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_port = htons(minirpc::Config::GetGlobalConfig()->m_port);
    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr);

    int rt = bind(listenfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
    if (rt != 0)
    {
        ERRORLOG("bind error");
        exit(1);
    }

    rt = listen(listenfd, 100);
    if (rt != 0)
    {
        ERRORLOG("listen error");
        exit(1);
    }

    minirpc::FdEvent event(listenfd);
    event.listen(minirpc::FdEvent::IN_EVENT, [listenfd]()
                 {
                     sockaddr_in peer_addr;
                     socklen_t addr_len = sizeof(peer_addr);
                     memset(&peer_addr, 0, sizeof(peer_addr));
                     int clientfd = accept(listenfd, reinterpret_cast<sockaddr *>(&peer_addr), &addr_len);

                     DEBUGLOG("success get client fd[%d], peer addr: [%s:%d]", clientfd, inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port)); });

    int i = 0;
    minirpc::TimerEvent::s_ptr timer_event = std::make_shared<minirpc::TimerEvent>(
        1000, true, [&i]()
        { INFOLOG("trigger timer event, count=%d", i++); });

    // minirpc::IOThread io_thread;

    // io_thread.getEventLoop()->addEpollEvent(&event);
    //  io_thread.getEventLoop()->addTimerEvent(timer_event);
    // io_thread.start();

    // io_thread.join();

    minirpc::IOThreadGroup io_thread_group(2);
    minirpc::IOThread *io_thread = io_thread_group.getIOThread();
    io_thread->getEventLoop()->addEpollEvent(&event);
    io_thread->getEventLoop()->addTimerEvent(timer_event);

    minirpc::IOThread *io_thread2 = io_thread_group.getIOThread();
    io_thread2->getEventLoop()->addTimerEvent(timer_event);

    io_thread_group.start();
    io_thread_group.join();
}

void test_E_L()
{
    minirpc::EventLoop *eventloop = new minirpc::EventLoop();
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        ERRORLOG("listenfd = -1");
        exit(0);
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_port = htons(minirpc::Config::GetGlobalConfig()->m_port);
    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr);

    int rt = bind(listenfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
    if (rt != 0)
    {
        ERRORLOG("bind error");
        exit(1);
    }

    rt = listen(listenfd, 100);
    if (rt != 0)
    {
        ERRORLOG("listen error");
        exit(1);
    }

    minirpc::FdEvent event(listenfd);
    event.listen(minirpc::FdEvent::IN_EVENT, [listenfd]()
                 {
                     sockaddr_in peer_addr;
                     socklen_t addr_len = sizeof(peer_addr);
                     memset(&peer_addr, 0, sizeof(peer_addr));
                     int clientfd = accept(listenfd, reinterpret_cast<sockaddr *>(&peer_addr), &addr_len);

                     DEBUGLOG("success get client fd[%d], peer addr: [%s:%d]", clientfd, inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port)); });
    eventloop->addEpollEvent(&event);
    int i = 0;
    minirpc::TimerEvent::s_ptr timer_event = std::make_shared<minirpc::TimerEvent>(
        1000, true, [&i]()
        { INFOLOG("trigger timer event, count=%d", i++); });
    // eventloop->addTimerEvent(timer_event);
    eventloop->loop();
    return;
}
int main()
{

    minirpc::Config::SetGlobalConfig("./conf/rocket.xml");

    minirpc::Logger::InitGlobalLogger();
    // test_E_L();
    test_io_thread();
    return 0;
}