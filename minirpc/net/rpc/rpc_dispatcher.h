#ifndef MINIRPC_NET_RPC_RPC_DISPATCHER_H
#define MINIRPC_NET_RPC_RPC_DISPATCHER_H

#include <map>
#include <memory>
#include <google/protobuf/service.h>
#include "minirpc/net/codec/abstract_protocol.h"
#include "minirpc/net/codec/tinypb_protocol.h"
// 用于服务端接收并分发来自客户端的RPC请求
namespace minirpc
{

    class TcpConnection;

    class RpcDispatcher
    {

    public:
        static RpcDispatcher *GetRpcDispatcher();

        static void g_dispatch(AbstractProtocol::s_ptr request, AbstractProtocol::s_ptr response, TcpConnection *connection);

        void callback_response(std::shared_ptr<TinyPBProtocol> rsp_protocol, TcpConnection *connection);

    public:
        typedef std::shared_ptr<google::protobuf::Service> service_s_ptr;

        void dispatch(AbstractProtocol::s_ptr request, AbstractProtocol::s_ptr response, TcpConnection *connection);

        void registerService(service_s_ptr service);

        void setTinyPBError(std::shared_ptr<TinyPBProtocol> msg, int32_t err_code, const std::string err_info);

    private:
        bool parseServiceFullName(const std::string &full_name, std::string &service_name, std::string &method_name);

    private:
        std::map<std::string, service_s_ptr> m_service_map;
    };

}

#endif