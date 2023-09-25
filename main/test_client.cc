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
#include "minirpc/comm/log.h"
#include "minirpc/comm/config.h"
#include "minirpc/net/tcp/tcp_client.h"
#include "minirpc/net/tcp/net_addr.h"
#include "minirpc/net/codec/string_codec.h"
#include "minirpc/net/codec/abstract_protocol.h"
#include "minirpc/net/codec/tinypb_codec.h"
#include "minirpc/net/codec/tinypb_protocol.h"
void test_connect()
{

  // 调用 connect 连接 server
  // wirte 一个字符串
  // 等待 read 返回结果

  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd < 0)
  {
    ERRORLOG("invalid fd %d", fd);
    exit(0);
  }

  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12321);
  inet_aton("127.0.0.1", &server_addr.sin_addr);

  int rt = connect(fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr));

  DEBUGLOG("connect success");

  std::string msg = "hello minirpc!";

  rt = write(fd, msg.c_str(), msg.length());

  DEBUGLOG("success write %d bytes, [%s]", rt, msg.c_str());

  char buf[100];
  rt = read(fd, buf, 100);
  DEBUGLOG("success read %d bytes, [%s]", rt, std::string(buf).c_str());
}

void test_tcp_client()
{

  minirpc::IPNetAddr::s_ptr addr = std::make_shared<minirpc::IPNetAddr>("127.0.0.1", 12321);
  minirpc::TcpClient client(addr);
  client.connect([addr, &client]()
                 {
    DEBUGLOG("conenct to [%s] success", addr->toString().c_str());
    std::shared_ptr<minirpc::TinyPBProtocol> message = std::make_shared<minirpc::TinyPBProtocol>();
    message->m_msg_id = "123456";
    message->m_pb_data = "test pb data";
    client.writeMessage(message, [](minirpc::AbstractProtocol::s_ptr msg_ptr) {
      DEBUGLOG("send message success");
    });

    client.readMessage("123456", [](minirpc::AbstractProtocol::s_ptr msg_ptr) {
      std::shared_ptr<minirpc::TinyPBProtocol> message = std::dynamic_pointer_cast<minirpc::TinyPBProtocol>(msg_ptr);
      DEBUGLOG("msg_id[%s], get response %s", message->m_msg_id.c_str(), message->m_pb_data.c_str());
    }); });
}

int main()
{

  minirpc::Config::SetGlobalConfig("./conf/rocket.xml");

  minirpc::Logger::InitGlobalLogger();

  // test_connect();

  test_tcp_client();

  return 0;
}