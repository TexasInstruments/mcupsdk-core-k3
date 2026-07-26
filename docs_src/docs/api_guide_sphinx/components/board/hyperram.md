# HyperRam

The driver takes care of all sequencing necessary to perform writes across pages and
the application need not take care of the programming intricacies.

## Features Supported

- Provides API to return HyperRam attributes like handle etc
- API to get device ID

## SysConfig Features

{{ VAR_SYSCFG_USAGE_NOTE }}

- Option to select HyperRam based on board
- Option to give corresponding CR1, ID0, ID1 values of HyperRam Registers

::::{only} SOC_AM275X
- Supported HyperRam devices
    - S80KS5122
::::

## Features NOT Supported

NA

## Important Usage Guidelines

::::{only} SOC_AM275X
- For the HyperRam region, the MPU Region Access Control Register should be set to Cacheable, Bufferable, and Non-shared for better performance.
- For the following HyperRam register regions, the MPU Region Access Control Register memory type should be set to Strongly Ordered to ensure that writes to the HyperRam registers occur in the expected sequence:
  - For IDENTIFICATION registers(ID0, ID1) of HyperRam at offset 0x0
  - For CONFIGURATION registers(CR0, CR1) of HyperRam at offset 0x1000
::::

## Example Usage

Include the below file to access the APIs

HyperRam open API

HyperRam close API

## API

`BOARD_HYPERRAM_MODULE`
