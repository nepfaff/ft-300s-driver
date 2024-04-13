# -*- python -*-
# This file contains rules for Bazel; see drake/doc/bazel.rst.

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "ft_300s_driver",
    srcs =  [
      "main.c",
      "rq_int.h",
      "rq_sensor_com.c",
      "rq_sensor_com.h",
      "rq_sensor_socket.c",
      "rq_sensor_socket.h",
      "rq_sensor_state.c",
      "rq_sensor_state.h",
      "Thread/mutex.c",
      "Thread/mutex.h",
      "Thread/rq_thread.c",
      "Thread/rq_thread.h",
    ],
    linkstatic = 1,
    deps = [
        "@gflags//:gflags",
        "@lcm//:lcm",
    ]
)
