load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "comm",
    srcs = ["log.cc", "run_time.cc", "tcp_buffer.cc", "config.cc", "utils.cc"],
    hdrs = ["log.h", "run_time.h", "tcp_buffer.h", "config.h", "utils.h", "mutex.h", "error_code.h"],
    visibility = ["//main:__pkg__", "//minirpc/net:__pkg__", "//minirpc/net/tcp:__pkg__", "//minirpc/net/codec:__pkg__"],
    deps = ["@minirpc//minirpc/tinyxml:tinyxml"]
)