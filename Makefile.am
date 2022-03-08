
LASSEN_ROOT=$(ROOTDIR)/datacsm-kernel
CONFIG_LASSEN_LOADER=$(MODULE_LASSEN_LOADER)
CONFIG_ECPRI_DMA=$(MODULE_ECPRI_DMA)
CONFIG_GSI=$(MODULE_GSI)
CONFIG_LASSEN_MTIP=$(MODULE_LASSEN_MTIP)
CONFIG_ECPRI_CORE=$(MODULE_ECPRI_CORE)
CONFIG_ECPRI_OXTOR=$(MODULE_ECPRI_OXTOR)
CONFIG_LASSEN_MACSEC=$(MODULE_LASSEN_MACSEC)
KBUILD_OPTIONS := LASSEN_ROOT=$(LASSEN_ROOT) \
			CONFIG_LASSEN_LOADER=$(CONFIG_LASSEN_LOADER) \
			CONFIG_ECPRI_DMA=$(CONFIG_ECPRI_DMA) \
			CONFIG_GSI=$(CONFIG_GSI) \
			CONFIG_LASSEN_MTIP=$(CONFIG_LASSEN_MTIP) \
			CONFIG_ECPRI_CORE=$(CONFIG_ECPRI_CORE) \
			CONFIG_ECPRI_OXTOR=$(CONFIG_ECPRI_OXTOR) \
			CONFIG_LASSEN_MACSEC=$(CONFIG_LASSEN_MACSEC)

ifeq ($(TARGET_SUPPORT),genericarmv8)
	KBUILD_OPTIONS += CONFIG_ARCH_WAIPIO=y
endif

obj-m += drivers/loader/
obj-m += drivers/ecpri/dma/
obj-m += drivers/mtip/
obj-m += drivers/ecpri/ecpri_core/
obj-m += drivers/ecpri/ecpri_oxtor/
obj-m += drivers/macsec/

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules $(KBUILD_OPTIONS)

modules_install:
	$(MAKE) INSTALL_MOD_STRIP=1 -C $(KERNEL_SRC) M=$(M) modules_install

%:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $@ $(KBUILD_OPTIONS)

clean:
	rm -f *.o *.ko *.mod.c *.mod.o *~ .*.cmd Module.symvers
	rm -rf .tmp_versions
