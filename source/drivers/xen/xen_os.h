#ifndef XEN_OS_H_
#define XEN_OS_H_

#include <stdint.h>

/* DOMID_SELF is used in certain contexts to refer to oneself. */
#define DOMID_SELF (0x7FF0U)

#define PAGE_SHIFT 12
static inline uintptr_t addr_to_pfn(uintptr_t va) { return va >> PAGE_SHIFT; }
static inline uintptr_t pfn_to_addr(uintptr_t va) { return va << PAGE_SHIFT; }

#define XEN_ASSERT(x)                                                          \
    do                                                                         \
    {                                                                          \
        if (!(x))                                                              \
        {                                                                      \
            char buf[128];                                                     \
            snprintf(buf, sizeof(buf), "ASSERTION FAILED: %s at %s:%d.\n", #x, \
                     __FILE__, __LINE__);                                      \
            Xen_printkXen(buf, strlen(buf));                                   \
        }                                                                      \
    } while (0)

#define ADDR (*(volatile long *)addr)

/* We probably only need "dmb" here, but we'll start by being paranoid. */
#define mb() __asm__("dsb sy" ::: "memory");
#define rmb() __asm__("dsb ld" ::: "memory");
#define wmb() __asm__("dsb st" ::: "memory");

#define barrier() __asm__ __volatile__("" : : : "memory")

/**
 * Test whether a bit is set. */
static __inline__ int test_bit(int nr, const volatile unsigned long *addr)
{
    const uint8_t *ptr = (const uint8_t *)addr;
    return ((1 << (nr & 7)) & (ptr[nr >> 3])) != 0;
}

/* As test_and_clear_bit, but using __ATOMIC_SEQ_CST */
static __inline__ int synch_test_and_clear_bit(int nr, volatile void *addr)
{
    uint8_t *byte = ((uint8_t *)addr) + (nr >> 3);
    uint8_t bit = 1 << (nr & 7);
    uint8_t orig;

    orig = __atomic_fetch_and(byte, ~bit, __ATOMIC_SEQ_CST);

    return (orig & bit) != 0;
}

/* As test_and_set_bit, but using __ATOMIC_SEQ_CST */
static __inline__ int synch_test_and_set_bit(int nr, volatile void *base)
{
    uint8_t *byte = ((uint8_t *)base) + (nr >> 3);
    uint8_t bit = 1 << (nr & 7);
    uint8_t orig;

    orig = __atomic_fetch_or(byte, bit, __ATOMIC_SEQ_CST);

    return (orig & bit) != 0;
}

/* As clear_bit, but using __ATOMIC_SEQ_CST */
static __inline__ void synch_clear_bit(int nr, volatile void *addr)
{
    synch_test_and_clear_bit(nr, addr);
}

/* As test_bit, but with a following memory barrier. */
static __inline__ int synch_test_bit(int nr, volatile void *addr)
{
    int result;
    result = test_bit(nr, addr);
    barrier();
    return result;
}

#endif /* XEN_OS_H_ */
