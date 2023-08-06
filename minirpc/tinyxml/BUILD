load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "tinyxml",
    srcs = ["libtinyxml.a"],
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    linkstatic = 1,
)