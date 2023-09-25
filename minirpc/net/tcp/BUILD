load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "tcp",
    srcs = ["tcp_accepter.cc", "tcp_client.cc", "tcp_connection.cc", "tcp_server.cc"],
    hdrs = ["tcp_accepter.h", "tcp_client.h", "tcp_connection.h", "tcp_server.h", ],
    visibility = ["//main:__pkg__", "//minirpc/net/rpc:__pkg__"],
    deps = ["@minirpc//minirpc/comm:comm", "@minirpc//minirpc/net:net", "@minirpc//minirpc/net/codec:codec"]
)