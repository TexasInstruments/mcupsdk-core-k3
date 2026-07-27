# Enet EST/TAS Support

```{contents}
:depth: 3
:local:
```

## Introduction

### IEEE 802.1Qbv EST/TAS

IEEE 802.1Qbv [Time-Aware Shaper](https://en.wikipedia.org/wiki/Time-Sensitive_Networking#IEEE_802.1Qbv_Enhancements_to_Traffic_Scheduling:_Time-Aware_Shaper_(TAS)) (TAS), also called *Enhancements for Scheduled Traffic* (EST) in IEEE Std 802.1Q-2018, defines a mechanism to allocate and grant exclusive Ethernet port transmission access on repeating cycles which are divided into slices where traffic of specific traffic class queues can be selected for transmission.

![EST schedule](../../../images/networking/EST_Schedule_Diagram.png)

*Transmission gates* are associated with specific traffic class queues (0-7). When a gate is *open*, frames from the corresponding queue can be selected for transmission. When the gate is *closed*, frames will not be selected for transmission.

The list of all gate states for all slices in the cycle is called *gate control list*. The control list that is programmed is called *administrative list*; when active it is called *operational list*.

### Guard band

In EST, the transmission of a frame will not be interrupted; the full frame transmission will be completed even if it spills over the next time slice. A [guard band](https://en.wikipedia.org/wiki/Time-Sensitive_Networking#IEEE_802.1Qbv_in_more_detail:_Time_slices_and_guard_bands), which is a time slice with all gates closed, can be added right before critical time slices to ensure that the wire is cleared of any previous traffic.

## Enet LLD API

Enet LLD provides support for TAS/EST through the following most important IOCTLs:

- `ENET_TAS_IOCTL_SET_STATE` - Sets the state of TAS module for each MAC port:
  - `ENET_TAS_RESET` to reset the state machine.
  - `ENET_TAS_ENABLE` to start EST/TAS after a valid administrative list has been programmed.
  - `ENET_TAS_DISABLE` to stop EST/TAS.

- `ENET_TAS_IOCTL_SET_ADMIN_LIST` - Sets a new administrative list of type `EnetTas_ControlList`. The gate control list is composed of:
  - `baseTime` - The administrative base time which determines when the administrative list will become active.
  - `gateCmdList` - The actual gate control list as list of *time interval duration* and *gate state mask* pairs. Enet LLD supports up to 16 intervals.
  - `listLength` - The number of entries in the gate control list.
  - `cycleTime` - The repeating cycle time.
  - `sduTable` - The maximum service data unit (SDU) per queue.

- `ENET_TAS_IOCTL_GET_OPER_LIST_STATUS` - Gets the status of the operational list update.

![TAS IOCTL sequence in Enet LLD](../../../images/networking/Enet_Est.png)

:::{only} SOC_AM263X or SOC_AM263PX

## CPSW Support

### CPSW EST Driver Implementation

The EST functionality in CPSW is implemented in Enet LLD through two of its Enet LLD modules: CPTS and MAC port.

- Each Ethernet port has an **EST function generator (ESTF)** in the CPTS hardware module, used to program the EST *cycle time*.
- Each Ethernet transmit port has 128 locations in the CPSW global **EST Fetch RAM** used to program the EST *gate control list*.

**Fetch allow** is an 8-bit field, where each bit corresponds to the state of each of the 8 gates (one per priority) in a given time slice.

**Fetch count** value is defined in terms of wireside clock cycles. The shortest time slice allowed by CPSW is a fetch count of 16, which corresponds to 128 nanoseconds for 1-Gbps link or 640 nanoseconds for 100-Mbps link.

The **EST Fetch RAM** is configured by Enet LLD in **two-buffer operation mode** in order to use one buffer to hold the *operational list*, while the other can be programmed with the next *administrative list*.

### Programming Guidelines and Limitations

#### Administrative base time

As per EST/TAS specification, the administrative base time can be set to a future or past time. When set to a past time, CPSW driver will start ESTF right away.

- If EST is in disabled or reset state, driver will allow a non-zero administrative base time.
- If EST is in enabled state, driver will reject any non-zero administrative base time.

#### Gate control list

The gate control list passed to the CPSW EST driver can be of the following types:

- Gate operation with non-zero time interval and non-zero gate mask - regular gate operation.
  - Minimum time interval and maximum time interval limits:

  | Link speed | Min time interval (nsecs) | Max time interval (nsecs) |
  |---|---|---|
  | 1 Gbps | 128 | 131,064 |
  | 100 Mbps | 640 | 655,320 |
  | 10 Mbps | 6,400 | 6,553,200 |

- Gate operation with non-zero time interval and zero gate mask - used for guard band.
- Gate operation with zero time interval and non-zero gate mask - holds corresponding fetch allow for remaining duration of cycle.
- Gate operation with zero time and zero gate mask - invalid.

#### Guard band

When computing the duration of the guard band:

- 1-Gbps: `((maxPktLen + 4) + 292) * 8` nanoseconds.
- 100-Mbps: `(((maxPktLen + 4) * 2) + 292) * 40` nanoseconds.
- 10-Mbps: `(((maxPktLen + 4) * 2) + 292) * 400` nanoseconds.

A helper macro `CPSW_MACPORT_EST_GUARD_BAND` is provided to compute the guard band duration.

#### Link-down event

When link is lost, CPSW driver will clear the previous operational list programmed in EST RAM. The application has to program again an administrative control list via `ENET_TAS_IOCTL_SET_ADMIN_LIST` command when link is back up.

#### Limitations

The following EST features are not supported by the driver:
- Administrative cycle time different from current operational cycle time is not supported.
- Administrative cycle time extension is not supported.
- Configuration of Maximum SDU table is not supported.
- Administrative list needs to be configured again by application after link down events.

The following EST features have limited support:
- Administrative base time at a future time is only supported when EST is not enabled.
- Time slices longer than 131.064 microseconds (1-Gbps) or 655.32 microseconds (100-Mbps) will be rejected.

### Debugging and Troubleshooting

#### EST Timestamping

EST packet timestamping can be used as an aid for debugging purposes. CPSW supports four types of timestamping modes:

- Timestamp all packets on any priority.
- Timestamp all packets of given priority.
- Timestamp the first packet in each time interval.
- Timestamp the first packet of a given priority in the time interval.

CPSW driver provides the following private EST timestamp related IOCTLs:

- `CPSW_MACPORT_IOCTL_EST_ENABLE_TIMESTAMP` - Enables EST packet timestamping.
- `CPSW_MACPORT_IOCTL_EST_DISABLE_TIMESTAMP` - Disables EST packet timestamping.
- `CPSW_CPTS_IOCTL_LOOKUP_EST_EVENT` - Retrieves EST timestamps from CPTS driver.

:::

:::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X

Enet LLD does not support CPSW EST for this SoC.

:::
