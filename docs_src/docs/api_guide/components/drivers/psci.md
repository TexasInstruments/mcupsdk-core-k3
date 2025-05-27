# PSCI {#DRIVERS_PSCI_PAGE}

[TOC]

Power State Coordination Interface (PSCI) is a standard interface for power management between ARM processors. It provides a standardized way for software running on an ARM system to communicate with power management firmware (Trusted Firmware-A).

## Features Supported

- CPU Power Management
  - CPU_ON
  - CPU_OFF
- System Power Management
  - SYSTEM_RESET
- Power State Query and Configuration
  - PSCI Version Query
  - PSCI Features

## SysConfig Features

- PSCI init and open is done by default through sysconfig generated code.
- No other specific configuration required for power management through PSCI.

## Features NOT Supported

NA

## Example Usage

Include the below file to access the APIs
\snippet Psci_sample.c include

Instance Open Example
\snippet Psci_sample.c open

Instance Close Example
\snippet Psci_sample.c close

CPU Power On Example
\snippet Psci_sample.c cpu_on

System Reset Example
\snippet Psci_sample.c system_reset

## API

\ref DRV_PSCI_MODULE
