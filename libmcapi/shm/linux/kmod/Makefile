KERNELDIR ?= /lib/modules/`uname -r`/build

PWD = $(shell pwd)
KBUILD_FLAGS = -C $(KERNELDIR) M=$(PWD) KERNELRELEASE=$(KERNELRELEASE)

modules:
	$(MAKE) $(KBUILD_FLAGS) $@

clean:
	$(MAKE) $(KBUILD_FLAGS) $@
