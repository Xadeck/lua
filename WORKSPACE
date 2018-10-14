load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.8.1",
)

new_http_archive(
    name = "lua",
    build_file = "lua.BUILD",
    url = "http://www.lua.org/ftp/lua-5.3.5.tar.gz",
)
