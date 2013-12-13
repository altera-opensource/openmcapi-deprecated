if OS_LINUX
bin_PROGRAMS = demo
demo_SOURCES = linux_init.c hi.c
demo_LDADD = ../libmcapi/libopenmcapi.a

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/libmcapi/include
AM_CPPFLAGS += -I$(top_srcdir)/include/linux
AM_LDFLAGS = -lrt -lpthread
endif
