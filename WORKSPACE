# -*- mode: python -*-

workspace(name = "ft_300s_driver")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

(DRAKE_COMMIT, DRAKE_CHECKSUM) = (
    "v1.20.0",
    "e343bc558f840be17c05053c6fc3fff899a3bf4540f3b285f6cd7ca5937f7b46",
)
# Before changing the COMMIT, temporarily uncomment the next line so that Bazel
# displays the suggested new value for the CHECKSUM.
# DRAKE_CHECKSUM = "0" * 64
DRAKE_STRIP_PREFIX = "drake-1.20.0"

# Or to build against a local checkout of Drake, at the bash prompt set an
# environment variable before building:
#  export SCHUNK_LOCAL_DRAKE_PATH=/home/user/stuff/drake

# Load an environment variable.
load("//:environ.bzl", "environ_repository")
environ_repository(name = "environ", vars = ["FT300S_LOCAL_DRAKE_PATH"])
load("@environ//:environ.bzl", FT300S_LOCAL_DRAKE_PATH = "FT300S_LOCAL_DRAKE_PATH")

# This declares the `@drake` repository as an http_archive from github,
# iff FT300S_LOCAL_DRAKE_PATH is unset.  When it is set, this declares a
# `@drake_ignored` package which is never referenced, and thus is ignored.
http_archive(
    name = "drake" if not FT300S_LOCAL_DRAKE_PATH else "drake_ignored",
    sha256 = DRAKE_CHECKSUM,
    strip_prefix = DRAKE_STRIP_PREFIX,
    urls = [x.format(DRAKE_COMMIT) for x in [
        "https://github.com/RobotLocomotion/drake/archive/{}.tar.gz",
    ]],
)

# This declares the `@drake` repository as a local directory,
# iff FT300S_LOCAL_DRAKE_PATH is set.  When it is unset, this declares a
# `@drake_ignored` package which is never referenced, and thus is ignored.
local_repository(
    name = "drake" if FT300S_LOCAL_DRAKE_PATH else "drake_ignored",
    path = FT300S_LOCAL_DRAKE_PATH,
)
print("Using FT300S_LOCAL_DRAKE_PATH={}".format(FT300S_LOCAL_DRAKE_PATH)) if FT300S_LOCAL_DRAKE_PATH else None  # noqa

load("@drake//tools/workspace:default.bzl", "add_default_repositories")

# WARNING: We allow `vtk`, but should take care to avoid linking in multiple
# versions of VTK!
add_default_repositories()
