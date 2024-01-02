#!/usr/bin/env python3
import binascii
import struct
import string
import sys
import serial
import time

# SCRIPT USAGE
# ------------
# usage: uart_boot_socid.py [-h] -d DEVICE (-s STRING | -f FILE)
#   -h, --help            show this help message and exit
# required arguments:
#
#   -d DEVICE, --device   - device for which the soc id will be parsed
#
#   -s STRING, --string   - Soc id reported from UART console
#                           (OR)
#   -f FILE, --file       - file which contains the soc id reported from UART console

# Changelog (yyyy-mm-dd)
# 2022-01-06 print secure blocks only when present. Format script with autopep8

# usage
# $ cat test.txt
# 01000000011a00006a3765730000000000000000475020200101010001010100
# $ ./parse_uart_boot_socid.py test.txt
# -----------------------
# SoC ID Header Info:
# -----------------------
# NumBlocks            : 1
# -----------------------
# SoC ID Public ROM Info:
# -----------------------
# SubBlockId           : 1
# SubBlockSize         : 26
# DeviceName           : j7es
# DeviceType           : GP
# DMSC ROM Version     : [0, 1, 1, 1]
# R5 ROM Version       : [0, 1, 1, 1]
#


if (len(sys.argv) != 2):
    print ("Usage:\n  python3 ./uart_boot_scoid.py /dev/ttyUSB0")
    sys.exit()

print( "SoC type detector...\n")


port = sys.argv[1]
dev = serial.Serial()
dev.port = port
dev.baudrate = 115200
dev.timeout = 0

try:
    dev.open()
except:
    print( "Invalid port or port is busy!" )
    exit()

# Get 10 continuous
num_continuous_c_char = 1
soc_detect_timeout_sec = 30
print( "Detecting SoC..." )
end_time = time.time() + soc_detect_timeout_sec
cnt = num_continuous_c_char
while True:
    if cnt == 0 or time.time() >= end_time:
        break

    ch = dev.read(1)

    if ch == b'':
        continue

    if ch == b'C':
        print( "#" )
        cnt-=1
    else:
        cnt=num_continuous_c_char

print()
if cnt == 0:
    print( "SoC Detected!\n" )
else:
    print( "No valid SoC Detected! Make Sure your device is in UART boot mode.\n" )
    dev.close()
    exit()

print( "Please Reset the SoC.")

soc_id_sm_timeout_sec = 30
soc_id = b''
soc_id_sm_state = 0
soc_id_sm_end_time = time.time() + soc_id_sm_timeout_sec
soc_id_sm_success = False
while True:
    if time.time() >= soc_id_sm_end_time:
        break

    ch = dev.read(1)
    if ch == b'':
        continue

    print( "#", end="" )

    if soc_id_sm_state == 0:
        # Waiting for starting character
        if ch == b'0':
            soc_id = b'0'
            soc_id_sm_state = 1
    elif soc_id_sm_state == 1:
        # Wait for first C after SoC id
        if ch == b'C':
            soc_id_sm_state = 2
        else:
            soc_id += ch
    elif soc_id_sm_state == 2:
        # Wait for second C after SoC id
        if ch == b'C':
            soc_id_sm_success = True
        break

print()
if soc_id_sm_success == True:
    print( "SoC ID : " )
    print( soc_id )
else:
    print( "No valid SoC ID detected!" )
    exit()

lines = [ soc_id.decode()+'\n' ]


# Convert to byte array
bin_arr = [binascii.unhexlify(x.rstrip()) for x in lines]
# print bin_arr

bin_str = b"".join(bin_arr)
# print bin_str


