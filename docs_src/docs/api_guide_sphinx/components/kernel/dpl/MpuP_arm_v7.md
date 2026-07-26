
# MPU for ARMv7 (ARM R5)
## Features Supported

- APIs to setup MPU regions, including region address, size, attributes like access permissions, cache properties
- APIs to enable, disable MPU
- API to check if MPU is enabled

## Features NOT Supported

NA

## Important Usage Guidelines


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- Refer to ARMv7-R or ARMv7-M architecture manual for more details
- The number of MPU entries varies based on the ARM R5, ARM M4 instantiated in a given DEVICE, refer DEVICE datasheet for more details.
- In R5 for this DEVICE, there are 16 MPU regions

::::

::::{only} SOC_AM62X

- Refer to ARMv7-M architecture manual for more details
- The number of MPU entries varies based on the ARM M4 instantiated in a given DEVICE, refer DEVICE datasheet for more details.

::::

::::{only} SOC_AM62AX

- Refer to ARMv7-R architecture manual for more details
- The number of MPU entries varies based on the ARM R5, ARM M4 instantiated in a given DEVICE, refer DEVICE datasheet for more details.
- In R5 for this DEVICE, there are 16 MPU regions

::::

::::{only} SOC_AM62DX

- Refer to ARMv7-R architecture manual for more details
- The number of MPU entries varies based on the ARM R5 instantiated in a given DEVICE, refer DEVICE datasheet for more details.
- In R5 for this DEVICE, there are 16 MPU regions

::::


::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- In M4 for this DEVICE, there are 16 MPU regions

::::


::::{only} SOC_AM275X
   - Refer to ARMv7-R architecture manual for more details
   - The number of MPU entries varies based on the ARM R5 instantiated in a given DEVICE, refer DEVICE datasheet for more details.
   - In R5 for this DEVICE, there are 16 MPU regions
::::

- MPU regions can overlap each other, with higher numbered regions taking more precedence in case of address overlaps.

## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/MpuP_arm_v7_sample.c
:language: c
:lines: 1-10
```

**Example usage to setup MPU regions and enable MPU:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/MpuP_arm_v7_sample.c
:language: c
:lines: 12-50
```


Example to setup MPU regions and enable MPU is shown below,



## API Reference

```{doxygenfile} MpuP_armv7.h
```
