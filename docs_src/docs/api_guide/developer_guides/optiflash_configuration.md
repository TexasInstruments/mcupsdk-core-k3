# Configuring OptiFlash various IP {#OPTIFLASH_CONFIGURE}

[TOC]

## Introduction

This document gives a basic introduction to configuring different IPs, which is part of OptiFlash.

## How to configure FLC.

FLC is a simplified DMA. To configure FLC, in syscfg, it can be done by clicking to the `Fast Local Copy` nav menu item under OptiFlash drop down menu at the bottom.

\imageStyle{flc_syscfg_initial.png,width:50%}
\image html flc_syscfg_initial.png

Use `Add` button to to add FLC instances. For @VAR_SOC_NAME_LOWER case, there are a total of 4 FLC instances per R5 core. All info that needs to be given is source address, destination address and size. Make sure that all these fields are 4K aligned.
