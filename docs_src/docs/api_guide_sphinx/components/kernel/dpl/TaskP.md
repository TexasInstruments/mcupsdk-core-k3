
# Task
:::{admonition} Attention
This module is not applicable for [NO RTOS](../os/nortos.md) environment
:::


## Features Supported
- APIs to create and destroy tasks
- APIs to yeild a task
- Ability to specify task priority, task entry function, stack pointer, stack size
- Ability to get task and CPU load

## Features NOT Supported

NA

## Important Usage Guidelines

- On R5F, and M4F, make sure memory provided as stack is 32b aligned and size is also multiple of 32b
- Stack and stack size MUST be provided by application and is not allocated internally

## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TaskP_sample.c
:language: c
:lines: 1-10
```

**Example usage to define task objects and parameters:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TaskP_sample.c
:language: c
:lines: 12-25
```

**Example task main function:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TaskP_sample.c
:language: c
:lines: 27-40
```

**Example usage to create a task:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TaskP_sample.c
:language: c
:lines: 42-55
```

**Example usage to get task and CPU load:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TaskP_sample.c
:language: c
:lines: 57-70
```


## API Reference

```{doxygenfile} TaskP.h
```
