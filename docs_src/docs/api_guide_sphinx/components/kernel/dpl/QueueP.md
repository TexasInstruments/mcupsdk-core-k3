
# Queue
## Features Supported
- APIs to create and destroy Queues
- APIs to Put element in Queue
- APIs to Get element from Queue
- APIs to Check if Queue is Empty

## Features NOT Supported

NA

## Important Usage Guidelines

- For creating the Queue application needs to provide the #QueueP_Object and it should not be modified by the applicaion.
- A field of type #QueueP_Elem should be placed at the head of client structs passed as Queue Elements to function #QueueP_put.
- It is recommended not to place the QueueP Object and QueueP Element objects in stack as they will be accessed by the driver till they are released.

## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/QueueP_sample.c
:language: c
:lines: 1-10
```

**Example usage to define Queue Object and Elements:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/QueueP_sample.c
:language: c
:lines: 12-25
```

**Example to create and use the Queue:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/QueueP_sample.c
:language: c
:lines: 27-40
```


## API Reference

```{doxygenfile} QueueP.h
```
