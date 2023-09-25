load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library") 
cc_binary(
    name = "testbuild",
    srcs = ["testbuild.cc"],
    deps = ["@minirpc//minirpc/comm", "@minirpc//minirpc/tinyxml:tinyxml"],
)

cc_binary(
    name = "testlog",
    srcs = ["testlog.cc"],
    deps = ["@minirpc//minirpc/comm"],
)

cc_binary(
    name = "testeventloop",
    srcs = ["testeventloop.cc"],
    deps = ["@minirpc//minirpc/comm", "@minirpc//minirpc/net"],
)

cc_binary(
    name = "test_tcp",
    srcs = ["test_tcp.cc"],
    deps = ["@minirpc//minirpc/comm", "@minirpc//minirpc/net", "@minirpc//minirpc/net/tcp"],
)

cc_binary(
    name = "test_client",
    srcs = ["test_client.cc"],
    deps = ["@minirpc//minirpc/comm", "@minirpc//minirpc/net", "@minirpc//minirpc/net/tcp", "@minirpc//minirpc/net/codec"],
)

cc_binary(
    name = "test_rpc_client",
    srcs = ["test_rpc_client.cc"],
    deps = ["@minirpc//minirpc/comm", "@minirpc//minirpc/net", "@minirpc//minirpc/net/tcp", "@minirpc//minirpc/net/codec", "@minirpc//minirpc/net/rpc", "@minirpc//protoc:order_cc_pb"],
)
cc_binary(
    name = "test_rpc_server",
    srcs = ["test_rpc_server.cc"],
    deps = [
        "@minirpc//minirpc/comm", 
        "@minirpc//minirpc/net", 
        "@minirpc//minirpc/net/tcp", 
        "@minirpc//minirpc/net/codec", 
        "@minirpc//minirpc/net/rpc", 
        "@minirpc//protoc:order_cc_pb",
        "@com_google_protobuf//:protobuf",
    ],
)
