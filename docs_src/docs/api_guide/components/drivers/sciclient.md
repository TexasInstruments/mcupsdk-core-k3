# SCICLIENT {#DRIVERS_SCICLIENT_PAGE}

[TOC]

The Sciclient driver provides API to communicate with the SYSFW to do system level tasks like resource allocation, peripheral power on/off, peripheral clock setting and so on. Below are the high level features supported by the driver

## Features Supported

- APIs to load the SYSFW onto the DMSC core
- APIs to pass a specific board configuration to the SYSFW
- Abstracted APIs for Power and Resource Management

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- There are no user programmable features for Sciclient SysConfig. However, adding any module makes the PowerClock_init() initialize the module power and clock. This is indirectly done using Sciclient APIs.

## Features NOT Supported

NA

## Important Usage Guidelines

-  Typical usage of Sciclient from user perspective would be for powering on/off a peripheral, or to get/set a particular clock

## Example Usage

Include the below file to access the APIs
\snippet Sciclient_sample.c include

Module Power ON Example
\snippet Sciclient_sample.c sciclient_module_power_on

## API

\ref DRV_SCICLIENT_MODULE
