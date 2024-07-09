
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/ddr/soc/ddr_${common.getSocName()}`);
let staticConfig = soc.getStaticConfig();

let ddrSize = staticConfig.size;
let sdramIdxMax = staticConfig.sdramIdxMax;

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};

function getClockEnableIds(instance) {
    return staticConfig.clockIds;
}

let ddr_module = {
    displayName: "DDR",
    longDescription:
`
IMPORTANT NOTES
- Formula: sdramIdx = log2(connected SDRAM size) - 16
- When ECC is enabled, last 1/9th of the total SDRAM space is used for ECC storage and
the rest 8/9th is available for system use.
`,
    alwaysShowLongDescription: true,

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/ddr/templates/ddr_config.c.xdt",
            driver_init: "/drivers/ddr/templates/ddr_init.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/ddr/templates/ddr.h.xdt",
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: "/drivers/ddr/ddr",
        },
    },
    maxInstances: 1,
    defaultInstanceName: "CONFIG_DDR",
    config: [
        {
            name: "ddrConfigIncludeFileName",
            displayName: "DDR Configuration File",
            skipTests: [ "configLongDescription" ], /* skipping due to intermittent 502 errors when checking the weblink in long description */
            longDescription:
`
The file specified here is generated using the DDR SUBSYSTEM REGISTER CONFIGURATION tool.

IMPORTANT NOTES,
- A default DDR config file for TI EVM is pre-generated and used as default value.
- You can override this with your own EVM specific file.

