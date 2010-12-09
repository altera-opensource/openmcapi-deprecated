KERNELDIR ?= /lib/modules/`uname -r`/build

PWD = $(shell pwd)
KBUILD_FLAGS = -C $(KERNELDIR) M=$(PWD) KERNELRELEASE=$(KERNELRELEASE)

%:
	$(MAKE) $(KBUILD_FLAGS) $@

.DEFAULT_GOAL = modules
