#! /bin/sh

usage ()
{
  echo "
Usage:
  --device              SD block device node (e.g /dev/sda or /dev/sdb)
"
	exit 1
}

unmount_all_partitions ()
{
  for i in `ls -1 $device*`; do
    echo "unmounting device '$i'"
    umount $i 2>/dev/null
  done
}

# Main script starts from here
if [ `whoami` != "root" ]; then
	echo "This script should be called with sudo!!"
	usage
	exit 1
fi

while [ $# -gt 0 ]; do
  case $1 in
    --help | -h)
      usage
      ;;
    --device) shift; device=$1; shift; ;;
    *) usage ;;
  esac
done

if [ ! -b $device ]; then
   echo "ERROR: $device is not a block device file"
	 usage
   exit 1;
fi

echo "************************************************************"
echo "*         THIS WILL DELETE ALL THE DATA ON $device         *"
echo "*                                                          *"
echo "*         WARNING! Make sure your computer does not go     *"
echo "*                  in to idle mode while this script is    *"
echo "*                  running. The script will complete,      *"
echo "*                  but your eMMC may be corrupted.         *"
echo "*                                                          *"
echo "*         Press <ENTER> to confirm....                     *"
echo "************************************************************"
read junk

unmount_all_partitions
sync

cat << END | fdisk $device
n
p
1

+62M
n
p
2


t
1
c
a
1
w
END

unmount_all_partitions
sleep 3

PARTITION1=${device}1
PARTITION2=${device}2

# make partitions.
echo "Formatting ${device} ..."
if [ -b ${PARTITION1} ]; then
	mkfs.vfat -F 32 -n "boot" ${PARTITION1}
else
	echo "Cant find boot partition in /dev"
fi

if [ -b ${PARITION2} ]; then
	mkfs.ext4 -L "rootfs" ${PARTITION2}
else
	echo "Cant find rootfs partition in /dev"
fi

echo "Partitioning and formatting completed!"
