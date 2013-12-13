#bin_PROGRAMS = hello #hello_SOURCES = main.c
AUTOMAKE_OPTIONS = subdir-objects

all-recursive: copy-shm

copy-shm:
	mkdir shm -p
	cp -Rf -H $(top_srcdir)/libmcapi/shm/* shm
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/libmcapi/include -I$(top_srcdir)/

lib_LIBRARIES = libopenmcapi.a
libopenmcapi_a_SOURCES = mcapi_cfg.c mcapi/cntrl_msg.c mcapi/connect.c mcapi/create_endpoint.c mcapi/data_avail.c mcapi/data_count.c mcapi/endpoint.c mcapi/forward.c mcapi/get_endp.c mcapi/handle.c mcapi/interface.c mcapi/mcapi_cancel.c mcapi/mcapi_connect_pktchan_i.c mcapi/mcapi_connect_sclchan_i.c mcapi/mcapi_create_endp.c mcapi/mcapi_delete_endp.c mcapi/mcapi_finalize.c mcapi/mcapi_get_endp_attrib.c mcapi/mcapi_get_endp_i.c mcapi/mcapi_get_endp.c mcapi/mcapi_get_node_id.c mcapi/mcapi_init.c mcapi/mcapi_msg_avail.c mcapi/mcapi_msg_rcv_i.c mcapi/mcapi_msg_rcv.c mcapi/mcapi_msg_snd_i.c mcapi/mcapi_msg_snd.c mcapi/mcapi_open_pktchan_rcv_i.c mcapi/mcapi_open_pktchan_snd_i.c mcapi/mcapi_open_sclchan_rcv_i.c mcapi/mcapi_open_sclchan_snd_i.c mcapi/mcapi_pktchan_avail.c mcapi/mcapi_pktchan_free.c mcapi/mcapi_pktchan_rcv_close_i.c mcapi/mcapi_pktchan_rcv_i.c mcapi/mcapi_pktchan_rcv.c mcapi/mcapi_pktchan_snd_close_i.c mcapi/mcapi_pktchan_snd_i.c mcapi/mcapi_pktchan_snd.c mcapi/mcapi_sclchan_avail.c mcapi/mcapi_sclchan_rcv_close_i.c mcapi/mcapi_sclchan_rcv_u16.c mcapi/mcapi_sclchan_rcv_u32.c mcapi/mcapi_sclchan_rcv_u64.c mcapi/mcapi_sclchan_rcv_u8.c mcapi/mcapi_sclchan_snd_close_i.c mcapi/mcapi_sclchan_snd_u16.c mcapi/mcapi_sclchan_snd_u32.c mcapi/mcapi_sclchan_snd_u64.c mcapi/mcapi_sclchan_snd_u8.c mcapi/mcapi_set_endp_attrib.c mcapi/mcapi_test.c mcapi/mcapi_wait_any.c mcapi/mcapi_wait.c mcapi/msg_rcv.c mcapi/msg_snd.c mcapi/node_data.c mcapi/node.c mcapi/pkt_rcv.c mcapi/pkt_snd.c mcapi/queue.c mcapi/request.c mcapi/route.c mcapi/scal_rcv.c mcapi/scal_snd.c mcapi/suspend.c mcapi/mcapi_tls.c shm/shm.c

if OS_LINUX
  libopenmcapi_a_SOURCES += mcapi/linux/mcapi_os.c
  AM_CPPFLAGS += -I$(top_srcdir)/include/linux -I$(KERNELDIR)/arch/$(ARCH)/include -I$(top_srcdir)/libmcapi/include/arch/$(ARCH)/
  AM_MAKEFLAGS = BUILDDIR=@abs_top_builddir@ SRCDIR=@abs_top_srcdir@ KERNELDIR=$(KERNELDIR) CROSS_COMPILE=$(CROSS_COMPILE)- ARCH=$(ARCH)
if OS_SYSV
  libopenmcapi_a_SOURCES += shm/sysv.c
else
  SUBDIRS = shm/linux/kmod
  libopenmcapi_a_SOURCES += shm/linux/shm_os.c
endif

else
if OS_UCOSII
  libopenmcapi_a_SOURCES += mcapi/ucosii/mcapi_os.c shm/ucosii/shm_os.c shm/ucosii/socfpga.c
  AM_CPPFLAGS += -I$(top_srcdir)/include/ucosii -I$(top_srcdir)/libmcapi/include/arch/$(ARCH)/ -DSYSTEM_BUS_WIDTH=32
  AM_CPPFLAGS += -I$(KERNELDIR)/UCOSII/inc -I$(KERNELDIR)/HAL/inc -I $(KERNELDIR)/drivers/inc -I$(KERNELDIR)
endif
endif

if CPU_ARM
  AM_CPPFLAGS += -I$(top_srcdir)/libmcapi/include/arch/arm
endif
