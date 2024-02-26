# Script to generate x509 debug certificate to
# do runtime JTAG debug port unlock in HSSE device.
# In HSSE device, the debug port is closed by default,
# TISCI message along with this certificate can be
# called runtime to unlock the JTAG debug functionality.
# Python 3 script

import argparse
import os
import subprocess
from random import randint
from textwrap import dedent

g_sha_to_use = "sha512"

g_dbg_types = {
	"DBG_PERM_DISABLE"   : '0',
	"DBG_SOC_DEFAULT"    : '1',
	"DBG_PUBLIC_ENABLE"  : '2',
    "DEBUG_PUBLIC_USER"  : '3',
	"DBG_FULL_ENABLE"    : '4',
	"DBG_SECURE_ENABLE"  : '5',
}

g_supported_socs =["am62ax"]

g_x509_template = '''
[ req ]
distinguished_name     = req_distinguished_name
x509_extensions        = v3_ca
prompt                 = no

dirstring_type = nobmp

[ req_distinguished_name ]
C                      = US
ST                     = SC
L                      = New York
O                      = Texas Instruments., Inc.
OU                     = DSP
CN                     = Albert
emailAddress           = Albert@gt.ti.com

[ v3_ca ]
basicConstraints = CA:true
1.3.6.1.4.1.294.1.3 = ASN1:SEQUENCE:swrv
1.3.6.1.4.1.294.1.8=ASN1:SEQUENCE:debug

[ swrv ]
swrv = INTEGER:{SWRV}

[ debug ]
debugUID     =  FORMAT:HEX,OCT:{DEVICE_UID}
debugType    =  INTEGER:{DBG_TYPE}
coreDbgEn    =  INTEGER:{NONSEC_DBG}
coreDbgSecEn =  INTEGER:{SEC_DBG}
'''

def get_cert(args):
    ''' Generating the x509 debug certificate config '''
    print("Generating debug certificate for {} ...".format(args.soc))

    swrev = args.swrv
    if(swrev is None):
        swrev = 0

    soc_uid = args.socUID
    if(soc_uid is None):
        soc_uid = "0000000000000000000000000000000000000000000000000000000000000000"

    dbg_type = g_dbg_types["DBG_FULL_ENABLE"]

    if(args.debugtype is not None):
        if(args.debugtype in g_dbg_types):
            dbg_type = g_dbg_types[args.debugtype]
        else:
            # Invalid debug extension, exit fail
            print("Invalid debug type argument, exiting ...")
            exit(2)

    if (args.soc == "am62ax"):
        nonsec_dbg = "0x0103"
        sec_dbg = "0x20212223"

    if(args.coreDbgEn is not None):
        nonsec_dbg = args.coreDbgEn

    if(args.coreDbgSecEn is not None):
        sec_dbg = args.coreDbgSecEn


    ret_cert = g_x509_template.format(SWRV=swrev, DEVICE_UID=soc_uid, DBG_TYPE=dbg_type, NONSEC_DBG=nonsec_dbg, SEC_DBG=sec_dbg)
    return dedent(ret_cert)


# arguments definition
my_parser = argparse.ArgumentParser(description="Generates a x509 debug certificate for run time JTAG debug unlock in HS device")

my_parser.add_argument('-s', '--soc',     type=str, required=True, help='SOC for which debug certificate has to be created. Supported SOCs: am62ax')
my_parser.add_argument('--key',           type=str, help='File with signing key inside it. Optional')
my_parser.add_argument('--swrv',          type=str, help='Software revision number. Required if you have specified a non-zero debug certificate revision in the secure boardcfg')
my_parser.add_argument('--socUID',        type=str, help='SOC unique ID. Required if board config does not allow wild card JTAG unlock')
my_parser.add_argument('--debugtype',     type=str, help='Debug type. Default to DBG_FULL_ENABLE ')
my_parser.add_argument('--coreDbgEn',     type=str, help='List of cores for which non-secure debug has to be enabled. Optional')
my_parser.add_argument('--coreDbgSecEn',  type=str, help='List of cores for which secure debug has to be enabled. Optional')

args = my_parser.parse_args()

if (args.soc in g_supported_socs):
    cert_str = get_cert(args)
else:
    print("{} is not a valid soc argument! Valid SOCs are : {}. Exiting ...".format(args.soc, ','.join(g_supported_socs)))
    exit(2)

key = "../../boot/signing/custMpk_"+args.soc+".pem"

if (args.key is not None):
    if (not os.path.exists(args.key)):
        print("Authentication key file not found! exiting ...")
        exit(2)
    else:
        key = args.key


cert_cfg_file_name = "temp_cert_config"+str(randint(111, 999))

with open(cert_cfg_file_name, "w+") as f:
	f.write(cert_str)

cert_name = "temp_cert"+str(randint(111, 999))

# Generate the certificate
subprocess.check_output('openssl req -new -x509 -key {} -nodes -outform DER -out {} -config {} -{}'.format(key, cert_name, cert_cfg_file_name, g_sha_to_use), shell=True)

output_header_file_name = "./soc/"+args.soc+"/debug_unlock_cert_hex.h"

copy_right_year = "2024"

subprocess.run(["python", "../../bin2c/bin2c.py", cert_name, output_header_file_name, "DEBUG_UNLOCK_X509_CERT", copy_right_year])

print("Debug unlock certificate created at {} ".format(output_header_file_name))

# remove the temporary files
os.remove(cert_cfg_file_name)
os.remove(cert_name)
