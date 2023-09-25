#include <assert.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <memory>
#include <unistd.h>
#include <google/protobuf/service.h>
#include "minirpc/comm/log.h"
#include "minirpc/comm/config.h"
#include "minirpc/comm/net_addr.h"
#include "minirpc/net/codec/string_codec.h"
#include "minirpc/net/codec/abstract_protocol.h"
#include "minirpc/net/codec/tinypb_codec.h"
#include "minirpc/net/codec/tinypb_protocol.h"
#include "minirpc/net/tcp/tcp_server.h"
#include "minirpc/net/tcp/tcp_client.h"
#include "minirpc/net/rpc/rpc_dispatcher.h"

#include "protoc/order.pb.h"

class OrderImpl : public Order
{
public:
    void makeOrder(google::protobuf::RpcController *controller,
                   const ::makeOrderRequest *request,
                   ::makeOrderResponse *response,
                   ::google::protobuf::Closure *done)
    {
        DEBUGLOG("start sleep s");
        sleep(1);
        DEBUGLOG("end sleep 5s");
        if (request->price() < 10)
        {
            response->set_ret_code(-1);
            response->set_res_info("short balance");
            return;
        }
        response->set_order_id("20230514");
        DEBUGLOG("call makeOrder success");
    }
};

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Start test_rpc_server error, argc not 2 \n");
        printf("Start like this: \n");
        printf("./test_rpc_server ./conf/rocket.xml \n");
        return 0;
    }

    minirpc::Config::SetGlobalConfig(argv[1]);

    minirpc::Logger::InitGlobalLogger();

    std::shared_ptr<OrderImpl> service = std::make_shared<OrderImpl>();
    minirpc::RpcDispatcher::GetRpcDispatcher()->registerService(service);

    minirpc::IPNetAddr::s_ptr addr = std::make_shared<minirpc::IPNetAddr>("127.0.0.1", minirpc::Config::GetGlobalConfig()->m_port);

    minirpc::TcpServer tcp_server(addr, minirpc::RpcDispatcher::g_dispatch);

    tcp_server.start();

    return 0;
}