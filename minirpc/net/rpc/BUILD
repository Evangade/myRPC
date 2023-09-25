load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library") 

cc_library(
    name = "rpc",
    srcs = ["rpc_controller.cc", "rpc_dispatcher.cc", "rpc_interface.cc", "rpc_channel.cc", "msg_id_util.cc"],
    hdrs = ["rpc_closure.h", "rpc_controller.h", "rpc_dispatcher.h", "rpc_interface.h", "rpc_channel.h", "msg_id_util.h"],
    visibility = ["//main:__pkg__"],
    deps = ["@minirpc//minirpc/comm:comm", "@minirpc//minirpc/net:net", 
    "@minirpc//minirpc/net/codec:codec", "@minirpc//minirpc/net/tcp:tcp",
    "@com_google_protobuf//:protobuf"]
)