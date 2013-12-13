KERNELDIR ?= /lib/modules/`uname -r`/build

PWD = $(shell pwd)
KBUILD_FLAGS = EXTRA_CFLAGS="-I$(SRCDIR)/libmcapi/include -I$(BUILDDIR)/" -C $(KERNELDIR) M=$(PWD) INSTALL_MOD_PATH=$(D)
KBUILD_EXTRA_SYMBOLS:=$(KERNELDIR)/Module.symvers

install:
	$(MAKE) -C $(KERNELDIR) modules_install DEPMOD=echo INSTALL_MOD_PATH=$(INSTALL_MOD_PATH) KERNEL_SRC=$(KERNELDIR) INSTALL_MOD_PATH=$(DESTDIR) M=$(PWD)

%:
	$(MAKE) $(KBUILD_FLAGS) modules

.DEFAULT_GOAL = modules
