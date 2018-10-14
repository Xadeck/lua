package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "state",
    srcs = ["state.cc"],
    hdrs = ["state.h"],
    include_prefix = "xdk/lua",
    deps = ["@lua"],
)

cc_test(
    name = "state_test",
    srcs = ["state_test.cc"],
    deps = [
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)
