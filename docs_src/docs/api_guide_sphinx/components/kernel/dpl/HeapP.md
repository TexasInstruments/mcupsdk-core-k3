
# Heap
## Features Supported

- Ability to create multiple user defined heaps
- Alloc and free APIs
- Detailed heap statistics
- Thread safe APIs with RTOS
- Minimum alignment of `HeapP_BYTE_ALIGNMENT` for all allocations

## Features NOT Supported

- Memory allocation with alignment as a input. Users should allocate extra and align after allocation.

## Important Usage Guidelines

NA

## Example Usage

Include the below file to access the APIs,

**Example usage to define a heap memory and heap handle:**

**Example usage to create a heap:**

**Example usage to allocate and free memory:**

## API Reference

```{doxygenfile} HeapP.h
```
