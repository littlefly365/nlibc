#	$NetBSD: Makefile,v 1.151.2.2 2026/05/06 17:18:04 martin Exp $
#
# NOTE: when changing ld.so, ensure that ldd still compiles.
#

# We are not building this with PIE
PIE_CFLAGS=
PIE_LDFLAGS=

PROG=		ld.elf_so

PREFIX?=	/usr
BINDIR=		${PREFIX}/libexec
LDFLAGS+=	-Wl,-Bsymbolic -shared -nostartfiles -nodefaultlibs
LDFLAGS+=	-Wl,-static
LDFLAGS+=	-Wl,--warn-shared-textrel
LDFLAGS+=	-Wl,--no-undefined
LDFLAGS+=	-Wl,-Map=${.TARGET}.map

COPTS+=		-fvisibility=hidden

SRCS+=		compat.c
SRCS+=		debug.c
SRCS+=		diagassert.c
SRCS+=		expand.c
SRCS+=		hash.c
SRCS+=		headers.c
SRCS+=		load.c
SRCS+=		map_object.c
SRCS+=		paths.c
SRCS+=		reloc.c
SRCS+=		rtld.c
SRCS+=		search.c
SRCS+=		symbol.c
SRCS+=		symver.c
SRCS+=		tls.c
SRCS+=		xmalloc.c
SRCS+=		xprintf.c
SRCS+=		mdreloc.c
SRCS+=		rtld_start.S

CPPFLAGS+=	-nostdinc
CPPFLAGS+=	-I../include
CPPFLAGS+=	-std=gnu11
CPPFLAGS+=	-DLIBDIR=\"${LIBDIR}\" -D_PATH_RTLD=\"${BINDIR}/${PROG}\"
CPPFLAGS+=	-I${.CURDIR} -I. -D_KERNTYPES
CPPFLAGS+=	-DRTLD_LOADER -D_LIBC_INTERNAL
CPPFLAGS+=	-DGNU_RELRO
CPPFLAGS+=	-D_RTLD_SOURCE
CPPFLAGS+=	-DHAVE_INITFINI_ARRAY
COPTS+=		-fno-stack-protector
COPTS+=		-O3
COPTS+=		-fomit-frame-pointer
COPTS+=		-mno-3dnow -mno-mmx -mno-sse -mno-sse2 -mno-sse3

LDADD+=		-nostdlib
LDADD+=		-Wl,--version-script=${.CURDIR}/symbols.map
LDADD+=		-L../libc
LDADD+=		-Wl,-e,.rtld_start
LDADD+=		-lc_pic
DPADD+=		../libc/libc_pic.a

.include <bsd.prog.mk>
