package(
    default_visibility = ["//visibility:public"],
)

COPTS = [
    "-Wall",
    "-Werror",
]

cc_library(
    name = "state",
    srcs = ["state.cc"],
    hdrs = ["state.h"],
    copts = COPTS,
    include_prefix = "xdk/lua",
    deps = ["@lua"],
)

cc_test(
    name = "state_test",
    srcs = ["state_test.cc"],
    copts = COPTS,
    deps = [
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "sandbox",
    srcs = ["sandbox.cc"],
    hdrs = ["sandbox.h"],
    copts = COPTS,
    include_prefix = "xdk/lua",
    deps = ["@lua"],
)

cc_test(
    name = "sandbox_test",
    srcs = ["sandbox_test.cc"],
    copts = COPTS,
    deps = [
        ":sandbox",
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "stack",
    srcs = ["stack.cc"],
    hdrs = ["stack.h"],
    copts = COPTS,
    include_prefix = "xdk/lua",
    deps = [
        "@com_google_absl//absl/strings",
        "@lua",
    ],
)

cc_test(
    name = "stack_test",
    srcs = ["stack_test.cc"],
    copts = COPTS,
    deps = [
        ":stack",
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)
