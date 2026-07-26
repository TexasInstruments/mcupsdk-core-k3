
# Event
## Features Supported
- APIs to construct and destruct Events
- APIs to set, get or clear bits and wait for bits

## Features NOT Supported

- These APIs are not implemented for [NO RTOS](../os/nortos.md). Error will be returned if these APIs called using [NO RTOS](../os/nortos.md).

## Important Usage Guidelines

- [EventP_waitBits](../../../../../_api/group/group__KERNEL__DPL__EVENT.html) should not be called within ISR context. It can be called from task context.
- Setting or clearing the Event bits is a non-deterministic operation and [FreeRTOS](../os/freertos.md) does not allow non-deterministic operations to be performed in interrupts or from critical sections. If [EventP_setBits](../../../../../_api/group/group__KERNEL__DPL__EVENT.html) or [EventP_clearBits](../../../../../_api/group/group__KERNEL__DPL__EVENT.html) is called from an ISR, a message is sent to RTOS daemon task to perform the operation in the context of daemon task. If the set or clear operation is required to be completed immediately, then the priority of RTOS daemon task must be higher than the priority of task waiting for the Event bits. The priority of RTOS daemon task is set by the `configTIMER_TASK_PRIORITY` in FreeRTOSConfig.h file.
-  The actual current value of Event bits returned from [EventP_waitBits](../../../../../_api/group/group__KERNEL__DPL__EVENT.html) and [EventP_getBits](../../../../../_api/group/group__KERNEL__DPL__EVENT.html) can be different from returned value if an interrupt or a higher priority task modifies the value between the calling task leaving blocked state and exiting this API.

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/EventP_sample.c
:language: c
:lines: 1-10
```

**Example usage to define an Event:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/EventP_sample.c
:language: c
:lines: 12-25
```

**Example usage to create an Event:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/EventP_sample.c
:language: c
:lines: 27-40
```

**Example usage to set and wait for bits across two tasks:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/EventP_sample.c
:language: c
:lines: 42-55
```


## API Reference

```{doxygenfile} EventP.h
```
