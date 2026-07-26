# Introduction

```{contents}
:depth: 2
:local:
```

## Introduction

LwIP is the TCP/IP networking protocol stack supported and integrated into SDK in its 'vanilla' version.

As per [LwIP project page](http://savannah.nongnu.org/projects/lwip/)

> The focus of the lwIP TCP/IP implementation is to reduce resource usage while still having a full scale TCP. This makes lwIP suitable for use in embedded systems with tens of kilobytes of free RAM and room for around 40 kilobytes of code ROM.
>
> Main features include:
> - Protocols: IP, IPv6, ICMP, ND, MLD, UDP, TCP, IGMP, ARP, PPPoS, PPPoE
> - DHCP client, DNS client (incl. mDNS hostname resolver), AutoIP/APIPA (Zeroconf), SNMP agent (v1, v2c, v3, private MIB support & MIB compiler)
> - APIs: specialized APIs for enhanced performance, optional Berkeley-alike socket API
> - Extended features: IP forwarding over multiple network interfaces, TCP congestion control, RTT estimation and fast recovery/fast retransmit
> - Add-on applications: HTTP(S) server, SNTP client, SMTP(S) client, ping, NetBIOS nameserver, mDNS responder, MQTT client, TFTP server.

Current version that is supported is {{ VAR_LWIP_VERSION }}.
