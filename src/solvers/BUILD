package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "threshold",
    srcs = [
        "threshold.cc",
        "threshold.h",
    ],
    deps = [
        ":sequence",
        "//src:problem",
        "//src:schedule",
    ],
)

cc_binary(
    name = "threshold_solve2",
    srcs = [
        "threshold_solve2.cc",
    ],
    deps = [
        ":sequence",
        ":threshold",
        "//src:parse",
        "//src:problem",
        "//src:schedule",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_binary(
    name = "threshold_solve",
    srcs = [
        "threshold_solve.cc",
    ],
    deps = [
        ":sequence",
        ":threshold",
        "//src:parse",
        "//src:problem",
        "//src:schedule",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_library(
    name = "sequence",
    srcs = [
        "sequence.cc",
        "sequence.h",
    ],
    deps = [
        "//src:schedule",
    ],
)
