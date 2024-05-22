load(":rmnetbam_modules.bzl", "rmnetbam_modules")
load(":module_mgr.bzl", "define_target_modules")

def define_mdm9607():
     define_target_modules(
        target = "mdm9607",
        variants = ["debug-defconfig", "perf-defconfig"],
        registry = rmnetbam_modules,
        modules = [
            "rmnet_bam",
        ],
        config_options = []
    )
