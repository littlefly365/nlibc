#	$NetBSD: Makefile,v 1.177 2026/10/04 15:24:07 mlelstv Exp $
#	@(#)Makefile	8.2 (Berkeley) 2/3/94
#
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, delete -DLIBC_SCCS and -DSYSLIBC_SCCS
# from CPPFLAGS below.  To remove these strings from just the system call
# stubs, remove just -DSYSLIBC_SCCS from CPPFLAGS.
#
# The NLS (message catalog) functions are always in libc.  To choose that
# strerror(), perror(), strsignal(), psignal(), etc. actually call the NLS
# functions, put -DNLS on the CPPFLAGS line below.
#
# The YP functions are always in libc. To choose that getpwent() and friends
# actually call the YP functions, put -DYP on the CPPFLAGS line below.
#
# The Hesiod functions are always in libc. To choose that getpwent() and friends
# actually call the Hesiod functions, put -DHESIOD on the CPPFLAGS line below.
LIB=c
INCS=empty.h	# if there's not any header the installation fails

LIBCDIR=${.CURDIR}
MACHINE_CPU ?= ${MACHINE_ARCH}
ARCHSUBDIR = ${MACHINE_ARCH}
ARCHDIR = ${.CURDIR}/arch/${ARCHSUBDIR}

NETBSDSRCDIR=${.CURDIR}
LIBCDIR=${NETBSDSRCDIR}
CPPFLAGS+=-ffreestanding -nostdinc -nostdlib
CPPFLAGS+=-I${.CURDIR}/include -I${.CURDIR}/../include -I${.CURDIR}/locale -I${.CURDIR}/citrus \
	-I${.CURDIR}/gen -I${.CURDIR}/stdlib -I${.CURDIR}/../csu/common -I${.CURDIR} \
	-I${.CURDIR}/../ld.elf_so -I${ARCHDIR}
CPPFLAGS+=-D_LIBC -DLIBC_SCCS -DSYSLIBC_SCCS -D_REENTRANT -D__ELF__
CPPFLAGS+=-D_LIBC_INTERNAL -D__NetBSD__ -DNLS -DYP -DHESIOD

CPPFLAGS+=-fPIC -std=gnu11
LDFLAGS+=-ffreestanding -nostdlib
CFLAGS+=-fno-stack-protector
AFLAGS+=	-I${ARCHDIR}

MKLINT=no
USE_INET6=yes
MKHESIOD=yes
RUMPRUN=no
MKYP=yes
MKMAN=yes
MKPIC=no
BUILD_LEGACY?=no

.if "${BUILD_LEGACY}" == "yes"
SUBDIR=compat
.include <bsd.subdir.mk>
.else
COMPATDIR=${.CURDIR}/compat
.include "${.CURDIR}/compat/Makefile.inc"
# Marker for compat code that can't be easily isolated
CPPFLAGS+=	-D__BUILD_LEGACY
.endif

.PATH: ${.CURDIR}/include
.if exists (${ARCHDIR}/Makefile.inc)
.PATH:	${ARCHDIR}
.include "${ARCHDIR}/Makefile.inc"
.endif

.include "${.CURDIR}/common/lib/libc/Makefile.inc"
.include "${.CURDIR}/atomic/Makefile.inc"
.include "${.CURDIR}/cdb/Makefile.inc"
.include "${.CURDIR}/db/Makefile.inc"
.include "${.CURDIR}/citrus/Makefile.inc"
.include "${.CURDIR}/compat-43/Makefile.inc"
#.include "${.CURDIR}/compiler_rt/Makefile.inc"
.include "${.CURDIR}/dlfcn/Makefile.inc"
.include "${.CURDIR}/gdtoa/Makefile.inc"
.include "${.CURDIR}/gen/Makefile.inc"
.include "${.CURDIR}/gmon/Makefile.inc"
.include "${.CURDIR}/hash/Makefile.inc"
.include "${.CURDIR}/iconv/Makefile.inc"
.include "${.CURDIR}/inet/Makefile.inc"
.include "${.CURDIR}/isc/Makefile.inc"
.include "${.CURDIR}/locale/Makefile.inc"
.include "${.CURDIR}/md/Makefile.inc"
.include "${.CURDIR}/misc/Makefile.inc"
.include "${.CURDIR}/net/Makefile.inc"
.include "${.CURDIR}/nameser/Makefile.inc"
.include "${.CURDIR}/nls/Makefile.inc"
#.include "${.CURDIR}/posix1e/Makefile.inc"
.include "${.CURDIR}/regex/Makefile.inc"
.include "${.CURDIR}/resolv/Makefile.inc"
.include "${.CURDIR}/rpc/Makefile.inc"
.include "${.CURDIR}/ssp/Makefile.inc"
.include "${.CURDIR}/stdio/Makefile.inc"
.include "${.CURDIR}/stdlib/Makefile.inc"
.include "${.CURDIR}/string/Makefile.inc"
.include "${.CURDIR}/termios/Makefile.inc"
.include "${.CURDIR}/thread-stub/Makefile.inc"
.include "${.CURDIR}/time/Makefile.inc"
.if ${RUMPRUN} != "yes"
.include "${.CURDIR}/tls/Makefile.inc"
.endif
.include "${.CURDIR}/sys/Makefile.inc"
#.if ${HAVE_LIBGCC_EH} == "no"
#.include "${NETBSDSRCDIR}/sys/lib/libunwind/Makefile.inc"
#.endif
.include "${.CURDIR}/uuid/Makefile.inc"
.if (${MKYP} != "no")
.include "${.CURDIR}/yp/Makefile.inc"
.endif
.include "${.CURDIR}/linux/Makefile.inc"

# Remove from SRCS the .c files for any .S files added by the MD makefiles,
# also remove from SRCS the .c files for the .S and .c files in NO_SRCS.
# Add the .c file for .S files (in both variables) to LSRCS so that the
# 'normal' .c file for assembly files is used for the lint librray.
#
# Usage:
# Add .S files to NO_SRCS when another .S file provides the entry points.
# Add .c files to NO_SRCS when another .c file provides the entry points.
# (lint is run on all .c files in SRCS)

.for check_file in ${SRCS:M*.S} ${NO_SRCS}
unwanted_file := ${SRCS:M${check_file:.S=.c}}
.if "${unwanted_file}" != ""
SRCS := ${SRCS:N${unwanted_file}}
.if "${unwanted_file}" != "${check_file}"
LSRCS := ${LSRCS} ${unwanted_file}
.endif
.endif
.endfor

# Tell ctype(3) that this is a dynamic libc, so if appropriate it
# should allocate a guard page.
CSHLIBFLAGS+=	-D_CTYPE_DYNAMIC

.include <bsd.lib.mk>

# force the dynamic linker to initialize libc first
SHLIB_SHFLAGS+=	-Wl,-z,initfirst
