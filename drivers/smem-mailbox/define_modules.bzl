load("//build/kernel/kleaf:kernel.bzl", "ddk_module")
load("@rules_pkg//pkg:install.bzl", "pkg_install")
load("@rules_pkg//pkg:mappings.bzl", "pkg_files", "strip_prefix")

def define_modules(target, variant):
    kernel_build_variant = "{}_{}".format(target, variant)

    ddk_module(
        name = "{}_smem_mailbox".format(kernel_build_variant),
        kernel_build = "//msm-kernel:{}".format(kernel_build_variant),
        deps = ["//msm-kernel:all_headers"],
        srcs = [
            "smem-mailbox.c"
        ],
        hdrs = [
            "include/smem-mailbox.h"
        ],
        includes = [
            "include"
        ],
        out = "smem-mailbox.ko",
        visibility = ["//visibility:public"]
    )

    pkg_files(
        name = kernel_build_variant + "_dist_files",
        srcs = [":{}_smem_mailbox".format(kernel_build_variant)],
        visibility = ["//visibility:private"],
        strip_prefix = strip_prefix.files_only(),
    )

    pkg_install(
        name = "{}_smem_mailbox_dist".format(kernel_build_variant),
        srcs = [":{}_dist_files".format(kernel_build_variant)],
        destdir = "out/target/product/{}/dlkm/lib/modules/".format(kernel_build_variant),
    )
