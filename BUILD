cc_binary(
    name = "main",
    srcs = ["main.cc"],
)

cc_library(
    name = "task",
    srcs = [
        "task.cc",
        "task.h",
    ],
)

cc_library(
    name = "parse",
    srcs = [
        "parse.cc",
        "parse.h",
    ],
    deps = [":task"],
)

# Normally we should use cc_test, but it's not working on my system...
cc_binary(
    name = "parse_test",
    srcs = ["parse_test.cc"],
    deps = [
        ":parse",
        "@com_google_googletest//:gtest_main",
    ],
)
