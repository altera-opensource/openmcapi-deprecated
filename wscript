#!/usr/bin/env python

import platform

top = '.'
out = 'build'

subdirs = [
	'libmcapi',
	'test',
	'util',
	]

def getarch():
	classes = {
		'i386': 'x86',
		'i586': 'x86',
		'i686': 'x86',
		'ppc': 'powerpc',
	}

	arch = platform.machine()
	return classes.get(arch, arch)

def options(opt):
	opt.load('compiler_c')
	opt.add_option('--arch', default=getarch())
	opt.add_option('--os', default='linux')
	opt.add_option('--transport', default='shm', help='Transport driver, e.g. \'shm\' for shared memory')
	opt.add_option('--cross', default='', help='Cross compiler prefix, e.g. powerpc-linux-gnu-')
	opt.add_option('--cc', default='gcc')
	opt.add_option('--no-kmods', action='store_true', help='Don\'t build Linux kernel modules')

	opt.recurse(subdirs)

def build(bld):
	bld.recurse(subdirs)

def configure(conf):
	conf.env.ARCH = conf.options.arch
	conf.define('CONFIG_%s' % conf.env.ARCH.upper(), 1)

	conf.env.OS = conf.options.os
	conf.define('CONFIG_%s' % conf.env.OS.upper(), 1)

	conf.env.TRANSPORT = conf.options.transport
	conf.define('CONFIG_%s' % conf.env.TRANSPORT.upper(), 1)

	conf.env.CROSS = conf.options.cross
	conf.env.CC = conf.env.CROSS + conf.options.cc

	conf.load('compiler_c')
	# compiler_c checks if CC is a GCC or not, and tells us in COMPILER_CC
	conf.define('CONFIG_%s' % conf.env.COMPILER_CC.upper(), 1)

	conf.env.NO_KMODS = conf.options.no_kmods

	conf.recurse(subdirs)
