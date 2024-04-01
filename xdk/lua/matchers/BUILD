package(default_visibility = ["//xdk/lua:__pkg__"])

cc_library(
    name = "is_number",
    testonly = 1,
    srcs = ["is_number.cc"],
    hdrs = ["is_number.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "is_number_test",
    srcs = ["is_number_test.cc"],
    deps = [
        ":is_number",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "is_string",
    testonly = 1,
    srcs = ["is_string.cc"],
    hdrs = ["is_string.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "is_string_test",
    srcs = ["is_string_test.cc"],
    deps = [
        ":is_string",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "is_nil",
    testonly = 1,
    srcs = ["is_nil.cc"],
    hdrs = ["is_nil.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "is_nil_test",
    srcs = ["is_nil_test.cc"],
    deps = [
        ":is_nil",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "has_field",
    testonly = 1,
    srcs = ["has_field.cc"],
    hdrs = ["has_field.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "has_field_test",
    srcs = ["has_field_test.cc"],
    deps = [
        ":has_field",
        ":is_number",
        ":is_string",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "element",
    testonly = 1,
    srcs = ["element.cc"],
    hdrs = ["element.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "element_test",
    srcs = ["element_test.cc"],
    deps = [
        ":element",
        ":is_number",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "top_is",
    testonly = 1,
    srcs = ["top_is.cc"],
    hdrs = ["top_is.h"],
    deps = [
        "//xdk/lua:stack",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "top_is_test",
    srcs = ["top_is_test.cc"],
    deps = [
        ":top_is",
        "//xdk/lua:state",
        "@googletest//:gtest_main",
    ],
)
