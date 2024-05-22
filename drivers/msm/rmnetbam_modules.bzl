load(":module_mgr.bzl", "create_module_registry")
RMNETBAM_PATH = ""

rmnetbam_modules = create_module_registry([":rmnetbam_src_headers"])

rmnetbam_modules.register(
    name = "rmnet_bam",
    path = RMNETBAM_PATH,
    srcs = ([
            "msm_rmnet_bam.c",
            ]),
)

