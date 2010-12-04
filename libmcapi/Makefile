D := libmcapi

LIB-CPPFLAGS-y = -MD

# public headers
LIB-CPPFLAGS-y += -I include
LIB-CPPFLAGS-$(CONFIG_LINUX) += -I include/linux

# private OpenMCAPI headers
LIB-CPPFLAGS-y += -I $(D)/include
LIB-CPPFLAGS-$(CONFIG_POWERPC) += -I $(D)/include/arch/powerpc
LIB-CPPFLAGS-$(CONFIG_SHM) += -I $(D)/include/shm -D CONFIG_SHM

LIB-CPPFLAGS = $(LIB-CPPFLAGS-y)

LIB-CFLAGS-y = -O2
LIB-CFLAGS = $(LIB-CFLAGS-y)


LIB-OBJS-y = \
	$(D)/mcapi_cfg.o \
	$(D)/mcapi/buf_mgmt.o \
	$(D)/mcapi/cntrl_msg.o \
	$(D)/mcapi/connect.o \
	$(D)/mcapi/create_endpoint.o \
	$(D)/mcapi/data_avail.o \
	$(D)/mcapi/data_count.o \
	$(D)/mcapi/endpoint.o \
	$(D)/mcapi/forward.o \
	$(D)/mcapi/get_endp.o \
	$(D)/mcapi/handle.o \
	$(D)/mcapi/interface.o \
	$(D)/mcapi/loopback.o \
	$(D)/mcapi/mcapi_cancel.o \
	$(D)/mcapi/mcapi_connect_pktchan_i.o \
	$(D)/mcapi/mcapi_connect_sclchan_i.o \
	$(D)/mcapi/mcapi_create_endp.o \
	$(D)/mcapi/mcapi_delete_endp.o \
	$(D)/mcapi/mcapi_finalize.o \
	$(D)/mcapi/mcapi_get_endp_attrib.o \
	$(D)/mcapi/mcapi_get_endp_i.o \
	$(D)/mcapi/mcapi_get_endp.o \
	$(D)/mcapi/mcapi_get_node_id.o \
	$(D)/mcapi/mcapi_init.o \
	$(D)/mcapi/mcapi_msg_avail.o \
	$(D)/mcapi/mcapi_msg_rcv_i.o \
	$(D)/mcapi/mcapi_msg_rcv.o \
	$(D)/mcapi/mcapi_msg_snd_i.o \
	$(D)/mcapi/mcapi_msg_snd.o \
	$(D)/mcapi/mcapi_open_pktchan_rcv_i.o \
	$(D)/mcapi/mcapi_open_pktchan_snd_i.o \
	$(D)/mcapi/mcapi_open_sclchan_rcv_i.o \
	$(D)/mcapi/mcapi_open_sclchan_snd_i.o \
	$(D)/mcapi/mcapi_pktchan_avail.o \
	$(D)/mcapi/mcapi_pktchan_free.o \
	$(D)/mcapi/mcapi_pktchan_rcv_close_i.o \
	$(D)/mcapi/mcapi_pktchan_rcv_i.o \
	$(D)/mcapi/mcapi_pktchan_rcv.o \
	$(D)/mcapi/mcapi_pktchan_snd_close_i.o \
	$(D)/mcapi/mcapi_pktchan_snd_i.o \
	$(D)/mcapi/mcapi_pktchan_snd.o \
	$(D)/mcapi/mcapi_sclchan_avail.o \
	$(D)/mcapi/mcapi_sclchan_rcv_close_i.o \
	$(D)/mcapi/mcapi_sclchan_rcv_u16.o \
	$(D)/mcapi/mcapi_sclchan_rcv_u32.o \
	$(D)/mcapi/mcapi_sclchan_rcv_u64.o \
	$(D)/mcapi/mcapi_sclchan_rcv_u8.o \
	$(D)/mcapi/mcapi_sclchan_snd_close_i.o \
	$(D)/mcapi/mcapi_sclchan_snd_u16.o \
	$(D)/mcapi/mcapi_sclchan_snd_u32.o \
	$(D)/mcapi/mcapi_sclchan_snd_u64.o \
	$(D)/mcapi/mcapi_sclchan_snd_u8.o \
	$(D)/mcapi/mcapi_set_endp_attrib.o \
	$(D)/mcapi/mcapi_test.o \
	$(D)/mcapi/mcapi_wait_any.o \
	$(D)/mcapi/mcapi_wait.o \
	$(D)/mcapi/msg_rcv.o \
	$(D)/mcapi/msg_snd.o \
	$(D)/mcapi/node_data.o \
	$(D)/mcapi/node.o \
	$(D)/mcapi/pkt_rcv.o \
	$(D)/mcapi/pkt_snd.o \
	$(D)/mcapi/queue.o \
	$(D)/mcapi/request.o \
	$(D)/mcapi/route.o \
	$(D)/mcapi/scal_rcv.o \
	$(D)/mcapi/scal_snd.o \
	$(D)/mcapi/suspend.o \
	$(D)/mcapi/mcapi_tls.o

LIB-OBJS-$(CONFIG_LINUX) += \
	$(D)/mcapi/linux/mcapi_os.o

LIB-SHMOBJS-y = \
	$(D)/shm/shm.o \

LIB-SHMOBJS-$(CONFIG_LINUX) += \
	$(D)/shm/linux/shm_os.o \

LIB-OBJS-$(CONFIG_SHM) += $(LIB-SHMOBJS-y)

LIB-DEPS = $(LIB-OBJS-y:.o=.d)
-include $(LIB-DEPS)


$(LIB-OBJS-y): %.o: %.c
	$(CC) $(LIB-CPPFLAGS) $(LIB-CFLAGS) -c $< -o $@


$(D)/libmcapi.a: $(LIB-OBJS-y)
	echo $(CONFIG_SHM)
	$(AR) $(ARFLAGS) $@ $?

TARGETS-y += $(D)/libmcapi.a

CLEAN += $(LIB-DEPS) $(LIB-OBJS-y)
