AC_INIT([openmcapi], [1.0], [thloh@altera.com])

dnl checking the target, for OS specific compilation
AC_CANONICAL_HOST
AC_ARG_VAR([CROSS_COMPILE], [ Sets the cross compiler for compiling Linux device driver ])
AC_SUBST([CROSS_COMPILE], $host_alias)
AC_ARG_VAR([ARCH], [ Sets the processor architecture for compiling Linux device driver ])

case $host_os in
  linux*)
	host_operating_system=linux
	;;
  *)
	host_operating_system=none
	AC_MSG_NOTICE([No platform detected])
	AS_IF([test "x$BAREMETAL_OS" = x], AC_MSG_ERROR([No operating system detected. Please use BAREMETAL_OS parameter to specify the operating system]))
	;;
esac

case $host_cpu in
  arm*)
	host_cpu=arm
	AC_SUBST([ARCH], [arm])
	;;
  nios*)
	host_cpu=nios2
	AC_SUBST([ARCH], [nios2])
	;;
  *)
	AC_MSG_ERROR([No known CPU detected])
	;;

#case $host in
 # *)
#	CROSS_COMPILE=$host
#	;;
esac

AC_ARG_VAR([BAREMETAL_OS], [ Baremetal operating system ])

AM_CONDITIONAL([CPU_ARM], [test x$host_cpu = xarm])
AM_CONDITIONAL([OS_UCOSII], [test x$BAREMETAL_OS = xucosii])
AM_CONDITIONAL([OS_LINUX], [test x$host_operating_system = xlinux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_ARG_VAR([SYSV], [ Debugging mode. ])
AM_CONDITIONAL([OS_SYSV], [test x$SYSV != x])

dnl setup the argument of the configurable parameters
AC_ARG_VAR([MCAPI_MAX_DATA_LEN], [ Maximum length of MCAPI endpoint ])
AS_IF([test "x$MCAPI_MAX_DATA_LEN" = x], AC_DEFINE([MCAPI_MAX_DATA_LEN], [1024], [Max1]))
AS_IF([test "x$MCAPI_MAX_DATA_LEN" != x], AC_DEFINE_UNQUOTED([MCAPI_MAX_DATA_LEN], [$MCAPI_MAX_DATA_LEN], [Max1]))

AC_ARG_VAR([MCAPI_MAX_ENDPOINTS], [ Maximum number of MCAPI endpoint ])
AS_IF([test "x$MCAPI_MAX_ENDPOINTS" = x], AC_DEFINE([MCAPI_MAX_ENDPOINTS], [4], [] ))
AS_IF([test "x$MCAPI_MAX_ENDPOINTS" != x], AC_DEFINE_UNQUOTED([MCAPI_MAX_ENDPOINTS], [$MCAPI_MAX_ENDPOINTS], [] ))

AC_ARG_VAR([CONFIG_SHM_NR_NODES], [ Number of SHM Nodes ])
AS_IF([test "x$CONFIG_SHM_NR_NODES" = x], AC_DEFINE([CONFIG_SHM_NR_NODES], [2], [] ))
AS_IF([test "x$CONFIG_SHM_NR_NODES" != x], AC_DEFINE_UNQUOTED([CONFIG_SHM_NR_NODES], [$CONFIG_SHM_NR_NODES], [] ))

AC_ARG_VAR([CONFIG_SHM], [ Shared memory channel ])
AS_IF([test "x$CONFIG_SHM" = x], AC_DEFINE([CONFIG_SHM], [1], [] ))
AS_IF([test "x$CONFIG_SHM" != x], AC_DEFINE_UNQUOTED([CONFIG_SHM], [$CONFIG_SHM], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_MODE_INT], [ ucosii MCAPI Mcomm mode int ])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_MODE_INT" = x], AC_DEFINE([UCOSII_MCAPI_MCOMM_MODE_INT], [0], [] ))
AS_IF([test "x$UCOSII_MCAPI_MCOMM_MODE_INT" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_MODE_INT], [$UCOSII_MCAPI_MCOMM_MODE_INT], [] ))

AC_ARG_VAR([ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE], [ ucosii to HPS DDR ASE base address ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE" = x],
		[AC_MSG_FAILURE([ Please set ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE to HPS DDR ASE mapping base address for MCAPI in UC/OS-II])
		])
])
AS_IF([test "x$ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE" != x], AC_DEFINE_UNQUOTED([ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE], [$ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_PHYS_BASE], [ ucosii physical base address ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_MCOMM_PHYS_BASE" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_PHYS_BASE to physical base address for MCAPI shared memory region in UC/OS-II])
		])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_PHYS_BASE" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_PHYS_BASE], [$UCOSII_MCAPI_MCOMM_PHYS_BASE], [] ))

AC_ARG_VAR([UCOSII_MCAPI_INIT_LOCK], [ Mutex instance name to be used as initialization lock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_INIT_LOCK" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_INIT_LOCK to the mutex instance name to be used as initialization lock])
		])
])
AS_IF([test "x$UCOSII_MCAPI_INIT_LOCK" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_INIT_LOCK], ["$UCOSII_MCAPI_INIT_LOCK"], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_DESQ_LOCK0], [ Mutex instance name to be used as descriptor queuelock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_MCOMM_DESQ_LOCK0" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_DESQ_LOCK0 to the mutex instance name to be used as descriptor queue lock])
		])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_DESQ_LOCK0" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_DESQ_LOCK0], ["$UCOSII_MCAPI_MCOMM_DESQ_LOCK0"], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_DESQ_LOCK1], [ Mutex instance name to be used as descriptor queuelock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
        [],
        [AS_IF([test "x$UCOSII_MCAPI_MCOMM_DESQ_LOCK1" = x],
                [AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_DESQ_LOCK1 to the mutex instance name to be used as descriptor queue lock])
                ])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_DESQ_LOCK1" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_DESQ_LOCK1], ["$UCOSII_MCAPI_MCOMM_DESQ_LOCK1"], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_BUFQ_LOCK], [ Mutex instance name to be used as initialization lock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_MCOMM_BUFQ_LOCK" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_BUFQ_LOCK to the mutex instance name to be used as buffer queue lock])
		])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_BUFQ_LOCK" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_BUFQ_LOCK], ["$UCOSII_MCAPI_MCOMM_BUFQ_LOCK"], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_MBOX_TX], [ Mutex instance name to be used as initialization lock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_MCOMM_MBOX_TX" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_MBOX_TX to the mutex instance name to be used as message sender])
		])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_MBOX_TX" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_MBOX_TX], ["$UCOSII_MCAPI_MCOMM_MBOX_TX"], [] ))

