load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "tcp",
    srcs = ["net_addr.cc", "tcp_accepter.cc", "tcp_client.cc", "tcp_connection.cc", "tcp_server.cc"],
    hdrs = ["net_addr.h", "tcp_accepter.h", "tcp_client.h", "tcp_connection.h", "tcp_server.h", ],
    visibility = ["//main:__pkg__"],
    deps = ["@minirpc//minirpc/comm:comm", "@minirpc//minirpc/net:net", "@minirpc//minirpc/net/codec:codec"]
)