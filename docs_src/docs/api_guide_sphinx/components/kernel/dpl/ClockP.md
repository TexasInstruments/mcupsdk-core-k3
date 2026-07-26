
# Clock
## Features Supported

- Provide system tick functionality using a single timer to periodically interrupt the CPU
- Default tick period is 1000 usecs
- Using this system tick,
  - Users can create arbitrary number of clock objects
  - When a clock object expires, a user specified callback is called
  - Clock expiry time is specified in units of clock ticks
  - Each clock can be started in one-shot callback or periodic callback mode
- Provides APIs to wait 'n' clock ticks, get current clock ticks
- Provides APIs to convert clock ticks to time in usecs and vica versa
- API to get current time in units of usecs

## Features NOT Supported

NA

## Important Usage Guidelines

- The user specific callback can be called in interrupt, SWI or task context depending on the underlying RTOS that is used
  - In no-RTOS case, the callback is called in interrupt context
  - It is recommended to assume that the callback is called in ISR context and not block within the callback.
  - Typically one should do very limited work within the callback itself and defer the larger part of the work to a task via a semaphore post.
- `ClockP_usleep` and `ClockP_sleep` will block until the user specified time is expired.
  - In no-RTOS case, there is only a single main task and that will block or spin until the ticks have elasped
  - In RTOS case, the current executing task will 'pend' and schedular will switch to another ready task
  - In both cases ISR's are still active
  - In RTOS case, actual sleep will be in the range of `sleep time - ClockP_ticksToUsec(1)` to `sleep time`. If you need to guarantee atleast minimum
    sleep of `sleep time`, you need to sleep for `sleep time + ClockP_ticksToUsec(1)`, i.e there will be a error on 1 OS tick at max.
- When using multiple CPUs, make sure each CPU uses a different HW timer else the tick ISR will not trigger as expected.
- Recommended value of tick period is 1ms or 1000us
- Adding any module in SysConfig, automatically adds a clock module with a timer configured for 1ms. The default timer is chosen
  such that it does not overlap with a timer from another CPU.

::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- In M4F, the M4F internal SysTick timer is used.

::::

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- In R5F, one of the many SOC level timer is used.

::::


## Example Usage

Include the below file to access the APIs,

**Example callback that increments a global counter based on the clock that invoked the callback:**

**Example usage to create a clock in one shot mode with timer expiry of 10ms:**

**Example usage to create a clock in periodic mode with timer period of 100ms:**

**Example usage to measure time and profile a function:**

## API Reference

```{doxygenfile} ClockP.h
```
