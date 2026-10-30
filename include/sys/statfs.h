/*    $nlibc: statfs.c,v 1.0 2026/10/11 11:47:10 littlefly365 Exp $    */

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

#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H

#include <sys/cdefs.h>
#include <sys/fstypes.h>

struct statfs {
	unsigned long	f_type;
	unsigned long	f_bsize;
	fsblkcnt_t	f_blocks;
	fsblkcnt_t	f_bfree;
	fsblkcnt_t	f_bavail;
	fsfilcnt_t	f_files;
	fsfilcnt_t	f_ffree;
	fsid_t		f_sid;
	unsigned long	f_namelen;
	unsigned long	f_frsize;
	unsigned long	f_flags;
	unsigned long	f_fspare[4];
};

__BEGIN_DECLS
int statfs(const char *, struct statfs *) __RENAME(linux_statfs);
int fstatfs(int, struct statfs *) __RENAME(linux_fstatfs);
__END_DECLS

#endif /* !_SYS_STATFS_H */
