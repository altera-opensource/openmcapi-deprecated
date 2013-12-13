mcapiincludedir = $(includedir)/mcapi
mcapiinclude_HEADERS = \
	include/mcapi.h \
	include/openmcapi_cfg.h \
	libmcapi/include/openmcapi.h
if OS_LINUX
mcapiinclude_HEADERS += include/linux/mcapi_os.h
endif

if OS_UCOSII
mcapiinclude_HEADERS += include/ucosii/mcapi_os.h
endif


SUBDIRS = libmcapi demo test util
