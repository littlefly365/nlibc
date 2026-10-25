/*    $nlibc: open.c,v 1.0 2026/10/11 11:47:10 littlefly365 Exp $    */

/*
 * Copyright (c) 2026, littlefly365
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$nlibc: open.c,v 1.0 2026/10/11 11:47:10 littlefly365 Exp $");
#endif /* LIBC_SCCS and not lint */

#include <sys/syscall.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

#define NEED_MODE(flags) (((flags) & O_CREAT) || (((flags) & O_TMPFILE) == O_TMPFILE))

int
openat(int fd, const char *path, int flags, ...)
{
	va_list ap;
	mode_t mode;

	flags |= O_LARGEFILE;

	if (NEED_MODE(flags)) {
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);

		return syscall(SYS_openat, fd, path, flags, mode);
        }

	return syscall(SYS_openat, fd, path, flags);
}

int
open(const char *path, int flags, ...)
{
	va_list ap;
	mode_t mode;

	if (NEED_MODE(flags)) {
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);

		return openat(AT_FDCWD, path, flags, mode);
	}

	return openat(AT_FDCWD, path, flags);
}
