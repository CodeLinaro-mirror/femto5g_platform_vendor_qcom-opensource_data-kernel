ECPRIDMADRVTOP = $(src)/drivers

ccflags-y += -I$(src)/../../include
ccflags-y += -I$(ECPRIDMADRVTOP)/gsi
ccflags-y += -I$(ECPRIDMADRVTOP)/gsi/gsihal
ccflags-y += -I$(ECPRIDMADRVTOP)/ecpri_dma
ccflags-y += -I$(ECPRIDMADRVTOP)/ecpri_dma/dmahal
ccflags-y += -I$(ECPRIDMADRVTOP)/ecpri_dma/dma_clients

gsim-m +=	drivers/gsi/gsi.o \
			drivers/gsi/gsihal/gsihal.o \
			drivers/gsi/gsihal/gsihal_reg.o

gsim-$(CONFIG_DEBUG_FS) += drivers/gsi/gsi_dbg.o

obj-$(CONFIG_GSI) += gsim.o


all:
	make -C $(KERNEL_SRC)/include/linux M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC)/build M=$(PWD) clean
