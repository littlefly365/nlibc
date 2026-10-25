/*    $nlibc: link.c,v 1.0 2026/10/18 16:43:05 littlefly365 Exp $    */

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
__RCSID("$nlibc: link.c,v 1.0 2026/10/18 16:43:05 littlefly365 Exp $");
#endif /* LIBC_SCCS and not lint */

#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef __weak_alias
__weak_alias(readlink, _readlink);
#endif

int
link(const char *oldpath, const char *newpath)
{
	return linkat(AT_FDCWD, oldpath, AT_FDCWD, newpath, 0);
}

int
unlink(const char *path)
{
	return syscall(SYS_unlink, path);
}

int
symlink(const char *oldpath, const char *newpath)
{
	return symlinkat(oldpath, AT_FDCWD, newpath);
}

ssize_t
_readlink(const char *path, char *buf, size_t len)
{
	return readlinkat(AT_FDCWD, path, buf, len);
}

int
linkat(int oldfd, const char *oldpath, int newfd, const char *newpath, int flag)
{
	return syscall(SYS_linkat, oldfd, oldpath, newfd, newpath, flag);
}

int
unlinkat(int fd, const char *path, int flag)
{
	return syscall(SYS_unlinkat, fd, path, flag);
}

int
symlinkat(const char *oldpath, int fd, const char *newpath)
{
	return syscall(SYS_symlinkat, oldpath, fd, newpath);
}

ssize_t
readlinkat(int fd, const char *path, char *buf, size_t len)
{
	return syscall(SYS_readlinkat, fd, path, buf, len);
}
