#!/usr/bin/env python

import platform

top = '.'
out = 'build'

subdirs = [
	'libmcapi',
	'test',
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
	opt.add_option('--transport', default='shm')
	opt.add_option('--cross-cc', default='gcc')

def build(bld):
	bld.recurse(subdirs)

def configure(conf):
	conf.recurse(subdirs)

	conf.env.ARCH = conf.options.arch
	conf.define('CONFIG_%s' % conf.env.ARCH.upper(), 1)

	conf.env.OS = conf.options.os
	conf.define('CONFIG_%s' % conf.env.OS.upper(), 1)

	conf.env.TRANSPORT = conf.options.transport
	conf.define('CONFIG_%s' % conf.env.TRANSPORT.upper(), 1)

	conf.env.CC = conf.options.cross_cc
	conf.load('compiler_c')
	# compiler_c checks if CC is a GCC or not, and tells us in COMPILER_CC
	conf.define('CONFIG_%s' % conf.env.COMPILER_CC.upper(), 1)
