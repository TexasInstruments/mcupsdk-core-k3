In the R5 SPL Linux Boot flow, the chosen node in the device tree is populated
by U-Boot. However, since there is no U-Boot in the  R5 SBL Linux Boot flow,
the chosen node in the device tree needs to be updated with bootargs and uart details

Steps to modify k3-j722s-evm.dtb :

- Clone ti-linux-kernel repo for j722s
- Replace chosen node with the following in arch/arm64/boot/dts/ti/k3-j722s-evm.dts file
chosen {
		stdout-path = "serial2:115200n8";
		bootargs = "console=ttyS2,115200n8 earlycon=ns16550a,mmio32,0x02800000 root=/dev/mmcblk1p2 rw rootfstype=ext4 rootwait";
	};
- Execute the following command - make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- defconfig ti_arm64_prune.config -j8
- Execute the following command - make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- dtbs -j8
- Copy arch/arm64/boot/dts/ti/k3-j722s-evm.dtb to <mcu plus sdk path>/tools/boot/linuxAppimageGen/board/j722s-evm/linuxBinaries