# typedef struct __attribute__((packed, aligned(4)))
# {
#     uint8_t             subBlockId;
#     uint8_t             size;
#     uint8_t             fixed[2];
#     uint8_t             devName[SOCID_SECINFO_DEVNAME_LEN];
#     uint32_t            devType;
#     uint32_t            dmscVersion;
#     uint32_t            r5Version;
# }
# SOCID_PubInfo_t;
pubInfoStr = "BB2B12B4B4B4B"
# /* Secure Info applicable only for EMU/HS device types */
# typedef struct __attribute__((packed, aligned(4)))
# {
#     uint8_t             subBlockId;
#     uint8_t             size;
#     uint16_t            secPrime;
#     uint16_t            keyRevision;
#     uint16_t            keyCount;
#     uint32_t            tiRootKeyHash[SOCID_SECINFO_ROOTKEYHASH_LEN];
#     uint32_t            custRootKeyHash[SOCID_SECINFO_ROOTKEYHASH_LEN];
#     uint32_t            uniqueID[SOCID_SECINFO_UNIQUEID_LEN];
# }
# SOCID_SecInfo_t;

secInfoStr = "BBHHH64B64B32B"

# Decode byte array to struct

# /* SOC ID definition */
# typedef struct __attribute__((packed, aligned(4)))
# {
#     uint32_t            numBlocks;
numBlocks = list(struct.unpack("I", bin_str[0:4]))
numBlocks = numBlocks[0]
#     SOCID_PubInfo_t     pubInfo;
pubROMInfo = struct.unpack(pubInfoStr, bin_str[4:32])
#     SOCID_SecInfo_t     secInfo;
if numBlocks > 1:
    secROMInfo = struct.unpack(secInfoStr, bin_str[32:200])
# }
# SOCID_Obj;
#

buff = ""

# numBlocks
buff = "\n-----------------------\nSoC ID Header Info:\n-----------------------\nNumBlocks            :"+str(numBlocks)

# pubInfo
buff+= "\n-----------------------\nSoC ID Public ROM Info:\n-----------------------\n"

# print pubROMInfo

buff+="SubBlockId           :"+str(pubROMInfo[0])+'\n'
buff+="SubBlockSize         :"+str(pubROMInfo[1])+'\n'
tmpList = list(pubROMInfo[4:15])
hexList = [hex(i) for i in tmpList]
deviceName = "".join(chr(int(c, 16)) for c in hexList[0:])
buff+="DeviceName           :"+str(deviceName)+'\n'
tmpList = list(pubROMInfo[16:20])
hexList = [hex(i) for i in tmpList]
deviceType = "".join(chr(int(c, 16)) for c in hexList[0:])
buff+="DeviceType           :"+str(deviceType)+'\n'
dmscROMVer = list(pubROMInfo[20:24])
dmscROMVer.reverse()
buff+="DMSC ROM Version     :"+str(dmscROMVer)+'\n'
r5ROMVer = list(pubROMInfo[24:28])
r5ROMVer.reverse()
buff+="R5 ROM Version       :"+str(r5ROMVer)+'\n'

if numBlocks > 1:
    # secInfo
    buff+= "\n-----------------------\nSoC ID Secure ROM Info:\n-----------------------\n"
    # print secROMInfo
    buff+="Sec SubBlockId       :"+ str(secROMInfo[0])+'\n'
    buff+="Sec SubBlockSize     :"+ str(secROMInfo[1])+'\n'
    buff+="Sec Prime            :"+ str(secROMInfo[2])+'\n'
    buff+="Sec Key Revision     :"+ str(secROMInfo[3])+'\n'
    buff+="Sec Key Count        :"+ str(secROMInfo[4])+'\n'
    tmpList = list(secROMInfo[5:69])
    tiMPKHash = "".join("{:02x}".format(x) for x in tmpList)
    buff+="Sec TI MPK Hash      :"+ str(tiMPKHash)+'\n'
    tmpList = list(secROMInfo[69:133])
    custMPKHash = "".join("{:02x}".format(x) for x in tmpList)
    buff+="Sec Cust MPK Hash    :"+ str(custMPKHash)+'\n'
    tmpList = list(secROMInfo[133:167])
    uID = "".join("{:02x}".format(x) for x in tmpList)
    buff+="Sec Unique ID        :"+ str(uID)+'\n'

print( buff )

try:
    out_filename = sys.argv[2]
    with open( out_filename, 'w' ) as fl:
        fl.write(buff)
except:
    pass
