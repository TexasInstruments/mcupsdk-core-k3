# SCMI {#DRIVERS_SCMI_PAGE}

[TOC]

System Control and Management Interface (SCMI) is a standardized protocol for communication between platform management controllers (Trusted Firmware-A) and application processors. It provides a unified interface for system control and management operations.

## Features Supported

- Message-based communication protocol
- Power domain control
- Clock management
- Support for multiple transport protocols
- Protocol versioning

## SysConfig Features

- SCMI init and open is done by default through sysconfig generated code.
- SCMI init and open has been done before power and clock are enabled for the peripherals in the sysconfig generated code.

## Important Usage Guidelines

- Most of these APIs are already integrated with SysConfig tool and the generated code does the required call to enable a module, set the required clock and so on through the SoC layer.
- User may not need to perform any explicit configuration for power domain and clock, unless it's needed in exceptional scenarios.

## Features NOT Supported

NA

## Example Usage

Include the below file to access the APIs
\snippet Scmi_sample.c include

Base protocol versioning example
\snippet Scmi_sample.c base_protocol

Power domain state set and get example
\snippet Scmi_sample.c power_domain_protocol

Clock rate get and set example
\snippet Scmi_sample.c clock_protocol

## API

\ref DRV_SCMI_MODULE
