	let path = require('path');

	let device = "j722s";

	const files = {
	    common: [
		"test_sciclient.c",
		"test_sciclient_coverage.c",
		"uart_print.c",
		"test_sciclient_ti_msg.c",
		"test_sciclient_val.c",
		"test_sciclient_rm_irq.c",
		"main.c",
	    ],
	};

	/* Relative to where the makefile will be generated
	 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
	 */
	const filedirs = {
	    common: [
		"..",       /* core_os_combo base */
		"../..",    /* Board base */
		"../../..", /* Example base */
	    ],
	};

	const libdirs_mcu_nortos = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/test/unity/lib",
	    ],
	};

	const libdirs_main_nortos = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/test/unity/lib",
	    ],
	};

	const libdirs_freertos_c75ss0 = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
		"${MCU_PLUS_SDK_PATH}/test/unity/lib",
	    ],
	}

	const libdirs_freertos_c75ss1 = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
		"${MCU_PLUS_SDK_PATH}/test/unity/lib",
	    ],
	}

	const includes_nortos = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/sciclient/sciclient_dynamic_analysis/j722s-evm/"
	    ],
	};
	
	const includes_freertos_c75ss0 = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/c75x",
		"${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/sciclient/sciclient_dynamic_analysis/j722s-evm/"
	    ],
	};

	const includes_freertos_c75ss1 = {
	    common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/c75x",
		"${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/sciclient/sciclient_dynamic_analysis/j722s-evm/"
	    ],
	};

	const libs_nortos_mcu_r5f = {
	    common: [
		"nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
		"unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
	    ],
	};

	const libs_nortos_main_r5f = {
	    common: [
		"nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
		"unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
	    ],
	};


	const libs_freertos_c75ss0 = {
	    common: [
		"freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
		"drivers.j722s.c75ss0-0.ti-c7000.${ConfigName}.lib",
		"unity.j722s.c75x.ti-c7000.${ConfigName}.lib",
	    ],
	};

	const libs_freertos_c75ss1 = {
	    common: [
		"freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
		"drivers.j722s.c75ss1-0.ti-c7000.${ConfigName}.lib",
		"unity.j722s.c75x.ti-c7000.${ConfigName}.lib",
	    ],
	};

	const lnkfiles = {
	    common: [
		"linker.cmd",
	    ]
	};

	const syscfgfile = "../example.syscfg";

	const templates_nortos_mcu_r5f =
	[
	    {
		input: ".project/templates/j722s/common/linker_mcu-r5f_nortos.cmd.xdt",
		output: "linker.cmd",
	    },
	    {
		input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
		    entryFunction: "test_main",
		},
	    }
	];

	const templates_nortos_main_r5f =
	[
	    {
		input: ".project/templates/j722s/common/linker_main-r5f_nortos.cmd.xdt",
		output: "linker.cmd",
	    },
	    {
		input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
		    entryFunction: "test_main",
		},
	    }
	];

	
	const templates_freertos_c75ss0 =
	[
	    {
		input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
		output: "linker.cmd",
	    },
	    {
		input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		    entryFunction: "test_main",
		    stackSize: 64*1024,
		},
	    }
	];

	const templates_freertos_c75ss1 =
	[
	    {
		input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
		output: "linker.cmd",
	    },
	    {
		input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		    entryFunction: "test_main",
		    stackSize: 64*1024,
		},
	    }
	];

	const buildOptionCombos = [
	    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
	    { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
	    { device: device, cpu: "c75ss0-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos"},
	    { device: device, cpu: "c75ss1-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos"},
	];

	function getComponentProperty() {
	    let property = {};

	    property.dirPath = path.resolve(__dirname, "..");
	    property.type = "executable";
	    property.name = "test_sciclient_dynamic_analysis";
	    property.isInternal = true;
	    property.skipProjectSpec = true;
	    property.buildOptionCombos = buildOptionCombos;

	    return property;
	}

	function getComponentBuildProperty(buildOption) {
	    let build_property = {};

	    build_property.files = files;
	    build_property.filedirs = filedirs;
	    build_property.lnkfiles = lnkfiles;
	    build_property.syscfgfile = syscfgfile;

	    if(buildOption.cpu.match(/mcu-r5f*/)) {
		build_property.includes = includes_nortos;
		build_property.libdirs = libdirs_mcu_nortos;
		build_property.libs = libs_nortos_mcu_r5f;
		build_property.templates = templates_nortos_mcu_r5f;
	    }
	    else if(buildOption.cpu.match(/main-r5f*/)) {
		build_property.includes = includes_nortos;
		build_property.libdirs = libdirs_main_nortos;
		build_property.libs = libs_nortos_main_r5f;
		build_property.templates = templates_nortos_main_r5f;
	    }
	    else if(buildOption.cpu.match(/c75ss0-0*/)) {
		build_property.includes = includes_freertos_c75ss0;
		build_property.libdirs = libdirs_freertos_c75ss0;
		build_property.libs = libs_freertos_c75ss0;
		build_property.templates = templates_freertos_c75ss0;
	    }
	    else if(buildOption.cpu.match(/c75ss1-0*/)) {
		build_property.includes = includes_freertos_c75ss1;
		build_property.libdirs = libdirs_freertos_c75ss1;
		build_property.libs = libs_freertos_c75ss1;
		build_property.templates = templates_freertos_c75ss1;
	    }
	       
	    return build_property;
	}

	module.exports = {
	    getComponentProperty,
	    getComponentBuildProperty,
	};
