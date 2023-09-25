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
#include "minirpc/net/rpc/rpc_controller.h"
#include "minirpc/net/rpc/rpc_channel.h"
#include "minirpc/net/rpc/rpc_closure.h"

#include "protoc/order.pb.h"

void test_tcp_client()
{

  minirpc::IPNetAddr::s_ptr addr = std::make_shared<minirpc::IPNetAddr>("127.0.0.1", 12321);
  minirpc::TcpClient client(addr);
  client.connect([addr, &client]()
                 {
    DEBUGLOG("conenct to [%s] success", addr->toString().c_str());
    std::shared_ptr<minirpc::TinyPBProtocol> message = std::make_shared<minirpc::TinyPBProtocol>();
    message->m_msg_id = "99998888";
    message->m_pb_data = "test pb data";

    makeOrderRequest request;
    request.set_price(100);
    request.set_goods("apple");
    
    if (!request.SerializeToString(&(message->m_pb_data))) {
      ERRORLOG("serilize error");
      return;
    }

    message->m_method_name = "Order.makeOrder";

    client.writeMessage(message, [request](minirpc::AbstractProtocol::s_ptr msg_ptr) {
      DEBUGLOG("send message success, request[%s]", request.ShortDebugString().c_str());
    });


    client.readMessage("99998888", [](minirpc::AbstractProtocol::s_ptr msg_ptr) {
      std::shared_ptr<minirpc::TinyPBProtocol> message = std::dynamic_pointer_cast<minirpc::TinyPBProtocol>(msg_ptr);
      DEBUGLOG("msg_id[%s], get response %s", message->m_msg_id.c_str(), message->m_pb_data.c_str());
      makeOrderResponse response;

      if(!response.ParseFromString(message->m_pb_data)) {
        ERRORLOG("deserialize error");
        return;
      }
      DEBUGLOG("get response success, response[%s]", response.ShortDebugString().c_str());
    }); });
}

void test_rpc_channel()
{

  NEWRPCCHANNEL("127.0.0.1:12321", channel);

  // std::shared_ptr<makeOrderRequest> request = std::make_shared<makeOrderRequest>();

  NEWMESSAGE(makeOrderRequest, request);
  NEWMESSAGE(makeOrderResponse, response);

  request->set_price(100);
  request->set_goods("apple");

  NEWRPCCONTROLLER(controller);
  controller->SetMsgId("99998888");
  controller->SetTimeout(10000);

  std::shared_ptr<minirpc::RpcClosure> closure = std::make_shared<minirpc::RpcClosure>(nullptr, [request, response, channel, controller]() mutable
                                                                                       {
    if (controller->GetErrorCode() == 0) {
      INFOLOG("call rpc success, request[%s], response[%s]", request->ShortDebugString().c_str(), response->ShortDebugString().c_str());
      // 执行业务逻辑
      if (response->order_id() == "xxx") {
        // xx
      }
    } else {
      ERRORLOG("call rpc failed, request[%s], error code[%d], error info[%s]", 
        request->ShortDebugString().c_str(), 
        controller->GetErrorCode(), 
        controller->GetErrorInfo().c_str());
    }
  
    INFOLOG("now exit eventloop");
    // channel->getTcpClient()->stop();
    channel.reset(); });

  CALLRPRC("127.0.0.1:12321", Order_Stub, makeOrder, controller, request, response, closure);

  // xxx
  // 协程
}

int main()
{

  minirpc::Config::SetGlobalConfig(NULL);

  minirpc::Logger::InitGlobalLogger(0);

  // test_tcp_client();
  test_rpc_channel();

  INFOLOG("test_rpc_channel end");

  return 0;
}