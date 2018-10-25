load("//:WORKSPACE.bzl", "COPTS")

package(default_visibility = ["//xdk/lua:__pkg__"])

cc_library(
    name = "is_number",
    testonly = 1,
    srcs = ["is_number.cc"],
    hdrs = ["is_number.h"],
    copts = COPTS,
    deps = [
        "//xdk/lua:stack",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "is_number_test",
    srcs = ["is_number_test.cc"],
    deps = [
        ":is_number",
        "//xdk/lua:state",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "is_string",
    testonly = 1,
    srcs = ["is_string.cc"],
    hdrs = ["is_string.h"],
    copts = COPTS,
    deps = [
        "//xdk/lua:stack",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "is_string_test",
    srcs = ["is_string_test.cc"],
    deps = [
        ":is_string",
        "//xdk/lua:state",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "element",
    testonly = 1,
    srcs = ["element.cc"],
    hdrs = ["element.h"],
    copts = COPTS,
    deps = [
        "//xdk/lua:stack",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "element_test",
    srcs = ["element_test.cc"],
    deps = [
        ":element",
        ":is_number",
        "//xdk/lua:state",
        "@com_google_googletest//:gtest_main",
    ],
)
