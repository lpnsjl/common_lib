//
// Created by andrew on 2023/6/18.
// 定义读写屏障宏
//

#ifndef BARRIER_H
#define BARRIER_H
#if defined  __aarch64__
#define rte_compiler_barrier()
#elif defined __x86_64__
#define	rte_compiler_barrier() do {		\
	asm volatile ("" : : : "memory");	\
} while(0)
#define rte_smp_wmb() rte_compiler_barrier()
#define rte_smp_rmb() rte_compiler_barrier()
#define rte_smp_mb() asm volatile("lock addl $0, -128(%%rsp); " ::: "memory");
#elif defined __arm__
#define rte_compiler_barrier()
#endif

// 强制对齐
#define rte_aligned(a) __attribute__((__aligned__(a)))

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

#endif //BARRIER_H
