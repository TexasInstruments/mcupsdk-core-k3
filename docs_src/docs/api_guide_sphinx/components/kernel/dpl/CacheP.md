
# Cache
## Features Supported

- APIs to perform below cache operations
  - region based writeback
  - region based invalidate
  - region based writeback invalidate
  - enable and disable APIs for I cache and D cache
  - full cache writeback, write invalidte

::::{only} SOC_AM64X

- CPUs supported,
  - R5F, A53
  - M4F, blank implementation since no cache on M4F

::::

::::{only} SOC_AM243X

- CPUs supported,
  - R5F
  - M4F, blank implementation since no cache on M4F

::::

## Features NOT Supported

NA


## Important Usage Guidelines

- The region based cache APIs, [CacheP_wb](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_wbInv](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_inv](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), operate on a CPU cache line, hence its strongly recommended to
  make sure 'addr' is cache line aliged and 'size` is a multiple of cache line size
  - Start address is calculated as follows, start_addr = floor(addr, CPU_CACHE_LINE)
  - End address is calculated as follows, end_addr = ceil(addr + size, CPU_CACHE_LINE)
  - No error is returned, for unaligned addr and size
- On R5F,
  - Valid values for [CacheP_Type](../../../../../_api/group/group__KERNEL__DPL__CACHE.html) for [CacheP_enable](../../../../../_api/group/group__KERNEL__DPL__CACHE.html) and [CacheP_disable](../../../../../_api/group/group__KERNEL__DPL__CACHE.html) are [CacheP_TYPE_L1D](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_TYPE_L1P](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_TYPE_ALL](../../../../../_api/group/group__KERNEL__DPL__CACHE.html)
  - Valid values for [CacheP_Type](../../../../../_api/group/group__KERNEL__DPL__CACHE.html) for [CacheP_wb](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_wbInv](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_inv](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_wbAll](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_wbInvAll](../../../../../_api/group/group__KERNEL__DPL__CACHE.html)  are [CacheP_TYPE_L1D](../../../../../_api/group/group__KERNEL__DPL__CACHE.html), [CacheP_TYPE_ALL](../../../../../_api/group/group__KERNEL__DPL__CACHE.html)
- CPU cache lines sizes for reference
  - R5F: 32B

::::{only} SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX
  - A53: 64B
::::

- On R5F, It is recommended to enable both program and data cache in R5F in all applications. In R5F for cache to be enabled [MPU](MpuP_arm_v7.md) needs to be enabled.
- On M4F, the CPU does not support cache so these APIs when used with M4F, will be blank and will have no effect

## Example Usage

Include the below file to access the APIs,

**Example usage for cache write back invalidate:**

**Example usage for cache invalidate:**

## API Reference

```{doxygenfile} CacheP.h
```
