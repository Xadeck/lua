load("//:WORKSPACE.bzl", "COPTS")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "state",
    srcs = ["state.cc"],
    hdrs = ["state.h"],
    copts = COPTS,
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
    name = "stack",
    srcs = ["stack.cc"],
    hdrs = ["stack.h"],
    copts = COPTS,
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

cc_library(
    name = "matchers",
    testonly = 1,
    hdrs = ["matchers.h"],
    copts = COPTS,
    deps = [
        ":stack",
        "//xdk/lua/matchers:element",
        "//xdk/lua/matchers:has_field",
        "//xdk/lua/matchers:is_nil",
        "//xdk/lua/matchers:is_number",
        "//xdk/lua/matchers:is_string",
        "@com_google_googletest//:gtest",
        "@lua",
    ],
)

cc_test(
    name = "matchers_test",
    srcs = ["matchers_test.cc"],
    copts = COPTS,
    deps = [
        ":matchers",
        ":stack",
        ":state",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "sandbox",
    srcs = ["sandbox.cc"],
    hdrs = ["sandbox.h"],
    copts = COPTS,
    deps = ["@lua"],
)

cc_test(
    name = "sandbox_test",
    srcs = ["sandbox_test.cc"],
    copts = COPTS,
    deps = [
        ":matchers",
        ":sandbox",
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "string_view",
    srcs = ["string_view.cc"],
    hdrs = ["string_view.h"],
    copts = COPTS,
    deps = [
        ":state",
        "@com_google_absl//absl/strings",
        "@lua",
    ],
)

cc_test(
    name = "string_view_test",
    srcs = ["string_view_test.cc"],
    copts = COPTS,
    deps = [
        ":string_view",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "back",
    srcs = ["back.cc"],
    hdrs = ["back.h"],
    copts = COPTS,
    deps = [
        ":string_view",
        "@lua",
    ],
)

cc_test(
    name = "back_test",
    srcs = ["back_test.cc"],
    copts = COPTS,
    deps = [
        ":back",
        ":matchers",
        ":state",
        "@com_google_googletest//:gtest_main",
    ],
)
