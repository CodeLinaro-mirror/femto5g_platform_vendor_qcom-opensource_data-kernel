ifeq ($(RELEASE_PACKAGE),1)
EXTRA_CFLAGS+=-DRELEASE_PACKAGE
endif
LBITS ?= $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
CCFLAGS += -m64
EXTRA_CFLAGS+=-DSYSTEM_IS_64
else
CCFLAGS += -m32
endif

M ?= $(shell pwd)

rmnet_bam-y += 	msm_rmnet_bam.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build

KBUILD_OPTIONS := RMNET_BAM_ROOT=$(PWD)
KBUILD_OPTIONS += MODNAME?=rmnet_bam

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules $(KBUILD_OPTIONS)

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) clean
