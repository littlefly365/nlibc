/*    $nlibc: brk.c,v 1.0 2026/10/11 11:47:10 littlefly365 Exp $    */

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
__RCSID("$nlibc: brk.c,v 1.0 2026/10/11 11:47:10 littlefly365 Exp $");
#endif /* LIBC_SCCS and not lint */

#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>

#ifdef __weak_alias
__weak_alias(sbrk, _sbrk);
__weak_alias(brk, _brk);
#endif

extern char _end;
void *__minbrk = &_end;
void *__curbrk __attribute__((visibility("hidden")));

void *
_sbrk(intptr_t increment)
{
	void *oldbrk;

	if (__curbrk == NULL) {
		if (brk(NULL) < 0)
			return (void*)-1;
	}

	if (increment == 0)
		return __curbrk;

	oldbrk = __curbrk;

	if (brk(oldbrk + increment) < 0)
		return (void*)-1;

	return oldbrk;
}

int
_brk(void *addr)
{
	void *newbrk;

	if (addr != NULL && addr < __minbrk)
		addr = __minbrk;

	newbrk = (void*)syscall(SYS_brk, addr);

	if (addr != NULL && newbrk < addr) {
		errno = ENOMEM;
		return -1;
	}

	__curbrk = newbrk;
	return 0;
}
