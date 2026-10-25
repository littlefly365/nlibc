#include <stdarg.h>

long
__raw_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	long r;
	va_list ap;

	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;

	__asm__ __volatile__ (  "syscall" : "=a" (r) : "a"(n), "D"(a1),
				"S"(a2), "d"(a3), "r"(r10), "r"(r8),
				"r"(r9) : "rcx", "r11", "memory");
	return r;
}
