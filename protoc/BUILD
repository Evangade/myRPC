load("@rules_cc//cc:defs.bzl", "cc_proto_library") 
load("@rules_proto//proto:defs.bzl", "proto_library") 

proto_library( 
    name = "order_pb", 
    srcs = ["order.proto"], 
) 
cc_proto_library(
    name = "order_cc_pb",
#    srcs = ["order.pb.cc"],
#    hdrs = ["order.pb.h"],
    deps = [":order_pb"],
)
package(default_visibility = ["//visibility:public"]) 