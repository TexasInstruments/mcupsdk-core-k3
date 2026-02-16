# SBL ETH UNIFLASH {#EXAMPLES_DRIVERS_SBL_ETH_UNIFLASH}

[TOC]

# Introduction


\cond SOC_AM275X

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5 and C7x cores.

The booting is done in single stage
 - The stage is multithreaded with one thread runs the sciServer and the other thread runs the SBL which boots the RTOS/NORTOS applications to R5/C7x cores

\endcond

# Supported Combinations

\cond SOC_AM275X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup_r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_eth_uniflash
\endcond

# Pre-requisites
- Linux PC with Ethernet Port
- AM275-EVM  with DP83867 PHY Add-on
- CAT5 Ethernet Cable

# Steps to Run the Example

## Boot Mode Switch Selection
\imageStyle{boot_pins_eth_mode.jpg,width:30%}
\image html boot_pins_eth_mode.jpg

\note Do not connect UART_CONN USB Connector on the EVM, This modifies the Boot selection signals causing the RBL to not boot from Ethernet.

## DHCP Setup
- On your PC, install DHCP server
\code
sudo apt install isc-dhcp-server
\endcode
- Disable services before configuring
\code
sudo systemctl disable --now isc-dhcp-server.service isc-dhcp-server6.service
\endcode
- Run the ip link or ifconfig command to find the name of your network interface, In this example, `eno1` is used as Network interface.
- Do following changes in `/etc/dhcp/dhcpd.conf`
\code
subnet 192.168.0.0 netmask 255.255.255.0
{
range dynamic-bootp 192.168.0.137 192.168.0.142;
if substring (option vendor-class-identifier, 0, 16) = "TI K3 Bootp Boot"
{
filename "sbl_eth_uniflash.release.tiimage";
}
default-lease-time 60000;
max-lease-time 720000;
next-server 192.168.0.136;
}
\endcode

- Do following changes in `/etc/default/isc-dhcp-server`
\code
DHCPDv4_CONF=/etc/dhcp/dhcpd.conf
INTERFACESv4="eno1"
INTERFACESv6=""
\endcode

- For your interface, change IP address, gateway and netmask to the following (the below values are hard-coded in the SBL)
\code
sudo ifconfig <interface-name> <static-HOST-IP>
\endcode

- Enable DHCP
\code
sudo systemctl enable --now isc-dhcp-server
\endcode

- To see if there is any configuration error or if DHCP is running, run the below command
\code
sudo service isc-dhcp-server status
\endcode

## TFTP Setup
- Follow the link below to setup the TFTP server
\code
https://linuxhint.com/install_tftp_server_ubuntu/
\endcode

# Steps to run Ethernet boot
- Create a network between EVM and host PC

\note The IP addresses used here are also used by the python script and the EVM application, so ensure to change the IP addresses in all the places if there’s any conflict with existing devices.

- Fix the Ethernet Link capabilities of the host PC using this command
\code
sudo ethtool -s eno1 speed 100 duplex full autoneg off
\endcode

- Add a static ARP entry with the below command. Use IP Address of EVM in the below command in this case its `192.168.0.195`
\code
sudo arp -i <interface-name> -s <IP-Address> <MAC-Address>
\endcode

- Replace the `ENET_HOST_PC_MAC_ADDRESS` in sbl_enet.h with the Host PC MAC Address that can be found using the command `ip a`
- Build the Example and copy the tiimage file to the tftp folder in this case the tftp folder is `/tftp/`

- Power-off the board and switch it to Ethernet boot mode.
- Connect to the UART Terminal to view the SBL Logs.
- Power on the board and wait for the SBL Logs to appear.
- Run the below python command to transfer the images.

\code
cd ${SDK_INSTALL_PATH}/tools/boot
python3 enet_uniflash.py --cfg=sbl_prebuilt/am275x-evm/sbl_eth_ospi_hs_fs.cfg
\endcode

- When the python script starts, it will display the message "Starting Linkup ...".
- After flashing is successful, power off the board, change the boot mode to OSPI to run the applications.

# Sample Output
\code
Sciserver Testapp Built On: Feb 23 2026 16:36:43
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED

SYSFW ABI: 4.0 (firmware rev 0x000b '11.2.9-9-g37556c (Fancy Rat)')

[ ENETSBL ] Starting Ethernet Transfer ...
ERROR: Bootloader_socCpuPowerOnResetR5f:1032: CPU set config failed for r5f0-0
Enabling clocks!
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:0 From 4 To 1 
Open MAC port 1
EnetPhy_bindDriver:1942 
PHY 0 is alive
[ ENETSBL ] initQs() txFreePktInfoQ initialized with 8 pkts
[ ENETSBL ] EVM MAC address: 44:6b:1f:2c:2d:2b
[ ENETSBL ] PHY 0 is alive
[ ENETSBL ] Please wait for Linkup ...
Cpsw_handleLinkUp:1423 
[ ENETSBL ] Linkup Done!
[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  324 
[ ENETSBL ] Total File Size    :  471625 Bytes
[ ENETSBL ] Flash Offset       :  0x0

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  37 
[ ENETSBL ] Total File Size    :  52122 Bytes
[ ENETSBL ] Flash Offset       :  0x400000

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  34 
[ ENETSBL ] Total File Size    :  47570 Bytes
[ ENETSBL ] Flash Offset       :  0x800000

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  34 
[ ENETSBL ] Total File Size    :  47570 Bytes
[ ENETSBL ] Flash Offset       :  0xC00000

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  34 
[ ENETSBL ] Total File Size    :  47570 Bytes
[ ENETSBL ] Flash Offset       :  0x1000000

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  98 
[ ENETSBL ] Total File Size    :  141735 Bytes
[ ENETSBL ] Flash Offset       :  0x1400000

[ ENETSBL ] Receiving file, please wait ...
[ ENETSBL ] Status:0
[ ENETSBL SUCCESS ] Ethernet Transfer Done.
[ ENETSBL ] Packets Received   :  104 
[ ENETSBL ] Total File Size    :  150383 Bytes
[ ENETSBL ] Flash Offset       :  0x1800000


Cpsw_handleLinkDown:1449 
Disabling clocks for ENET: 5, inst:0!

\endcode
# Troubleshooting

- If there are no SBL Logs on the JTAG_UART, then check the following things
1. Check the link speed using this command, Link speed must be 100M and Duplexity must be Full.
\code
sudo ethtool eno1
\endcode
2. If the Link settings are as mentioned above, then check the Messages from the Device using Wireshark, The Device sends BOOTP message to PC in Ethernet Boot mode.
3. If the PC sent the application through TFTP (can be seen in wireshark) and still Booting fails, then check the TFTP service.