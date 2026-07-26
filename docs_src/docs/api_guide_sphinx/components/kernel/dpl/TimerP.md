
# Timer
## Features Supported
- APIs to setup timer configuration
- APIs to start and stop the timer
- APIs to get the current timer count
- APIs to check for counter overflow and clear timer overflow interrupt

## Features NOT Supported

NA

## Important Usage Guidelines

::::{only} SOC_AM64X or SOC_AM243X

- Support configuration for DM timer

::::

::::{only} SOC_AWR294X or SOC_AM273X or SOC_AM263X

- Support configuration for RTI timer
- Value for 'inputPreScaler' should be set to 1

::::

- Supports continues and oneshot mode
- When configuring the timer period in micro second the 'periodInNsec' should be set to 0

::::{only} SOC_AM62DX

:::{admonition} Attention
Timer(TIMER2) is used for the system tick functionality in c7x is also availbale to uses as a timer peripheral for a53 core. Hence use TIMER2 for single purpose either system tick functionality in c7x or timer peripheral for a53 core
:::

::::


## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TimerP_sample.c
:language: c
:lines: 1-10
```

**Example usage to initialize the timer:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TimerP_sample.c
:language: c
:lines: 12-40
```

**Example usage to start the timer:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TimerP_sample.c
:language: c
:lines: 20-25
```

**Example usage to get the current count value:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TimerP_sample.c
:language: c
:lines: 28-34
```

**Example usage to stop the timer:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/TimerP_sample.c
:language: c
:lines: 37-40
```


## API Reference

```{doxygenfile} TimerP.h
```
