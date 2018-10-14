load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "com_google_googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.8.1",
)

git_repository(
    name = "com_github_google_benchmark",
    remote = "https://github.com/google/benchmark.git",
    tag = "v1.4.1",
)

git_repository(
    name = "com_github_abseil_abseil_cpp",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20180600",
)

new_http_archive(
    name = "lua",
    build_file = "lua.BUILD",
    url = "http://www.lua.org/ftp/lua-5.3.5.tar.gz",
)
