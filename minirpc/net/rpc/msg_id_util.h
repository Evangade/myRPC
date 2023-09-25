#ifndef MINIRPC_COMMON_MSGID_UTIL_H
#define MINIRPC_COMMON_MSGID_UTIL_H

#include <string>

namespace minirpc
{

    class MsgIDUtil
    {

    public:
        static std::string GenMsgID();
    };

}

#endif