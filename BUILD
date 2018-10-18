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

cc_library(
    name = "sandbox",
    srcs = ["sandbox.cc"],
    hdrs = ["sandbox.h"],
    include_prefix = "xdk/lua",
    deps = ["@lua"],
)

cc_test(
    name = "sandbox_test",
    srcs = ["sandbox_test.cc"],
    deps = [
        ":sandbox",
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)
