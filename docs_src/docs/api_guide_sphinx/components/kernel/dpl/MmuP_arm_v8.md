
# MMU for ARMv8 (ARM A53, TI C75)
## Features Supported

- APIs to setup MMU regions, including region address, size, attributes like access permissions, cache properties
- APIs to enable, disable MMU
- API to check if MMU is enabled

## Features NOT Supported

NA

## Important Usage Guidelines

- MMU regions can overlap each other, with higher numbered regions taking more precedence in case of address overlaps.

## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/MmuP_arm_v8_sample.c
:language: c
:lines: 1-10
```

**Example to setup MMU regions and enable MMU:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/MmuP_arm_v8_sample.c
:language: c
:lines: 12-41
```

## API

See [MmuP_armv8.h](../../../../../../source/kernel/dpl/MmuP_armv8.h)
