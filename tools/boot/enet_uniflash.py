import os
import sys
import time
import math
import socket
import argparse
import struct
import ipaddress
import shlex

try:
    from tqdm import tqdm
except ImportError:
    print('[ERROR] Dependent modules not installed, use below pip command to install them. Ensure proxy for pip is setup if needed.')
    print()
    print('python -m pip install tqdm --proxy={http://your proxy server:port or leave blank if no proxy}')
    sys.exit(2)

BOOTLOADER_UNIFLASH_PACKET_SIZE                      = 1464
BOOTLOADER_UNIFLASH_SEQNUM_SIZE                      = 4
BOOTLOADER_UNIFLASH_MGCNUM_SIZE                      = 4
BOOTLOADER_UNIFLASH_OFFSET_SIZE                      = 4
BOOTLOADER_UNIFLASH_ERASESIZE_SIZE                   = 4
BOOTLOADER_UNIFLASH_PAYLOAD_SIZE                     = BOOTLOADER_UNIFLASH_PACKET_SIZE + BOOTLOADER_UNIFLASH_SEQNUM_SIZE + BOOTLOADER_UNIFLASH_MGCNUM_SIZE
BOOTLOADER_UNIFLASH_BUF_SIZE                         = 1024*1024 # 1 MB This has to be a 256 KB aligned value, because flash writes will be block oriented
BOOTLOADER_UNIFLASH_HEADER_SIZE                      = 32 # 32 B
BOOTLOADER_UNIFLASH_HEADER_PKT_SIZE                  = BOOTLOADER_UNIFLASH_HEADER_SIZE + BOOTLOADER_UNIFLASH_SEQNUM_SIZE + BOOTLOADER_UNIFLASH_MGCNUM_SIZE

BOOTLOADER_UNIFLASH_MAX_FILE_PKT_NUM                 = math.floor((BOOTLOADER_UNIFLASH_BUF_SIZE - BOOTLOADER_UNIFLASH_HEADER_PKT_SIZE)/BOOTLOADER_UNIFLASH_PAYLOAD_SIZE)

BOOTLOADER_UNIFLASH_PKT_MAGIC_NUMBER                 = 0x05B1C00D # SBL GOOD
BOOTLOADER_UNIFLASH_PKT_ACK                          = 0x05B10ACD # SBL AC(K)D
BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER         = bytearray([0x42, 0x4C ,0x55, 0x46]) # BLUF
BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER         = 0x52554C42 # BLUR

