#include <memory>
#include "minirpc/comm/log.h"
#include "minirpc/comm/config.h"
#include "minirpc/comm/net_addr.h"
#include "minirpc/net/tcp/tcp_server.h"

void test_tcp_server()
{

    minirpc::IPNetAddr::s_ptr addr = std::make_shared<minirpc::IPNetAddr>("127.0.0.1", minirpc::Config::GetGlobalConfig()->m_port);

    DEBUGLOG("create addr %s", addr->toString().c_str());

    minirpc::TcpServer tcp_server(addr);

    tcp_server.start();
}

int main()
{

    minirpc::Config::SetGlobalConfig("./conf/rocket.xml");
    minirpc::Logger::InitGlobalLogger();

    test_tcp_server();
}
