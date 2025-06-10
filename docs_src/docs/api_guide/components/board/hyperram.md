# HyperRam {#BOARD_HYPERRAM_PAGE}

[TOC]
The driver takes care of all sequencing necessary to perform writes across pages and
the application need not take care of the programming intricacies.

## Features Supported

- Provides API to return HyperRam attributes like handle etc
- API to get device ID

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Option to select HyperRam based on board
- Option to give corresponding CR1, ID0, ID1 values of HyperRam

\cond SOC_AM275X
- Supported HyperRam devices
    - S80KS5122
\endcond

## Features NOT Supported

NA

## Important Usage Guidelines


## Example Usage

Include the below file to access the APIs
\snippet HyperRam_sample.c include

HyperRam open API
\snippet HyperRam_sample.c open

HyperRam close API
\snippet HyperRam_sample.c close

## API

\ref BOARD_HYPERRAM_MODULE