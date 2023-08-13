#include <thread>
#include "minirpc/comm/log.h"
#include "minirpc/comm/config.h"
// using namespace minirpc;
void fun()
{

    int i = 20;
    while (i--)
    {
        DEBUGLOG("debug this is thread in %s", "fun");
        INFOLOG("info this is thread in %s", "fun");
    }

    return;
}
int main(int argc, const char **argv)
{
    minirpc::Config::SetGlobalConfig("./conf/rocket.xml");
    minirpc::Logger::InitGlobalLogger();

    std::thread t(fun);

    int i = 20;
    while (i--)
    {
        DEBUGLOG("test debug log %s", "10");
        INFOLOG("test info log %s", "10");
    }

    t.join();
    return 0;
}