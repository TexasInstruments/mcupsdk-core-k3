# Modifying resource allocation {#RESOURCE_ALLOCATION_GUIDE}

[TOC]

## Introduction

Various resources of the SOC like the number of DMA channels, number of interrupt router outputs, number of interrupt aggregator virtual interrupt numbers etc. are usually managed by a resource management system or a resource manager.

\cond SOC_AM64X
In the case of AM64x and AM243x devices, this is managed by the System Controller Firmware (SYSFW) running on the M3 core. Once the SYSFW is loaded on M3 and is initialized, we need to send a certain configuration data to the SYSFW regarding the resources we would be using. This is largely an array of resource assignment entries, with each entry specifying the start number of the resource, count or number of resource needed, type of resource, host id of the core which will request for this resource, etc. Later when the request for a specific resource is made, the SYSFW will cross check the request parameters with this already sent configuration data, and the requested resources will only be allocated if that falls within the range in this configuration data. We call this the Resource Management Board Configuration or __RM boardcfg__.
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
In the case of @VAR_SOC_NAME devices, this is managed by the DM Firmware (Divice Manager Firmware) running on the WKUP R5 / DM R5 core. Once the DM firmware is loaded on DM R5 and is initialized, it will read a certain configuration data regarding the resources we would be using. Rom bootloader (RBL) should have loaded this as part of bootflow. This is largely an array of resource assignment entries, with each entry specifying the start number of the resource, count or number of resource needed, type of resource, host id of the core which will request for this resource, etc. Later when the request for a specific resource is made, the DM firmware will cross check the request parameters with this already sent configuration data, and the requested resources will only be allocated if that falls within the range in this configuration data. We call this the Resource Management Board Configuration or __RM boardcfg__.
\endcond