BOOTLOADER_UNIFLASH_OPTYPE_FLASH                     = bytearray([0xF0, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY              = bytearray([0xF1, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP                 = bytearray([0xF2, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY_XIP          = bytearray([0xF3, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_FLASH_TUNING_DATA         = bytearray([0xF4, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE               = bytearray([0xFE, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_EMMC_FLASH                = bytearray([0xF5, 0x00, 0x00, 0x00])
BOOTLOADER_UNIFLASH_OPTYPE_EMMC_VERIFY               = bytearray([0xF6, 0x00, 0x00, 0x00])

BOOTLOADER_UNIFLASH_IMAGE_TYPE_MULTICORE             = bytearray([0x4D, 0x43, 0x00, 0x00]) # MC
BOOTLOADER_UNIFLASH_IMAGE_TYPE_UBOOT                 = bytearray([0x55, 0x42, 0x00, 0x00]) # UB

BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS                = 0x00000000
BOOTLOADER_UNIFLASH_STATUSCODE_MAGIC_ERROR            = 0x10000001
BOOTLOADER_UNIFLASH_STATUSCODE_OPTYPE_ERROR           = 0x20000001
BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR            = 0x30000001
BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR     = 0x40000001
BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR      = 0x50000001

ENET_START_FRAME                                      = 0xAACBEDFA

TMP_SUFFIX = ".tmp"
DEADBABE = bytearray([0xBE, 0xBA, 0xAD, 0xDE])

optypewords = {
    "flash" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
    "flashverify" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY,
    "flash-xip" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
    "flashverify-xip" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY_XIP,
    "flash-phy-tuning-data" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH_TUNING_DATA,
    "erase" : BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
    "flash-emmc":BOOTLOADER_UNIFLASH_OPTYPE_EMMC_FLASH,
    "flashverify-emmc":BOOTLOADER_UNIFLASH_OPTYPE_EMMC_VERIFY,
}

statuscodes = {
    BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS : "[FLASH] (SUCCESS) Flashing successful !!!\n",
    BOOTLOADER_UNIFLASH_STATUSCODE_MAGIC_ERROR : "[FLASH] (ERROR) Incorrect magic number in file header !!!\n",
    BOOTLOADER_UNIFLASH_STATUSCODE_OPTYPE_ERROR : "[FLASH] (ERROR) Invalid file operation type sent !!!\n",
    BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR : "[FLASH] (ERROR) Flashing failed !!!\n",
    BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR : "[FLASH] (ERROR) Flash verify failed !!!\n",
    BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR : "[FLASH] (ERROR) Flash erase failed !!!\n",
}

bar_cursize = 0
bar_filesize = 0

class LineCfg():
    def __init__(self, line=None, filename=None, optype=None, offset=None, erase_size=None, flashwriter=None):
        self.line = line
        self.filename = filename
        self.optype = optype
        self.offset = offset
        self.flashwriter = flashwriter
        self.erase_size = erase_size
        self.found_flashwriter_cmd = False
        self.ops_invalid = False
        self.exit_now = False

    # Takes a string of comma separated key=value pairs and parses into a dictionary
    def parse_to_dict(self, config_string):
        config_dict = dict()
        splitter = shlex.shlex(config_string, posix=True)
        splitter.commenters="#"
        splitter.whitespace = ' '
        splitter.whitespace_split = True

        for key_value_pair in splitter:
            kv = key_value_pair.strip()
            if not kv:
                continue
            kv_t = kv.split('=', 1)
            if(len(kv_t)==1):
                #error, no value
                pass
            else:
                config_dict[kv_t[0]] = kv_t[1]

        return config_dict

    # Validate the configuration
    def validate(self):
        status = 0
        optypes = ["flash", "flashverify", "erase", "flash-xip", "flashverify-xip", "flash-phy-tuning-data", "flash-emmc", "flashverify-emmc"]
        if(self.line!=None):
            config_dict = self.parse_to_dict(self.line)
            if not config_dict:
                status = "invalid_line"
            else:
                # check for flashwriter
                if "--flash-writer" not in config_dict.keys():
                    if "--operation" not in config_dict.keys():
                        status = "[ERROR] No/invalid file operation specified !!!"
                        return status
                    else:
                        self.optype = config_dict["--operation"]

                    if(self.optype == "flash" or self.optype == "flashverify" or self.optype == "erase" or self.optype == "flash-emmc" or self.optype == "flashverify-emmc"):
                        if "--flash-offset" not in config_dict.keys():
                            status = "[ERROR] Operation selected was {}, but no offset provided !!!".format(self.optype)
                            return status
                        else:
                            self.offset = config_dict["--flash-offset"]

                    if(self.optype == "flash" or self.optype == "flashverify" or self.optype == "flash-xip" or self.optype == "flashverify-xip" or self.optype == "flash-emmc" or self.optype == "flashverify-emmc"):
                        if "--file" not in config_dict.keys():
                            status = "[ERROR] Operation selected was {}, but no filename provided !!!".format(self.optype)
                            return status
                        else:
                            self.filename = config_dict["--file"]

                    if(self.optype == "erase"):
                        if "--erase-size" not in config_dict.keys():
                            status = "[ERROR] Operation selected was {}, but no erase size provided !!!".format(self.optype)
                            return status
                        else:
                            self.erase_size = config_dict["--erase-size"]

                    #No errors in parsing, now validate params to the extent possible
                    if(self.optype not in ("erase", "flash-phy-tuning-data")):
                        try:
                            f = open(self.filename)
                        except FileNotFoundError:
                            status = "[ERROR] File not found !!!"
                            return status

                    if(self.optype not in optypes):
                        status = "[ERROR] Invalid File Operation type !!!"
                        return status

                # we have a flash writer argument, other arguments are moot
                else:
                    self.flashwriter = config_dict["--flash-writer"]
                    try:
                        f = open(self.flashwriter)
                    except FileNotFoundError:
                        status = "[ERROR] Flashwriter file not found !!!"
                        return status
        else:
            # Should not hit this
            status = -1
        return status

class FileCfg():
    def __init__(self, filename=None):
        self.filename = filename
        self.lines = list()
        self.cfgs = list()
        self.errors = list()
        self.flash_writer_index = None

    def parse(self):
        f = open(self.filename, "r")
        lines = f.readlines()
        f.close()
        parse_status = 0
        linecount = 0
        found_flashwriter = False
        valid_cfg_count = 0

        for line in lines:
            linecfg = LineCfg(line=line)
            status = linecfg.validate()

            if(status != 0 and status != "invalid_line"):
                self.errors.append("[ERROR] Parsing error found on line {} of {}\n{}\n".format(linecount+1, self.filename, status))
            else:
                if(status != "invalid_line"):
                    if(linecfg.flashwriter != None):
                        if(found_flashwriter == True):
                            # error, another instance of flashwriter found
                            flash_writer_error_msg = "[ERROR] Redefinition of flash writer !!!"
                            self.errors.append("[ERROR] Parsing error found on line {} of {}\n{}\n".format(linecount+1, self.filename, flash_writer_error_msg))
                        else:
                            found_flashwriter = True
                            self.cfgs.append(linecfg)
                            self.lines.append(line.rstrip('\n'))
                            self.flash_writer_index = valid_cfg_count
                            valid_cfg_count += 1
                    else:
                        self.cfgs.append(linecfg)
                        self.lines.append(line.rstrip('\n'))
                        valid_cfg_count += 1
            linecount += 1

        if(len(self.errors) > 0):
            # Some commands have errors
            parse_status = "Parsing config file ... ERROR. {} error(s).\n\n".format(len(self.errors)) + "\n".join(self.errors)

        return parse_status

# Parse and validate input arguments, config file
def parse():
    parser = argparse.ArgumentParser(description="Helper script to upload appimage files via ethernet to AWR2944EVM",
                                     formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--hostIP",
                        metavar='ip',
                        type=str,
                        help="Host PC IP address",
                        default="192.168.0.136")
    parser.add_argument("--hostPort",
                        metavar='n',
                        type=int,
                        help="Host PC UDP Port number",
                        default=5001)
    parser.add_argument("--boardIP",
                        metavar='ip',
                        type=str,
                        help="EVM IP address",
                        default="192.168.0.195")
    parser.add_argument("--boardPort",
                        metavar='n',
                        type=int,
                        help="EVM UDP Port number",
                        default=5001)
    parser.add_argument("--debug", "-d",
                        action="store_true",
                        help="Print debug statements")
    parser.add_argument("--cfg",
                        metavar="myconfig.cfg",
                        type=str,
                        help="Path to config file",
                        default="default_sbl_eth.cfg")
    args = parser.parse_args()

    try:
        hostIP = ipaddress.ip_address(args.hostIP)
    except ValueError:
        print("[ERROR] Bad Host IP Address entered")
        sys.exit(1)
    try:
        boardIP = ipaddress.ip_address(args.boardIP)
    except ValueError:
        print("[ERROR] Bad EVM IP Address entered")
        sys.exit(1)

    if not os.path.exists(args.cfg):
        print("[ERROR] Config file not found")
        sys.exit(3)
    else:
        print("[LOG] Parsing config file ...")
        filecfg = FileCfg(args.cfg)
        parse_status = filecfg.parse()
        if(parse_status != 0):
            print(parse_status)
            sys.exit()
        else:
            print("[LOG] Ensure that sbl_qspi_enet has already been sent over before running this script.")
            # No errors, can proceed to flash
            print("[LOG] Found {} command(s) !!!".format(len(filecfg.cfgs)))
    return args, filecfg

# Make custom payloads from given file by splitting into multiple chunks
def packetize(linecfg: LineCfg, debug: bool):
    total_packet_list = []
    total_size = 0
    filesize = 0

    if linecfg.optype not in ("erase","flash-phy-tuning-data"):
        filesize = os.path.getsize(linecfg.filename)
        total_num_packets = math.ceil(filesize/BOOTLOADER_UNIFLASH_PACKET_SIZE)
        num_files = math.ceil(total_num_packets/BOOTLOADER_UNIFLASH_MAX_FILE_PKT_NUM)
        with open(linecfg.filename, 'rb') as f:
            file_bytes = bytes(f.read())
    else:
        num_files = 1
        total_num_packets = 1
    last_file_size = total_num_packets - ((num_files-1)*BOOTLOADER_UNIFLASH_MAX_FILE_PKT_NUM)
    file_sizes = [BOOTLOADER_UNIFLASH_MAX_FILE_PKT_NUM]*(num_files-1)
    file_sizes.append(last_file_size)

    for i in range(num_files):
        file_packet_list = []

        # Add magic number to differentiate from other packets
        # Add SEQ number
        # Add Uniflash header
        # Fill total number of packets in rsv2 of header
        data_bytes = bytearray(BOOTLOADER_UNIFLASH_PKT_MAGIC_NUMBER.to_bytes(length=BOOTLOADER_UNIFLASH_MGCNUM_SIZE, byteorder='little', signed=False))
        data_bytes += bytearray(BOOTLOADER_UNIFLASH_SEQNUM_SIZE)
        data_bytes += BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER
        data_bytes += optypewords[linecfg.optype]
        if linecfg.optype == "flash-xip" or linecfg.optype == "flashverify-xip" or linecfg.optype == "flash-phy-tuning-data":
            data_bytes += DEADBABE
        else:
            if (linecfg.offset).startswith('0x'):
                offset = int(linecfg.offset, 16)
            else:
                offset = int(linecfg.offset, 10)
            # change offset for each partial file
            data_bytes += bytearray(((i*BOOTLOADER_UNIFLASH_BUF_SIZE) + offset).to_bytes(length=BOOTLOADER_UNIFLASH_OFFSET_SIZE, byteorder='little', signed=False))
        if linecfg.optype == "erase":
            data_bytes += bytearray((linecfg.erase_size).to_bytes(length=BOOTLOADER_UNIFLASH_ERASESIZE_SIZE, byteorder='little', signed=False))
        else:
            data_bytes += DEADBABE
        data_bytes += bytearray(filesize.to_bytes(length=BOOTLOADER_UNIFLASH_ERASESIZE_SIZE, byteorder='little', signed=False))
        # reserved bytes in uniflash header
        # fill partial file packet count in rsv2 of uniflash header
        data_bytes += DEADBABE #rsv1
        data_bytes += bytearray((file_sizes[i]+1).to_bytes(length=BOOTLOADER_UNIFLASH_SEQNUM_SIZE, byteorder='little', signed=False)) #rsv2
        data_bytes += DEADBABE #rsv3
        if debug:
            print("[DEBUG] Part {} Packet {}: ".format(i, 0))
            print(data_bytes.hex())
        file_packet_list.extend([data_bytes])

        if linecfg.optype not in ("erase","flash-phy-tuning-data"):
            for j in range(file_sizes[i]):
                # Add magic number to differentiate from other packets
                # Add SEQ number
                # Add actual data from file
                data_bytes = bytearray(BOOTLOADER_UNIFLASH_PKT_MAGIC_NUMBER.to_bytes(length=BOOTLOADER_UNIFLASH_MGCNUM_SIZE, byteorder='little', signed=False))
                data_bytes += bytearray((j+1).to_bytes(length=BOOTLOADER_UNIFLASH_SEQNUM_SIZE, byteorder='little', signed=False))
                start = (i*BOOTLOADER_UNIFLASH_BUF_SIZE) + (j*BOOTLOADER_UNIFLASH_PACKET_SIZE)
                end = start + BOOTLOADER_UNIFLASH_PACKET_SIZE
                if end >= len(file_bytes):
                    # end = -1
                    data_bytes += file_bytes[start:]
                else:
                    data_bytes += file_bytes[start:end]
                if debug:
                    print("[DEBUG] Part {} Packet {}: ".format(i, j+1))
                    print(data_bytes.hex())
                file_packet_list.extend([data_bytes])
        total_packet_list.append(file_packet_list)
    total_size = filesize + (total_num_packets*8) + 32
    return total_size, total_num_packets, total_packet_list

# Setup UDP socket
def setup(bind_ip: str, bind_port: int):
    print("[LOG] Creating socket")
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    sock.settimeout(8)
    sock.bind((bind_ip, bind_port))
    return sock

# Perform cleanup functions - close socket
def cleanup(sock: socket.SocketType):
    print("[LOG] Closing socket")
    sock.close()

# Transfer with Stop-and-Wait ARQ protocol
def transceive(sock: socket.SocketType, payloads: list, num_packets: int, transmit_ip: str, transmit_port: int, filename: str, total_size: int, debug: bool=False):
    flashed = False

    bar_filesize = os.path.getsize(filename)
    bar = tqdm(total=bar_filesize, unit="bytes", leave=False, desc='Sending {}'.format(filename))
    tstart = time.time()
    for i in range(num_packets):
        sock.sendto(payloads[i], (transmit_ip, transmit_port))
        ackd = False
        pkt_timeout_count = 0
        while not ackd:
            try:
                data, addr = sock.recvfrom(8)
                code = struct.unpack('<II', data)
                if addr[0] == transmit_ip:
                    if (code[0] == i) and (code[1] == BOOTLOADER_UNIFLASH_PKT_ACK):
                        ackd = True
                        if debug:
                            print("[TRANSFER] (SUCCESS) ACK received for packet {}".format(i))
                        bar.update(len(payloads[i]))
                        bar.refresh()
            except socket.timeout:
                pkt_timeout_count += 1
                if debug:
                    print("[TRANSFER] (TIMEOUT) ACK timed out for packet {}".format(i))
                if pkt_timeout_count == 5:
                    print("[ERROR] Connection timed out too many times for same packet. Check connection to EVM.")
                    print("        Power cycle EVM and run this script again !!!")
                    bar.close()
                    sock.close()
                    sys.exit(6)
                sock.sendto(payloads[i], (transmit_ip, transmit_port))
    tstop = time.time()
    timetaken = round(tstop-tstart, 2)
    while not flashed:
        data, addr = sock.recvfrom(8)
        code = struct.unpack('<II', data)
        if addr[0] == transmit_ip:
            if code[0] == BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER:
                flashed = True
                if code[1] in statuscodes.keys():
                    status = statuscodes[code[1]]
                else:
                    status = "[FLASH] (ERROR) Invalid status code in response !!!"
    bar.close()
    return status, timetaken

def get_numword(s):
    numword = None
    if(s.startswith('0x')):
        numword = int(s, 16)
    else:
        numword = int(s, 10)
    return numword

def create_temp_file(linecfg):
    '''
    File header struct used in the target side :

    typedef struct Bootloader_UniflashFileHeader_s
    {
        uint32_t magicNumber;
        /* BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER */

        uint32_t operationTypeAndFlags;
        /* LSByte - Operation Type:flash, verify flash or erase */

        uint32_t offset;
        /* Offset to flash, verify flash or erase flash */

        uint32_t eraseSize;
        /* Size of flash to erase */

        uint32_t actualFileSize;
        /* Size of the file sent. This is needed because xmodem returns a padded file size */

        uint32_t flashType;
        /* Flash type used for flashing. Whether serial/parallel flash*/

        uint32_t rsv2;
        uint32_t rsv3;
        /* Reserved */
    } Bootloader_UniflashFileHeader;

    So we need to use same struct to pack in python
    '''
    file_header_str = '<LLLLLLLL'

    if(linecfg.optype in ("erase", "flash-phy-tuning-data")):
        # No separate file required
        tempfilename = "{}_command".format(linecfg.optype)
    else:
        tempfilename = linecfg.filename + TMP_SUFFIX

    f = open(tempfilename, "wb")

    '''
    # Construct the header now, first define the reserved word
    rsv_word = 0xDEADBABE

    # Determine the offset if applicable
    offset_val = rsv_word
    if(linecfg.optype not in ("flash-xip", "flashverify-xip", "flash-phy-tuning-data")):
        offset_val = get_numword(linecfg.offset)

    flash_type = rsv_word
    if(linecfg.optype not in ("flash-emmc", "flashverify-emmc", "flash-phy-tuning-data")):
        flash_type = flashType[linecfg.flashtype]

    # Determine the erase size if applicable
    erase_size_val = rsv_word
    if(linecfg.optype in ("erase")):
        erase_size_val = get_numword(linecfg.erase_size)

    # Determine the actual file size if applicable, no original file in case of erase or phy tuning
    actual_file_size = 0
    if(linecfg.optype not in ("erase","flash-phy-tuning-data")):
        actual_file_size = os.path.getsize(linecfg.filename)

    file_header = struct.pack(file_header_str,
                              BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                              optypewords[linecfg.optype],
                              offset_val,
                              erase_size_val,
                              actual_file_size,
                              flash_type, rsv_word, rsv_word
                             )

    # Write header to file
    f.write(file_header)
    '''

    # No original file in case of erase or phy tuning
    if(linecfg.optype not in ("erase","flash-phy-tuning-data")):
        # copy the original file to this file
        original_file = open(linecfg.filename, "rb")
        f.write(original_file.read())
        original_file.close()

    f.close()

    return tempfilename

def send_file_by_parts(l_cfg, s_port, args):
    orig_f_name = l_cfg.filename
    orig_offset = l_cfg.offset

    f = open(orig_f_name, "rb")
    f_bytes = f.read()
    f.close()

    num_parts   = int(len(f_bytes) / BOOTLOADER_UNIFLASH_BUF_SIZE)
    remain_size = len(f_bytes) % BOOTLOADER_UNIFLASH_BUF_SIZE
    total_time_taken = 0


    for i in range(0, num_parts):

        start = i*BOOTLOADER_UNIFLASH_BUF_SIZE
        end = start+BOOTLOADER_UNIFLASH_BUF_SIZE

        part_data = f_bytes[start:end]
        part_filename = orig_f_name + ".part{}".format(i+1)
        # make the partial file
        f = open(part_filename, "wb")
        f.write(part_data)
        f.close()

        # temporarily change this to the partial filename
        l_cfg.filename = part_filename
        l_cfg.offset = hex(get_numword(orig_offset) + i*BOOTLOADER_UNIFLASH_BUF_SIZE)

        # send the partial file normally
        tempfilename = create_temp_file(l_cfg)

        total_size, num_packets, total_packet_list = packetize(l_cfg, args.debug)


        for partial_file in total_packet_list:

            status, timetaken = transceive(s_port, partial_file, len(partial_file), args.boardIP, args.boardPort, l_cfg.filename, total_size)
            total_time_taken += timetaken
            if status != statuscodes[BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS]:
                print(status)
                print("[ERROR] Something went wrong")
                print("        Power cycle EVM and run this script again !!!")
                sys.exit(7)
            print("[STATUS] Sent file {} of size {} bytes in {}s.".format(l_cfg.filename, os.path.getsize(l_cfg.filename), total_time_taken))
            print(status)
            break

        # delete the temporary file
        os.remove(part_filename)
        os.remove(tempfilename)

    # Send the last part, if there were residual bytes
    if(remain_size > 0):
        start = num_parts*BOOTLOADER_UNIFLASH_BUF_SIZE

        part_data = f_bytes[start:]
        part_filename = orig_f_name + ".part{}".format(num_parts+1)

        # make the partial file
        f = open(part_filename, "wb")
        f.write(part_data)
        f.close()

        # temporarily change this to the partial filename
        l_cfg.filename = part_filename
        l_cfg.offset = hex(get_numword(orig_offset) + num_parts*BOOTLOADER_UNIFLASH_BUF_SIZE)

        # send the partial file normally
        tempfilename = create_temp_file(l_cfg)
        total_size, num_packets, total_packet_list = packetize(l_cfg, args.debug)


        for partial_file in total_packet_list:
            status, timetaken = transceive(s_port, partial_file, len(partial_file), args.boardIP, args.boardPort, l_cfg.filename, total_size)
            total_time_taken += timetaken
            if status != statuscodes[BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS]:
                print(status)
                print("[ERROR] Something went wrong")
                print("        Power cycle EVM and run this script again !!!")
                sys.exit(7)
            print("[STATUS] Sent file {} of size {} bytes in {}s.".format(l_cfg.filename, os.path.getsize(l_cfg.filename), total_time_taken))
            print(status)

        # delete the temporary file
        os.remove(part_filename)
        os.remove(tempfilename)

    # revert back the original filename and offset
    l_cfg.filename = orig_f_name
    l_cfg.offset = orig_offset

    return status, total_time_taken

addr="test"
if __name__ == "__main__":
    args, filecfg = parse()
    sock = setup(args.hostIP, args.hostPort)
    try:
        # Wait for EVM linkup
        linkup = False
        linkup_timeout_count = 0
        while linkup is False:
            try:
                print("Starting Linkup ...")
                data, addr = sock.recvfrom(8)

                print("Received.")
                print(addr)
                code = struct.unpack('<II', data)
                if addr[0] == args.boardIP:
                    if code[0] == BOOTLOADER_UNIFLASH_PKT_MAGIC_NUMBER:
                        linkup = True
                        if code[1] == BOOTLOADER_UNIFLASH_PKT_ACK:
                            print("")
                            print("[LINKUP] (SUCCESS) EVM Linked up. Starting transfer ...")
                            print("")
            # linkup might timeout 1 or 2 times due to the small socket timeout, ignore this.
            # if more than 5 times, then something seriously wrong
            except socket.timeout:
                linkup_timeout_count += 1
                if linkup_timeout_count == 5:
                    print("[ERROR] Connection timed out too many times for link-up. Check connection to EVM.")
                    print("        Power cycle EVM and run this script again !!!")
                    sock.close()
                    sys.exit(3)

        # Send each file
        for index in range(0,len(filecfg.cfgs)):
            if index != filecfg.flash_writer_index:
                total_size, num_packets, total_packet_list = packetize(filecfg.cfgs[index], args.debug)
                if((total_size > BOOTLOADER_UNIFLASH_BUF_SIZE) and (filecfg.cfgs[index].optype in ["flash", "flashverify"])):
                    print("[INFO] Size of the file {} is more than receive buffer size, sending by parts ...".format(filecfg.cfgs[index].filename))
                    send_file_by_parts(filecfg.cfgs[index], sock, args)
                else:
                    total_time = 0
                    for partial_file in total_packet_list:
                        status, part_time = transceive(sock, partial_file, len(partial_file), args.boardIP, args.boardPort, filecfg.cfgs[index].filename, total_size)
                        total_time += part_time
                        if status != statuscodes[BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS]:
                            print(status)
                            print("[ERROR] Something went wrong")
                            print("        Power cycle EVM and run this script again !!!")
                            sys.exit(7)
                        print("[STATUS] Sent file {} of size {} bytes in {}s.".format(filecfg.cfgs[index].filename, os.path.getsize(filecfg.cfgs[index].filename), total_time))
                        print(status)

        print("[LOG] All commands from config file are executed !!!")

    except KeyboardInterrupt:
        tqdm.close()
        print("[ERROR] Operation cancelled by user")
        print("        Power cycle EVM and run this script again !!!")
        sys.exit(8)
