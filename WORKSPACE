load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "84bf0acb4a7ed172ffdd806bb3bef76ad705f4ea63ac7175cd7c86df2a017d17",
    strip_prefix = "googletest-3e0e32ba300ce8afe695ad3ba7e81b21b7cf237a",
    urls = ["https://github.com/google/googletest/archive/3e0e32ba300ce8afe695ad3ba7e81b21b7cf237a.zip"],  # Nov 18, 2021
)

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-ec0d76f1d012cc1a4b3b08dfafcfc5237f5ba2c9",
    urls = ["https://github.com/abseil/abseil-cpp/archive/ec0d76f1d012cc1a4b3b08dfafcfc5237f5ba2c9.zip"],  # Nov 22, 2021
)

# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    sha256 = "631ebb98ad2742c60112ab7fbf2f23563e398ccbb6919dacabd1a576b15d34ae",
    strip_prefix = "bazel-compile-commands-extractor-cae9ef3d0e1e401986d97ebc4fb072c9bcb5f8e3",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/cae9ef3d0e1e401986d97ebc4fb072c9bcb5f8e3.tar.gz",
)

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "ce2931dd537eaab7dab78b25bec6136a0756ca0b2acbdab9aec0266998c0d9a7",
    strip_prefix = "gflags-827c769e5fc98e0f2a34c47cef953cc6328abced",
    url = "https://github.com/gflags/gflags/archive/827c769e5fc98e0f2a34c47cef953cc6328abced.tar.gz",
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "f3a1ef9b757545f4ab0b0190dfc802973a362f30bff2be8477277d1ead332c70",
    strip_prefix = "glog-503e3dec8d1fe071376befc62119a837c26612a3",
    url = "https://github.com/google/glog/archive/503e3dec8d1fe071376befc62119a837c26612a3.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