Refer \htmllink{https://software-dl.ti.com/tisci/esd/latest/3_boardcfg/BOARDCFG_RM.html, TISCI documentation} for more details on the RM board configuration.

## Changing a particular resource
\note At the moment the changes need to made manually by editing C files, but soon a Sysconfig GUI based tool will be available to generate this C file.

\cond SOC_AM64X
- To change the assigned number of a particular resource, the `sciclient_defaultBoardcfg_rm.c` file at path `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\sciclient_default_boardcfg\am64x_am243x\` location.

- Around line 135 of the file, you should find a line which says `.resasg_entries = {`. This is an array of resource assignment entries. Resource assignment entries are structs with members
 - num_resource (Number or Count of resources)
 - type (Type of resource, can be DMA channel, or Interrupt Router Output, etc.)
 - start_resource (Starting number of the resource)
 - host_id (Host ID of the core which can request for this resource)

\imageStyle{resasg_1.png,width:50%}
\image html resasg_1.png "Resource Assignment Entries"

- Once you have identified the resource type which you want to modify, you can see if an entry with that type is already part of the array. If yes, you can go ahead and make the changes directly depending on what you want to do. Change the start number, decrease/increase the number of resources etc. Make sure that resources do not overlap when you change this. Another thing to take care is the host_id in the entry you make. If you add the entry with the current resource range but with a wrong host_id, your host won't be able to request for that particular resource. For each core present in the SoC, there will be two host types - Secure and Non-Secure. These host ids are defined in `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\include\tisci\am64x_am243x\tisci_hosts.h` file.

- Here is the host id to core mapping:
<table>
<tr>
    <th>HOST ID
    <th>Core
</tr>
<tr>
    <td>TISCI_HOST_ID_DMSC (0U)
    <td>DMSC ARM Cortex M3
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_0 (35U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_1 (36U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_2 (37U)
    <td>Cortex R5FSS0_1 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_3 (38U)
    <td>Cortex R5FSS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_1_R5_0 (40U)
    <td>Cortex R5FSS1_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_1_R5_1 (41U)
    <td>Cortex R5FSS1_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_1_R5_2 (42U)
    <td>Cortex R5FSS1_1 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_1_R5_3 (43U)
    <td>Cortex R5FSS1_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (10U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (11U)
    <td>Cortex A53SS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (12U)
    <td>Cortex A53SS0_1 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (13U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_M4_0 (30U)
    <td>Cortex M4 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_ICSSG_0 (50U)
    <td>ICSSG_0 (Non-Secure Context)
</tr>
</table>

- If the resource type required is not present in the array, you need to add this entry and give all the four parameters described above. In this case, make sure that you change the array size accordingly at around line 132 where we specify `resasg_entries_size = ...`. Change that number to reflect the entry added or removed in your case.

\imageStyle{resasg_2.png,width:50%}
\image html resasg_2.png "Resource Assignment Entries Size"

\endcond
\cond SOC_AM62X
- To change the assigned number of a particular resource, the `sciclient_defaultBoardcfg_rm.c` file at path `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\sciclient_default_boardcfg\am62x\` location.

- Around line 110 of the file, you should find a line which says `.resasg_entries = {`. This is an array of resource assignment entries. Resource assignment entries are structs with members
 - num_resource (Number or Count of resources)
 - type (Type of resource, can be DMA channel, or Interrupt Router Output, etc.)
 - start_resource (Starting number of the resource)
 - host_id (Host ID of the core which can request for this resource)

\imageStyle{resasg_1_am62x.png,width:50%}
\image html resasg_1_am62x.png "Resource Assignment Entries"

- Once you have identified the resource type which you want to modify, you can see if an entry with that type is already part of the array. If yes, you can go ahead and make the changes directly depending on what you want to do. Change the start number, decrease/increase the number of resources etc. Make sure that resources do not overlap when you change this. Another thing to take care is the host_id in the entry you make. If you add the entry with the current resource range but with a wrong host_id, your host won't be able to request for that particular resource. For each core present in the SoC, there will be two host types - Secure and Non-Secure. These host ids are defined in `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\include\tisci\am62x\tisci_hosts.h` file.

- A host is defined as a logically distinct high level software entity along with a particular security status. This is mostly a
  particular piece of software running on a physical core.

- In the RTOS world this does not have a lot of significance, where mostly it is going to be one piece of software which
  is going to run in a core - be it a bare-metal application or an RTOS based one. In linux/HLOS, it is possible that a
  core has multiple SW entities running, mostly as VMs.

- In a case where a security firmware and the Linux OS is running in the same core, both these SW entities would be considered
  as different hosts, because of the difference in security status.

- Each of these 'hosts' are given an ID by the SYSFW:

- Here is the host id to core mapping:
<table>
<tr>
    <th>HOST ID
    <th>Core
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS (0U)
    <td>TIFS ARM Cortex M4
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (10U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_1 (11U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_2 (12U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_3 (13U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_4 (14U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_M4_0 (30U)
    <td>Cortex M4 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_GPU_0 (31U)
    <td>GPU (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_0 (35U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_1 (36U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_2 (37U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_3 (38U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM2TIFS (250U)
    <td>DM2TIFS(Secure): DM to TIFS communication
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS2DM (251U)
    <td>TIFS2DM(Non Secure): TIFS to DM communication
</tr>
<tr>
    <td>TISCI_HOST_ID_HSM (253U)
    <td>HSM (Secure)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM (254U)
    <td>DM(Non Secure): Device Management
</tr>
</table>

Refer \htmllink{https://software-dl.ti.com/tisci/esd/latest/5_soc_doc/am62x/hosts.html, TISCI Host descriptions}

- If the resource type required is not present in the array, you need to add this entry and give all the four parameters described above. In this case, make sure that you change the folloing number.

\imageStyle{resasg_2_am62x.png,width:50%}
\image html resasg_2_am62x.png "Resource Assignment Entries Size"

\endcond

\cond SOC_AM62AX || SOC_AM62DX
- To change the assigned number of a particular resource, the `sciclient_defaultBoardcfg_rm.c` file at path `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\sciclient_default_boardcfg\am62ax\` location.

- Around line 100 of the file, you should find a line which says `.resasg_entries = {`. This is an array of resource assignment entries. Resource assignment entries are structs with members
 - num_resource (Number or Count of resources)
 - type (Type of resource, can be DMA channel, or Interrupt Router Output, etc.)
 - start_resource (Starting number of the resource)
 - host_id (Host ID of the core which can request for this resource)

\imageStyle{resasg_1_am62ax.png,width:50%}
\image html resasg_1_am62ax.png "Resource Assignment Entries"

- Once you have identified the resource type which you want to modify, you can see if an entry with that type is already part of the array. If yes, you can go ahead and make the changes directly depending on what you want to do. Change the start number, decrease/increase the number of resources etc. Make sure that resources do not overlap when you change this. Another thing to take care is the host_id in the entry you make. If you add the entry with the current resource range but with a wrong host_id, your host won't be able to request for that particular resource. For each core present in the SoC, there will be two host types - Secure and Non-Secure. These host ids are defined in `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\include\tisci\am62ax\tisci_hosts.h` file.

- A host is defined as a logically distinct high level software entity along with a particular security status. This is mostly a
  particular piece of software running on a physical core.

- In the RTOS world this does not have a lot of significance, where mostly it is going to be one piece of software which
  is going to run in a core - be it a bare-metal application or an RTOS based one. In linux/HLOS, it is possible that a
  core has multiple SW entities running, mostly as VMs.

- In a case where a security firmware and the Linux OS is running in the same core, both these SW entities would be considered
  as different hosts, because of the difference in security status.

- Each of these 'hosts' are given an ID by the SYSFW:

- Here is the host id to core mapping:
<table>
<tr>
    <th>HOST ID
    <th>Core
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS (0U)
    <td>TIFS ARM Cortex M4
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (10U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_1 (11U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_2 (12U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_3 (13U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_4 (14U)
    <td>Cortex Cortex A53SS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_C7X_0_0 (20U)
    <td>C7X_0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MCU_0_R5_0 (30U)
    <td>Cortex MCU R5 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_0 (35U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_1 (36U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_2 (37U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_3 (38U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM2TIFS (250U)
    <td>DM2TIFS(Secure): DM to TIFS communication
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS2DM (251U)
    <td>TIFS2DM(Non Secure): TIFS to DM communication
</tr>
<tr>
    <td>TISCI_HOST_ID_HSM (253U)
    <td>HSM (Secure)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM (254U)
    <td>DM(Non Secure): Device Management
</tr>
</table>

Refer \htmllink{https://software-dl.ti.com/tisci/esd/latest/5_soc_doc/am62ax/hosts.html, TISCI Host descriptions}

- If the resource type required is not present in the array, you need to add this entry and give all the four parameters described above. In this case, make sure that you change the folloing number.

\imageStyle{resasg_2_am62ax.png,width:50%}
\image html resasg_2_am62ax.png "Resource Assignment Entries Size"

\endcond

\cond SOC_AM62PX
- To change the assigned number of a particular resource, the `sciclient_defaultBoardcfg_rm.c` file at path `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\sciclient_default_boardcfg\am62px\` location.

- Around line 100 of the file, you should find a line which says `.resasg_entries = {`. This is an array of resource assignment entries. Resource assignment entries are structs with members
 - num_resource (Number or Count of resources)
 - type (Type of resource, can be DMA channel, or Interrupt Router Output, etc.)
 - start_resource (Starting number of the resource)
 - host_id (Host ID of the core which can request for this resource)

\imageStyle{resasg_1_am62px.png,width:50%}
\image html resasg_1_am62px.png "Resource Assignment Entries"

- Once you have identified the resource type which you want to modify, you can see if an entry with that type is already part of the array. If yes, you can go ahead and make the changes directly depending on what you want to do. Change the start number, decrease/increase the number of resources etc. Make sure that resources do not overlap when you change this. Another thing to take care is the host_id in the entry you make. If you add the entry with the current resource range but with a wrong host_id, your host won't be able to request for that particular resource. For each core present in the SoC, there will be two host types - Secure and Non-Secure. These host ids are defined in `{SDK_ROOT_DIRECTORY}\source\drivers\sciclient\include\tisci\am62px\tisci_hosts.h` file.

- A host is defined as a logically distinct high level software entity along with a particular security status. This is mostly a
  particular piece of software running on a physical core.

- In the RTOS world this does not have a lot of significance, where mostly it is going to be one piece of software which
  is going to run in a core - be it a bare-metal application or an RTOS based one. In linux/HLOS, it is possible that a
  core has multiple SW entities running, mostly as VMs.

- In a case where a security firmware and the Linux OS is running in the same core, both these SW entities would be considered
  as different hosts, because of the difference in security status.

- Each of these 'hosts' are given an ID by the SYSFW:

- Here is the host id to core mapping:
<table>
<tr>
    <th>HOST ID
    <th>Core
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS (0U)
    <td>TIFS ARM Cortex M4
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_0 (10U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_1 (11U)
    <td>Cortex A53SS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_2 (12U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_3 (13U)
    <td>Cortex A53SS0_1 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_A53_4 (14U)
    <td>Cortex Cortex A53SS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MCU_0_R5_0 (30U)
    <td>Cortex MCU R5 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_0 (35U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_1 (36U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_2 (37U)
    <td>Cortex R5FSS0_0 (Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_MAIN_0_R5_3 (38U)
    <td>Cortex R5FSS0_0 (Non-Secure Context)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM2TIFS (250U)
    <td>DM2TIFS(Secure): DM to TIFS communication
</tr>
<tr>
    <td>TISCI_HOST_ID_TIFS2DM (251U)
    <td>TIFS2DM(Non Secure): TIFS to DM communication
</tr>
<tr>
    <td>TISCI_HOST_ID_HSM (253U)
    <td>HSM (Secure)
</tr>
<tr>
    <td>TISCI_HOST_ID_DM (254U)
    <td>DM(Non Secure): Device Management
</tr>
</table>

Refer \htmllink{https://software-dl.ti.com/tisci/esd/latest/5_soc_doc/am62px/hosts.html, TISCI Host descriptions}

- If the resource type required is not present in the array, you need to add this entry and give all the four parameters described above. In this case, make sure that you change the folloing number.

\imageStyle{resasg_2_am62px.png,width:50%}
\image html resasg_2_am62px.png "Resource Assignment Entries Size"

\endcond

## Rebuilding the board configuration

- Once the changes are made in the file, we need to generate a hex array corresponding to the file and make sure that the bootloader libraries and the `sciclient_set_boardcfg` application are updated with these changes. For this one can follow \ref BOARCFG_GEN section