AC_ARG_VAR([UCOSII_MCAPI_MCOMM_MBOX_RX], [ Mutex instance name to be used as initialization lock in MCAPI library ])
AS_IF([test "x$BAREMETAL_OS" != xucosii],
	[],
	[AS_IF([test "x$UCOSII_MCAPI_MCOMM_MBOX_RX" = x],
		[AC_MSG_FAILURE([ Please set UCOSII_MCAPI_MCOMM_MBOX_RX to the mutex instance name to be used as message sender])
		])
])
AS_IF([test "x$UCOSII_MCAPI_MCOMM_MBOX_RX" != x], AC_DEFINE_UNQUOTED([UCOSII_MCAPI_MCOMM_MBOX_RX], ["$UCOSII_MCAPI_MCOMM_MBOX_RX"], [] ))

AH_TEMPLATE([CONFIG_ARM], [Defined if the platform is ARM])
AS_IF([test "x$host_cpu" = xarm], AC_DEFINE([CONFIG_ARM], [1], []))
AH_TEMPLATE([CONFIG_NIOS2], [Defined if the platform is NIOS-II])
AS_IF([test "x$host_cpu" = xnios2], AC_DEFINE([CONFIG_NIOS2], [1], []))
AH_TEMPLATE([CONFIG_LINUX], [Defined if the OS is Linux])
AS_IF([test "x$host_operating_system" = xlinux], AC_DEFINE([CONFIG_LINUX], [1], []))
AH_TEMPLATE([CONFIG_UCOSII], [Defined if the OS is micro C/OS-II])
AS_IF([test "x$BAREMETAL_OS" = xucosii], AC_DEFINE([CONFIG_UCOSII], [1], []))

AC_ARG_VAR([KERNELDIR], [ Sets kernel directory, only valid for Linux operating system])
AC_SUBST([KERNELDIR])


#AC_PROG_CC(nios2-elf-gcc)
#AC_PROG_CXX(nios2-elf-g++)

AC_PROG_CC
#AM_PROG_AR
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile libmcapi/Makefile demo/Makefile test/Makefile])
AC_OUTPUT

