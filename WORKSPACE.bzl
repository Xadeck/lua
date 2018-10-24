load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def dependencies():
    git_repository(
        name = "com_google_googletest",
        remote = "https://github.com/google/googletest.git",
        tag = "release-1.8.1",
    )

    git_repository(
        name = "com_google_absl",
        remote = "https://github.com/abseil/abseil-cpp.git",
        tag = "20180600",
    )

    native.new_http_archive(
        name = "lua",
        build_file_content = """
cc_library(
    name = "lua",
    srcs = glob(
        [
            "lua-5.3.5/src/*.c",
            "lua-5.3.5/src/*.h",
        ],
        exclude = [
            "lua-5.3.5/src/lua.c",
            "lua-5.3.5/src/luac.c",
        ],
    ),
    hdrs = [
        "lua-5.3.5/src/lauxlib.h",
        "lua-5.3.5/src/lua.h",
        "lua-5.3.5/src/lua.hpp",
        "lua-5.3.5/src/luaconf.h",
        "lua-5.3.5/src/lualib.h",
    ],
    copts = ["-w"],  # inhibit all warning messages
    includes = ["lua-5.3.5/src"],
    strip_include_prefix = "lua-5.3.5/src",
    include_prefix = "xdk/lua",
    visibility = ["//visibility:public"],
)
        """,
        url = "http://www.lua.org/ftp/lua-5.3.5.tar.gz",
        sha256 = "0c2eed3f960446e1a3e4b9a1ca2f3ff893b6ce41942cf54d5dd59ab4b3b058ac",
    )

COPTS = [
    "-Wall",
    "-Werror",
]
