
# tests are allowed to access openmcapi internals
TEST-CPPFLAGS-y = -MD
TEST-CPPFLAGS-y += \
	-I include \
	-I test \
	-I . \
	-I libmcapi/include
TEST-CPPFLAGS-$(CONFIG_LINUX) += \
	-I include/linux \
	-I test/support_suite/linux

TEST-CFLAGS-y = -O2

DEMO-CPPFLAGS-y = -MD
DEMO-CPPFLAGS-y += \
	-I include \
	-I test \
	-I . \
	-I libmcapi/include
DEMO-CPPFLAGS-$(CONFIG_LINUX) += \
	-I include/linux \
	-I test/support_suite/linux

DEMO-CFLAGS-y = -O2



TEST-OBJS-API = \
	test/3/mcapi_tests.o

TEST-OBJS-FUNC = \
	test/1/fts_main.o \
	test/1/fts_mcapi_cancel.o \
	test/1/fts_mcapi_connect_pktchan_i.o \
	test/1/fts_mcapi_connect_sclchan_i.o \
	test/1/fts_mcapi_create_endpoint.o \
	test/1/fts_mcapi_delete_endpoint.o \
	test/1/fts_mcapi_get_endpoint.o \
	test/1/fts_mcapi_get_endpoint_attribute.o \
	test/1/fts_mcapi_get_endpoint_i.o \
	test/1/fts_mcapi_msg_available.o \
	test/1/fts_mcapi_msg_recv.o \
	test/1/fts_mcapi_msg_recv_i.o \
	test/1/fts_mcapi_msg_send.o \
	test/1/fts_mcapi_msg_send_i.o \
	test/1/fts_mcapi_open_pktchan_recv_i.o \
	test/1/fts_mcapi_open_pktchan_send_i.o \
	test/1/fts_mcapi_open_sclchan_recv_i.o \
	test/1/fts_mcapi_open_sclchan_send_i.o \
	test/1/fts_mcapi_pktchan_available.o \
	test/1/fts_mcapi_pktchan_free.o \
	test/1/fts_mcapi_pktchan_recv.o \
	test/1/fts_mcapi_pktchan_recv_close_i.o \
	test/1/fts_mcapi_pktchan_recv_i.o \
	test/1/fts_mcapi_pktchan_send.o \
	test/1/fts_mcapi_pktchan_send_close_i.o \
	test/1/fts_mcapi_pktchan_send_i.o \
	test/1/fts_mcapi_sclchan_available.o \
	test/1/fts_mcapi_sclchan_recv_close_i.o \
	test/1/fts_mcapi_sclchan_recv_x.o \
	test/1/fts_mcapi_sclchan_send_close_i.o \
	test/1/fts_mcapi_sclchan_send_x.o \
	test/1/fts_mcapi_set_endpoint_attribute.o \
	test/1/fts_mcapi_test.o \
	test/1/fts_mcapi_wait.o \
	test/1/fts_mcapi_wait_any.o

DEMO-OBJS = \
	test/default_demo/client_server_demo.o \
	test/default_demo/demo_msg_client.o \
	test/default_demo/demo_msg_server.o \
	test/default_demo/demo_pkt_client.o \
	test/default_demo/demo_pkt_server.o \
	test/default_demo/demo_scl_client.o \
	test/default_demo/demo_scl_server.o

TEST-OBJS-SUPPORT-y = \
	test/support_suite/create_svc.o \
	test/support_suite/destroy_svc.o \
	test/support_suite/reg_svcs.o

TEST-OBJS-SUPPORT-$(CONFIG_LINUX) += \
	test/support_suite/linux/os_linux_demo.o

TEST-OBJS-MGMT = \
	test/mgmt_svc.o

TEST-OBJS-ALL = \
	$(TEST-OBJS-FUNC) \
	$(TEST-OBJS-API) \
	$(TEST-OBJS-PORT) \
	$(TEST-OBJS-SUPPORT-y) \
	$(TEST-OBJS-MGMT)

TEST-DEPS-ALL = $(TEST-OBJS-ALL:.o=.d)
-include $(TEST-DEPS-ALL)

$(TEST-OBJS-ALL): %.o: %.c
	$(CC) $(TEST-CPPFLAGS-y) $(TEST-CFLAGS-y) -c $< -o $@


DEMO-DEPS = $(DEMO-OBJS:.o=.d)
-include $(DEMO-DEPS)

$(DEMO-OBJS) : %.o: %.c
	$(CC) $(DEMO-CPPFLAGS-y) $(DEMO-CFLAGS-y) -c $< -o $@



test/api_suite: $(TEST-OBJS-API) $(TEST-OBJS-PORT) $(TEST-OBJS-SUPPORT-y) libmcapi/libmcapi.a
	$(CC) $^ -lpthread -lrt -o $@

test/func_suite: $(TEST-OBJS-FUNC) $(TEST-OBJS-SUPPORT-y) $(TEST-OBJS-MGMT) libmcapi/libmcapi.a
	$(CC) $^ -lpthread -lrt -o $@

test/demo: $(DEMO-OBJS) $(TEST-OBJS-SUPPORT-y) libmcapi/libmcapi.a
	$(CC) $^ -lpthread -lrt -o $@

TARGETS-y += test/api_suite test/func_suite test/demo
CLEAN += $(TEST-DEPS-ALL) $(TEST-OBJS-ALL) $(DEMO-OBJS) $(DEMO-DEPS)
