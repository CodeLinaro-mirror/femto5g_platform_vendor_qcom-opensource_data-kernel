
ifeq ($(LASSEN_ROOT),)
LASSEN_ROOT=$(srctree)/datacsm-kernel
endif

KBUILD_EXTRA_SYMBOLS +=../transceiver-driver/drivers/Module.symvers

obj-$(CONFIG_LASSEN_LOADER) += drivers/loader/
obj-$(CONFIG_ECPRI_DMA) += drivers/ecpri/dma/
obj-$(CONFIG_LASSEN_MTIP) += drivers/mtip/
obj-$(CONFIG_ECPRI_CORE) += drivers/ecpri/ecpri_core/
obj-$(CONFIG_ECPRI_OXTOR) += drivers/ecpri/ecpri_oxtor/
obj-$(CONFIG_LASSEN_MACSEC) += drivers/macsec/
obj-$(CONFIG_LASSEN_QCOM_AW_PHY) += drivers/qcom_aw_phy/
