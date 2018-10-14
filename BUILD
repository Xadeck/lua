cc_library(
    name = "state",
    srcs = ["state.cc"],
    hdrs = ["state.h"],
    deps = ["@lua"],
)

cc_test(
    name = "state_test",
    srcs = ["state_test.cc"],
    deps = [
        ":state",
        "@googletest//:gtest_main",
    ],
)
