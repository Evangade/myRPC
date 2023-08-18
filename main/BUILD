load("@rules_cc//cc:defs.bzl", "cc_binary")

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

