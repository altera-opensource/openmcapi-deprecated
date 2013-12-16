if OS_LINUX
check_PROGRAMS = unit_test
unit_test_SOURCES = 3/mcapi_tests.c \
	support_suite/create_svc.c \
	support_suite/destroy_svc.c \
	support_suite/reg_svcs.c \
	support_suite/linux/os_linux_demo.c

unit_test_LDADD = ../libmcapi/libopenmcapi.a

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/libmcapi/include -I$(top_srcdir)/test/support_suite/linux
AM_CPPFLAGS += -I$(top_srcdir)/include/linux
AM_LDFLAGS = -lrt -lpthread

bin_PROGRAMS = func_frontend func_backend api_suite
api_suite_SOURCES = 3/mcapi_tests.c \
		support_suite/linux/os_linux_demo.c

func_frontend_SOURCES = func/frontend.c \
                func/fts_mcapi_cancel.c \
                func/fts_mcapi_connect_pktchan_i.c \
                func/fts_mcapi_connect_sclchan_i.c \
                func/fts_mcapi_create_endpoint.c \
                func/fts_mcapi_delete_endpoint.c \
                func/fts_mcapi_get_endpoint.c \
                func/fts_mcapi_get_endpoint_attribute.c \
                func/fts_mcapi_get_endpoint_i.c \
                func/fts_mcapi_msg_available.c \
                func/fts_mcapi_msg_recv.c \
                func/fts_mcapi_msg_recv_i.c \
                func/fts_mcapi_msg_send.c \
                func/fts_mcapi_msg_send_i.c \
                func/fts_mcapi_open_pktchan_recv_i.c \
                func/fts_mcapi_open_pktchan_send_i.c \
                func/fts_mcapi_open_sclchan_recv_i.c \
                func/fts_mcapi_open_sclchan_send_i.c \
                func/fts_mcapi_pktchan_available.c \
                func/fts_mcapi_pktchan_free.c \
                func/fts_mcapi_pktchan_recv.c \
                func/fts_mcapi_pktchan_recv_close_i.c \
                func/fts_mcapi_pktchan_recv_i.c \
                func/fts_mcapi_pktchan_send.c \
                func/fts_mcapi_pktchan_send_close_i.c \
                func/fts_mcapi_pktchan_send_i.c \
                func/fts_mcapi_sclchan_available.c \
                func/fts_mcapi_sclchan_recv_close_i.c \
                func/fts_mcapi_sclchan_recv_x.c \
                func/fts_mcapi_sclchan_send_close_i.c \
                func/fts_mcapi_sclchan_send_x.c \
                func/fts_mcapi_set_endpoint_attribute.c \
                func/fts_mcapi_test.c \
                func/fts_mcapi_wait.c \
                func/fts_mcapi_wait_any.c \
		mgmt_svc.c \
		support_suite/create_svc.c \
		support_suite/destroy_svc.c \
		support_suite/reg_svcs.c \
		support_suite/linux/os_linux_demo.c

func_backend_SOURCES = func/backend.c \
		mgmt_svc.c \
		support_suite/create_svc.c \
		support_suite/destroy_svc.c \
		support_suite/reg_svcs.c \
		support_suite/linux/os_linux_demo.c

func_backend_LDADD = ../libmcapi/libopenmcapi.a
func_frontend_LDADD = ../libmcapi/libopenmcapi.a
api_suite_LDADD = ../libmcapi/libopenmcapi.a

endif
