load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "net",
    srcs = ["eventloop.cc", "fd_event.cc", "fd_event_group.cc", "wakeup_fd_event.cc", "timer_event.cc", "timer.cc", "io_thread_group.cc", "io_thread.cc"],
    hdrs = ["eventloop.h", "fd_event.h", "fd_event_group.h", "wakeup_fd_event.h", "timer_event.h", "timer.h", "io_thread_group.h", "io_thread.h"],
    visibility = ["//main:__pkg__", "//minirpc/net/tcp:__pkg__", "//minirpc/net/codec:__pkg__", "//minirpc/net/rpc:__pkg__"],
    deps = ["@minirpc//minirpc/comm:comm"]
)