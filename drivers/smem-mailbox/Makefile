KBUILD_OPTIONS += SMEM_MAILBOX_ROOT=$(KERNEL_SRC)/$(M)

all: modules # dtbs

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) clean

%:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $@ $(KBUILD_OPTIONS)
