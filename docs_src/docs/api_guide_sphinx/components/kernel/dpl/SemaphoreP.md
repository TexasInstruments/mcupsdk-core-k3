
# Semaphore
## Features Supported
- APIs to create binary and counting semaphore's
- APIs to create mutual exclusion semaphore
- Nesting of mutual exclusion semaphores
- Priority inheritance when supported by the underlying OS

## Features NOT Supported

NA

## Important Usage Guidelines

- `SemaphoreP_post` can be called from ISR as well as task context
- `SemaphoreP_pend` should not be called within ISR context. It can be called from task context.
- `SemaphoreP_pend` will block until the user specific timeout ticks have expired or semaphore is acquired.
  - In baremetal case, there is only a single main task and that will block or spin until the ticks have elasped or semaphore acquire is successful
  - In RTOS case, the current executing task will 'pend' and schedular will switch to another ready task until the ticks have elasped or semaphore acquire is successful
  - In both cases ISR's are still active
- There is nothing like priority inheritance in [NO RTOS](../os/nortos.md) mode

## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 1-10
```

**Example usage to define a semaphore:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 12-25
```

**Example usage to post a binary semaphore from an ISR:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 27-40
```

**Example usage to create and use a mutex:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 42-55
```

**Example usage to create and use a binary semaphore with timeout:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 57-70
```

**Example usage to create and use a counting semaphore:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/SemaphoreP_sample.c
:language: c
:lines: 72-85
```


## API Reference

```{doxygenfile} SemaphoreP.h
```
