package(
    default_visibility = ["//visibility:public"],
)

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
    deps = [":constants"],
)

cc_library(
    name = "parse",
    srcs = [
        "parse.cc",
        "parse.h",
    ],
    deps = [":task"],
)

cc_library(
    name = "problem",
    srcs = [
        "problem.cc",
        "problem.h",
    ],
    deps = [
        ":constants",
        ":task",
    ],
)

cc_library(
    name = "schedule",
    srcs = [
        "schedule.cc",
        "schedule.h",
    ],
    deps = [
        ":constants",
        ":problem",
        ":task",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "constants",
    srcs = [
        "constants.h",
    ],
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

cc_binary(
    name = "problem_test",
    srcs = ["problem_test.cc"],
    deps = [
        ":parse",
        ":problem",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "schedule_test",
    srcs = ["schedule_test.cc"],
    deps = [
        ":parse",
        ":schedule",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:span",
        "@com_google_googletest//:gtest_main",
    ],
)
