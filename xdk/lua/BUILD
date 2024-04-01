package(
    default_visibility = ["//visibility:public"],
)

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

cc_library(
    name = "stack",
    srcs = ["stack.cc"],
    hdrs = ["stack.h"],
    deps = ["@lua"],
)

cc_test(
    name = "stack_test",
    srcs = ["stack_test.cc"],
    deps = [
        ":stack",
        ":state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "matchers",
    testonly = 1,
    hdrs = ["matchers.h"],
    deps = [
        ":stack",
        "//xdk/lua/matchers:element",
        "//xdk/lua/matchers:has_field",
        "//xdk/lua/matchers:is_nil",
        "//xdk/lua/matchers:is_number",
        "//xdk/lua/matchers:is_string",
        "//xdk/lua/matchers:top_is",
        "@googletest//:gtest",
        "@lua",
    ],
)

cc_test(
    name = "matchers_test",
    srcs = ["matchers_test.cc"],
    deps = [
        ":matchers",
        ":stack",
        ":state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "sandbox",
    srcs = ["sandbox.cc"],
    hdrs = ["sandbox.h"],
    deps = ["@lua"],
)

cc_test(
    name = "sandbox_test",
    srcs = ["sandbox_test.cc"],
    deps = [
        ":matchers",
        ":sandbox",
        ":state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "string_view",
    srcs = ["string_view.cc"],
    hdrs = ["string_view.h"],
    deps = [
        ":state",
        "@lua",
    ],
)

cc_test(
    name = "string_view_test",
    srcs = ["string_view_test.cc"],
    deps = [
        ":string_view",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "back",
    srcs = ["back.cc"],
    hdrs = ["back.h"],
    deps = [
        ":string_view",
        "@lua",
    ],
)

cc_test(
    name = "back_test",
    srcs = ["back_test.cc"],
    deps = [
        ":back",
        ":matchers",
        ":state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "rawfield",
    srcs = ["rawfield.cc"],
    hdrs = ["rawfield.h"],
    deps = [
        "@lua",
    ],
)

cc_test(
    name = "rawfield_test",
    srcs = ["rawfield_test.cc"],
    deps = [
        ":matchers",
        ":rawfield",
        ":state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "read",
    srcs = ["read.cc"],
    hdrs = ["read.h"],
    deps = ["@lua"],
)

cc_test(
    name = "read_test",
    srcs = ["read_test.cc"],
    deps = [
        ":read",
        ":state",
        "@googletest//:gtest_main",
    ],
)