To generate a DDR config file for your EVM
- Goto https://dev.ti.com/sysconfig
- Select product as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select the device of interest ( ${common.getSocName()} )
- Configure the DDR parameters using the tool
- Save the generated board_ddrReginit.h in your workspace
- Specify the path to this file including the filename in this text box
- Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
- Make sure that path to this is file set in your application include path, as needed.
`,
            default: soc.getDefaultDdrConfigFileName(),
        },
        {
            name: "eccEnableFlag",
            displayName: "Enable Inline ECC",
            longDescription:
`
IMPORTANT NOTES
- 3 Regions can be specified to enable inline ECC.
- The address (ECC start and end) is specified as an offset from the DDR region start
- If start address is greater than end address ECC in this range will be disabled
- ECC region size = ECC region end address - ECC region start address + 1
- When ECC is enabled, last 1/9th of the total SDRAM space is used for ECC storage and
the rest 8/9th is available for system use.
- When ECC is enabled, BIST engine primes only the 8/9th portion of the given
size. So the actual ECC end address will be lesser than the given ECC address.
`,
            default: false,
            onChange: function (inst, ui) {
                let hideEccAddr = true;
                if (inst.eccEnableFlag == true)
                {
                    hideEccAddr = false;
                }
                else
                {
                    inst.eccStart0 = 0;
                    inst.eccStart1 = 0;
                    inst.eccStart2 = 0;
                    inst.eccEnd0 = 0;
                    inst.eccEnd1 = 0;
                    inst.eccEnd2 = 0;
                    inst.eccEnd0Actual = 0;
                    inst.eccEnd1Actual = 0;
                    inst.eccEnd2Actual = 0;
                    ui.eccEnd0Actual.hidden = true;
                    ui.eccEnd1Actual.hidden = true;
                    ui.eccEnd2Actual.hidden = true;
                }
                ui.eccStart0.hidden = hideEccAddr;
                ui.eccEnd0.hidden = hideEccAddr;
                ui.eccStart1.hidden = hideEccAddr;
                ui.eccEnd1.hidden = hideEccAddr;
                ui.eccStart2.hidden = hideEccAddr;
                ui.eccEnd2.hidden = hideEccAddr;
            }
        },
        {
            name: "eccStart0",
            displayName: "ECC Region 0 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd0 == 0)
                {
                    inst.eccEnd0Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd0Actual = inst.eccEnd0 - Math.trunc((inst.eccEnd0- inst.eccStart0 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd0Actual/0x100000000);
                    eccEnd0Actual = (eccEnd0Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd0Actual = eccEnd0Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd0Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd0",
            displayName: "ECC Region 0 End Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd0 == 0)
                {
                    inst.eccEnd0Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd0Actual = inst.eccEnd0 - Math.trunc((inst.eccEnd0- inst.eccStart0 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd0Actual/0x100000000);
                    eccEnd0Actual = (eccEnd0Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd0Actual = eccEnd0Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd0Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd0Actual",
            displayName: "ECC Region 0 Actual End Address",
            longDescription:"It is the actual end address written into the ECC_R0_END_ADDR_REG.\n" +
                    "Becuase when inline ECC is enabled, BIST engine primes only the 8/9th portion of the \n" +
                    "the given size.\n" + "\n" +
                    " ECC Region 0 Actual End Address = (ECC Region 0 End Address - ((ECC Region 0 End Address\n" + "\n" +
                    "                                    - ECC Region 0 Start Address + 1)/9)  & ~0xFFFF\n",
            default: 0x00000000,
            hidden: true,
            readOnly: true,
            displayFormat: "hex",
        },
        {
            name: "eccStart1",
            displayName: "ECC Region 1 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd1 == 0)
                {
                    inst.eccEnd1Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd1Actual = inst.eccEnd1 - Math.trunc((inst.eccEnd1- inst.eccStart1 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd1Actual/0x100000000);
                    eccEnd1Actual = (eccEnd1Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd1Actual = eccEnd1Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd1Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd1",
            displayName: "ECC Region 1 End Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd1 == 0)
                {
                    inst.eccEnd1Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd1Actual = inst.eccEnd1 - Math.trunc((inst.eccEnd1- inst.eccStart1 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd1Actual/0x100000000);
                    eccEnd1Actual = (eccEnd1Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd1Actual = eccEnd1Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd1Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd1Actual",
            displayName: "ECC Region 1 Actual End Address",
            longDescription:"It is the actual end address written into the ECC_R1_END_ADDR_REG.\n" +
                    "Because when inline ECC is enabled, BIST engine primes only the 8/9th portion of the \n" +
                    "the given size.\n" + "\n" +
                    " ECC Region 1 Actual End Address = (ECC Region 1 End Address - ((ECC Region 1 End Address\n" + "\n" +
                    "                                      - ECC Region 1 Start Address + 1)/9)  & ~0xFFFF\n",
            default: 0x00000000,
            hidden: true,
            readOnly: true,
            displayFormat: "hex",
        },
        {
            name: "eccStart2",
            displayName: "ECC Region 2 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd2 == 0)
                {
                    inst.eccEnd2Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd2Actual = inst.eccEnd2 - Math.trunc((inst.eccEnd2- inst.eccStart2 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd2Actual/0x100000000);
                    eccEnd2Actual = (eccEnd2Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd2Actual = eccEnd2Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd2Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd2",
            displayName: "ECC Region 2 End Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
            onChange: function (inst,ui)
            {
                let hideEccActualAddr = false;
                if (inst.eccEnd2 == 0)
                {
                    inst.eccEnd2Actual = 0;
                    hideEccActualAddr = true;
                }
                else
                {
                    let eccEnd2Actual = inst.eccEnd2 - Math.trunc((inst.eccEnd2- inst.eccStart2 + 1)/9);
                    /* Javascript supports only 32-bit operands. But DDR size can be upto 32 GB. Calculate the offset value after 32-bit*/
                    let offset = Math.trunc(eccEnd2Actual/0x100000000);
                    eccEnd2Actual = (eccEnd2Actual & ~0xFFFF) >>> 0;
                    inst.eccEnd2Actual = eccEnd2Actual + (offset * 0x100000000); /* After bit operation, add the value back */
                }
                ui.eccEnd2Actual.hidden = hideEccActualAddr;
            }
        },
        {
            name: "eccEnd2Actual",
            displayName: "ECC Region 2 Actual End Address ",
            longDescription:"It is the actual end address written into the ECC_R2_END_ADDR_REG.\n" +
                    "Because when inline ECC is enabled, BIST engine primes only the 8/9th portion of the \n" +
                    "the given size.\n" + "\n" +
                    " ECC Region 2 Actual End Address = (ECC Region 2 End Address - ((ECC Region 2 End Address\n" + "\n" +
                    "                                      - ECC Region 2 Start Address + 1)/9)  & ~0xFFFF\n",
            default: 0x00000000,
            hidden: true,
            readOnly: true,
            displayFormat: "hex",
        },
        {
            name: "sdramIdx",
            displayName: "SDRAM Index",
            longDescription:
`
- Formula: sdramIdx = log2(connected SDRAM size) - 16
- The field configures the SDRAM_IDX in V2A_CTL_REG
- Used to determine the mask used to detect memory rollover and prevent
aliasing and false coherency issues
`,
            default: soc.getStaticConfig().sdramIdx,
        },
    ],
    validate: validate,
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
    getClockEnableIds,
};

function validate(instance, report) {

    let granule_size = 0x10000;

    let connectedDDREndAddress = Math.pow(2, (instance.sdramIdx + 16)) - 1;

    common.validate.checkNumberRange (instance, report, "sdramIdx", 0, sdramIdxMax, "hex");

    common.validate.checkNumberRange (instance, report, "eccStart0", 0, connectedDDREndAddress, "hex");
    common.validate.checkNumberRange (instance, report, "eccEnd0", 0, connectedDDREndAddress, "hex");

    common.validate.checkNumberRange (instance, report, "eccStart1", 0, connectedDDREndAddress, "hex");
    common.validate.checkNumberRange (instance, report, "eccEnd1", 0, connectedDDREndAddress, "hex");

    common.validate.checkNumberRange (instance, report, "eccStart2", 0, connectedDDREndAddress, "hex");
    common.validate.checkNumberRange (instance, report, "eccEnd2", 0, connectedDDREndAddress, "hex");

    let ddrSizeMaxWithECC = Math.trunc(((connectedDDREndAddress + 1) * 8) / 9);

    if ((instance.eccStart0 % granule_size) != 0)
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccStart0");
    }

    if ((instance.eccStart1 % granule_size) != 0)
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccStart1");
    }

    if ((instance.eccStart2 % granule_size) != 0)
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccStart2");
    }

    if ((instance.eccEnd0 != 0) && (((instance.eccEnd0 + 1) % granule_size) != 0))
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccEnd0");
    }

    if ((instance.eccEnd1 != 0) && (((instance.eccEnd1 + 1) % granule_size) != 0))
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccEnd1");
    }

    if ((instance.eccEnd2 != 0) && (((instance.eccEnd2 + 1) % granule_size) != 0))
    {
        report.logError( `ECC start address and size must aligned to 0x${granule_size.toString(16).toUpperCase()} B`,
            instance, "eccEnd2");
    }

    if (Math.trunc(instance.eccEnd0 - ((instance.eccEnd0 - instance.eccStart0 + 1)/9)) > ddrSizeMaxWithECC)
    {
        report.logError( `8/9th of the given ECC region should not fall under the last 1/9th region of the whole DDR
            (i.e from 0x${ddrSizeMaxWithECC.toString(16).toUpperCase()} to 0x${connectedDDREndAddress.toString(16).toUpperCase()})`,
            instance, "eccEnd0");
    }

    if (Math.trunc(instance.eccEnd1 - ((instance.eccEnd1 - instance.eccStart1 + 1)/9)) > ddrSizeMaxWithECC)
    {
        report.logError( `8/9th of the given ECC region should not fall under the last 1/9th region of the whole DDR
            (i.e from 0x${ddrSizeMaxWithECC.toString(16).toUpperCase()} to 0x${connectedDDREndAddress.toString(16).toUpperCase()})`,
            instance, "eccEnd1");
    }

    if (Math.trunc(instance.eccEnd2 - ((instance.eccEnd2 - instance.eccStart2 + 1)/9)) > ddrSizeMaxWithECC)
    {
        report.logError( `8/9th of the given ECC region should not fall under the last 1/9th region of the whole DDR
            (i.e from 0x${ddrSizeMaxWithECC.toString(16).toUpperCase()} to 0x${connectedDDREndAddress.toString(16).toUpperCase()})`,
            instance, "eccEnd2");
    }

    let eccRegionSize;

    if ((instance.eccStart0 != 0) || (instance.eccEnd0 != 0))
    {
        eccRegionSize = Math.log2(instance.eccEnd0 - instance.eccStart0 + 1);

        if (!((parseInt(eccRegionSize) == eccRegionSize) && (eccRegionSize > Math.log2(granule_size))))
        {
            report.logError( `ECC region size should be in the powers of two and greater than 0x${granule_size.toString(16).toUpperCase()} B`,
                instance, "eccEnd0", "eccStart0");
        }
    }

    if ((instance.eccStart1 != 0) || (instance.eccEnd1 != 0))
    {
        eccRegionSize = Math.log2(instance.eccEnd1 - instance.eccStart1 + 1);

        if (!((parseInt(eccRegionSize) == eccRegionSize) && (eccRegionSize > Math.log2(granule_size))))
        {
            report.logError( `ECC region size should be in the powers of two and greater than 0x${granule_size.toString(16).toUpperCase()} B`,
                instance, "eccEnd1", "eccStart1");
        }
    }

    if ((instance.eccStart2 != 0) || (instance.eccEnd2 != 0))
    {
        eccRegionSize = Math.log2(instance.eccEnd2 - instance.eccStart2 + 1);

        if (!((parseInt(eccRegionSize) == eccRegionSize) && (eccRegionSize > Math.log2(granule_size))))
        {
            report.logError( `ECC region size should be in the powers of two and greater than 0x${granule_size.toString(16).toUpperCase()} B`,
                instance, "eccEnd2", "eccStart2");
        }
    }
}


exports = ddr_module;
