load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "codec",
    srcs = ["tinypb_codec.cc", "tinypb_protocol.cc"],
    hdrs = ["abstract_codec.h", "abstract_protocol.h", "string_codec.h", "tinypb_codec.h", "tinypb_protocol.h"],
    visibility = ["//main:__pkg__", "//minirpc/net/tcp:__pkg__", "//minirpc/net/rpc:__pkg__"],
    deps = ["@minirpc//minirpc/comm:comm", "@minirpc//minirpc/net:net"]
)