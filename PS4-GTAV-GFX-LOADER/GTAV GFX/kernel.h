#pragma once

#include "types.h"

#define __Xfast_syscall							0x1C0
#define __copyin								0x1EA710
#define __copyout								0x1EA630
#define __printf								0x436040
#define __vprintf								0x4360B0
#define __malloc								0x10E250
#define __free									0x10E460

static inline __attribute__((always_inline)) uint64_t __readmsr(uint32_t __register) {
	uint32_t __edx, __eax;

	__asm__ volatile (
	    "rdmsr"
	    : "=d"(__edx),
	    "=a"(__eax)
	    : "c"(__register)
	);

	return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

static inline uint64_t getkernbase() {
	return __readmsr(0xC0000082) - __Xfast_syscall;
}
