#ifndef MINIRPC_COMM_RUN_TIME_H
#define MINIRPC_COMM_RUN_TIME_H

#include <string>

namespace minirpc
{

    class RpcInterface;

    class RunTime
    {
    public:
        RpcInterface *getRpcInterface();

    public:
        static RunTime *GetRunTime();

    public:
        std::string m_msgid;
        std::string m_method_name;
        RpcInterface *m_rpc_interface{NULL};
    };

}

#endif