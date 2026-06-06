# ASTRA Robot File Generation Guide

This guide explains how to enable automated ASTRA CI testing for a new example or test in mcu_plus_sdk. It assumes you have already added the example/test to the SDK (source files, `.syscfg`, `project_<soc>.js`, device registry).

## Supported SoCs

ASTRA robot file generation is supported for:

| SoC | Templates Available |
|-----|---------------------|
| am62x | `tests.robot.xdt`, `tests_sbl.robot.xdt`, `tests_sbl_linux.robot.xdt` |
| am62ax | `tests.robot.xdt`, `tests_sbl.robot.xdt`, `tests_sbl_linux.robot.xdt` |
| am62px | `tests.robot.xdt`, `tests_sbl.robot.xdt`, `tests_sbl_linux.robot.xdt` |
| am62dx | `tests.robot.xdt`, `tests_sbl.robot.xdt` |
| am275x | `tests.robot.xdt`, `tests_sbl.robot.xdt`, `tests_uniflash.robot.xdt` |

> **Note:** am62lx and j722s do not have ASTRA support. Do not add robot templates for these SoCs.

---

## Step 1: Create the JIRA Test Case

Before adding a robot template, a JIRA test case must exist in the SITSW project.

- Issue Type: **Test Case**
- Set **Execution Type** to `Automated`.
- Select the correct **Platform(s)** for the boards this test runs on (e.g., `am62a-sk`, `am62px-sk`, `am62dx-evm`, `am275x-evm`).
- Fill in the **Test Script** field with at minimum:

```json
{
    "skip_execution": true
}
```

`skip_execution: true` ensures the test farm runs the application only once even when multiple JIRA test cases share the same application.

If the test requires a board with a specific hardware setup (e.g., SD card, flash connected), add `hw_assets`:

```json
{
    "skip_execution": true,
    "hw_assets": "sdflash"
}
```

> **Note:** The **Test Application Name** and **Test Setup** fields are used by the legacy STP framework and are not consumed by ASTRA. They are not required for ASTRA based test farm.

---

## Step 2: Choose the Right Template

Select the template based on what the test does:

| Template | When to Use |
|----------|-------------|
| `tests.robot.xdt` | Standard application boot (bare-metal or RTOS, no SBL flashing) |
| `tests_sbl.robot.xdt` | Bootloader/SBL tests that flash an image to OSPI/eMMC and reboot |
| `tests_sbl_linux.robot.xdt` | SBL tests that boot a full Linux stack (requires Linux login sequence) |
| `tests_uniflash.robot.xdt` | am275x UartUniFlash-based boot (HyperFlash/OSPI XIP) |

Template files are located at:
```
.project/templates/<soc>/astra/<template_name>.robot.xdt
```

---

## Step 3: Add `robot_template` to `project_<soc>.js`

Open the `project_<soc>.js` file for your example/test (e.g., `project_am62ax.js`) and add a `robot_template` constant before `getComponentBuildProperty()`. Then append it to `build_property.templates` inside `getComponentBuildProperty()`.

### Basic example without CFG (`tests.robot.xdt`):

Uses the `WITH ARGS` boot flow — the template derives the binary path automatically from the project.

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL Demo application",
        appName: "dpl_demo",
        testCaseIds: "SITSW-1249",
        timeout: 300,
    },
};
```

### Basic example with CFG (`tests.robot.xdt`):

Use `withCfg: true` when the test requires a multi-core boot config file (e.g., IPC tests that need all cores loaded).

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "IPC Notify Echo application",
        appName: "ipc_notify_echo",
        testCaseIds: "SITSW-1940",
        withCfg: true,
        cfgPath: "examples/drivers/ipc/ipc_notify_echo/{board}/ipc_notify_echo_sbl_uart_${DEVICE_TYPE}.cfg",
        timeout: 1200,
    },
};
```

### SBL example (`tests_sbl.robot.xdt`):

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND",
        appName: "sbl_ospi_nand_multistage",
        testCaseIds: "SITSW-1757",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 660,
        expectTimeout: 200,
        expectations: [
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};
```

### Appending to `build_property.templates`:

```javascript
function getComponentBuildProperty(buildOption) {
    let build_property = {};
    // ... existing setup ...

    // Only attach robot template to the master/driver core
    if (buildOption.cpu === "r5fss0-0") {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    return build_property;
}
```

> **Tip:** Only add the robot template to one core per test (the master or driver core). Attaching to all cores creates duplicate test entries in ASTRA.

---

## Step 4: Template Options Reference

### Common options (all templates)

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `componentName` | string | `"SBL"` | ASTRA component tag (e.g., `"IPC"`, `"UART"`, `"DPL"`) |
| `testCaseName` | string | `componentName + " application"` | Human-readable test case name. **No consecutive spaces allowed.** |
| `appName` | string | `property.name` | ASTRA `app_name` tag. Must match JIRA Test Application Name exactly. |
| `testCaseIds` | string | `"SITSW-XXXXX"` | Space-separated JIRA test case IDs. See formatting rules below. |
| `timeout` | number | `700` | Total test timeout in seconds |
| `expectTimeout` | number | `100` | Per-string wait timeout in seconds |
| `expectedString` | string | `"All tests have passed"` | Expected UART output string (single-string mode) |
| `expectPort` | string | varies by core | UART port for expected string (e.g., `"USB2"`, `"USB3"`) |
| `expectations` | array | `null` | Sequential multi-port checks: `[{ port, string, send? }]` |

### `tests.robot.xdt` additional options

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `withCfg` | boolean | `false` | Use `WITH CFG` boot (requires `cfgPath`) instead of `WITH ARGS` |
| `cfgPath` | string | — | Path to `.cfg` file relative to SDK root. Use `{board}` and `${DEVICE_TYPE}` as placeholders. |
| `logPort` | string | auto | Override computed log port |

### `tests_sbl.robot.xdt` / `tests_sbl_linux.robot.xdt` additional options

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `cfgPath` | string | — | Path to flash config file relative to SDK root |
| `bootMode` | string | varies | Boot mode after flashing (e.g., `"OSPI_NAND_BOOT_MODE"`, `"OSPI_NOR_BOOT_MODE"`, `"EMMC_BOOT_MODE"`) |
| `useBootloader` | boolean | `false` | Use `UartBootloader` instead of `UartUniFlash` |
| `useNFS` | boolean | `false` | Enable NFS setup before Linux boot (`tests_sbl_linux` only) |

### Path Placeholders in `cfgPath`

The `cfgPath` string supports the following placeholders, which are substituted at build time (during `gen-buildfiles`) or at runtime:

| Placeholder | Resolved At | Value | Example |
|-------------|-------------|-------|---------|
| `{board}` | Build time | Board name from `buildOptionCombos` (e.g., `am62ax-sk`, `am62px-sk`) | `{board}` → `am62ax-sk` |
| `{coreName}` | Build time | CPU + OS string from the build combo (e.g., `r5fss0-0_freertos`) | `{coreName}` → `r5fss0-0_freertos` |
| `${DEVICE_TYPE}` | Runtime | `hs` on HS-SE platform, `hs_fs` on HS-FS platform | `${DEVICE_TYPE}` → `hs_fs` |

**`{board}`** and **`{coreName}`** are substituted by the JavaScript template engine when the robot file is generated. Each `buildOptionCombos` entry produces its own robot file with its own resolved values.

**`${DEVICE_TYPE}`** is a Robot Framework variable resolved at test runtime based on the `${PLATFORM}` environment variable set by the ASTRA test farm:
- `hs` — HS-SE (`hsse`) platform
- `hs_fs` — HS-FS (`hsfs`) platform

Ensure both `_hs.cfg` and `_hs_fs.cfg` files exist if the test runs on both platforms. If only one platform is supported, hardcode the suffix (e.g., `..._hs.cfg`).

**Example using all three placeholders:**
```javascript
cfgPath: "test/drivers/ipc/{board}/{coreName}/ipc_test_sbl_uart_${DEVICE_TYPE}.cfg"
// Resolves to (build time): test/drivers/ipc/am62ax-sk/r5fss0-0_freertos/ipc_test_sbl_uart_${DEVICE_TYPE}.cfg
// Resolves to (runtime):    test/drivers/ipc/am62ax-sk/r5fss0-0_freertos/ipc_test_sbl_uart_hs_fs.cfg
```

---

## Step 5: Port Mapping Reference

### am62ax / am62dx

| Port | Physical UART | Core |
|------|--------------|------|
| USB0 | UART0 / ttyUSB0 | A53 (bootloader log) |
| USB2 | WKUP_UART / ttyUSB2 | r5fss0-0 (DM core) |
| USB3 | MCU_UART / ttyUSB3 | mcu-r5fss0-0 |

### am62px

| Port | Physical UART | Core |
|------|--------------|------|
| USB0 | UART0 / ttyUSB0 | A53 / bootloader |
| USB2 | WKUP_UART / ttyUSB2 | wkup-r5fss0-0 |
| USB3 | MCU_UART / ttyUSB3 | mcu-r5fss0-0 |

### am62x

| Port | Physical UART | Core |
|------|--------------|------|
| USB0 | UART0 / ttyUSB0 | A53 / bootloader |
| USB2 | WKUP_UART / ttyUSB2 | r5fss0-0 |
| USB3 | MCU_UART / ttyUSB3 | m4fss0-0 |

### am275x

| Port | Physical UART | Core |
|------|--------------|------|
| ACM0 | UART0 / ttyACM0 | Main R5F / bootloader |
| USB2 | WKUP_UART / ttyUSB2 | wkup-r5fss0-0 |
| USB0 | UART2 / ttyUSB0 | c75ss0-0 |

---

## Step 6: `testCaseIds` Formatting Rules

1. **Max 10 JIRA IDs per line.** Use JavaScript `+` string concatenation to split longer lists. The continuation line must start with a space to preserve the separator between IDs.

2. **IDs must be in ascending numerical order.**

```javascript
// Correct — 10 per line, sorted, leading space on continuation
testCaseIds: "SITSW-1001 SITSW-1002 SITSW-1003 SITSW-1004 SITSW-1005 SITSW-1006 SITSW-1007 SITSW-1008 SITSW-1009 SITSW-1010" +
             " SITSW-1011 SITSW-1012 SITSW-1013 SITSW-1014 SITSW-1015 SITSW-1016 SITSW-1017 SITSW-1018 SITSW-1019 SITSW-1020",
```

---

## Step 7: `testCaseName` Rules

- **No consecutive spaces** — Robot Framework treats two or more spaces as a column separator, which will break the test case name.

```javascript
// Wrong
testCaseName: "UART  Echo Test",   // double space — broken

// Correct
testCaseName: "UART Echo Test",
```

---

## Step 8: Regenerate Build Files

After modifying `project_<soc>.js`, regenerate the makefiles and robot files:

```bash
cd mcu_plus_sdk
make gen-buildfiles DEVICE=<soc>
# e.g.: make gen-buildfiles DEVICE=am62ax
```

---

## Step 9: Verify the Generated Robot File

The robot file is generated at:
```
<example_or_test>/<board>/<core_os>/tests.robot
```

Verify the `[Tags]` line contains the correct values:
```
[Tags]    core:<core_os>    component:<componentName>    app_name:<appName>    <testCaseIds>
```

Example:
```
[Tags]    core:r5fss0-0_freertos    component:IPC    app_name:ipc_notify_echo    SITSW-1940
```

---

## Step 10: Verify JIRA `testCaseIds`

Confirm the JIRA IDs listed in `testCaseIds` exist and are of type **Test Case** in the SITSW project. Each ID must have `skip_execution: true` in its **Test Script** field (see Step 1).

ASTRA matches tests by the `SITSW-XXXXX` tags in the robot file's `[Tags]` line. If a JIRA ID is missing from the report or shows as SKIP, verify:

1. The ID is present in `testCaseIds` in the robot template.
2. The `appName` tag in the generated robot file matches what ASTRA expects.
3. The JIRA test case has `skip_execution: true` in **Test Script**.

---

## Complete Example

### Without CFG — single-core test (e.g., `dpl_demo`)

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL Demo application",
        appName: "dpl_demo",
        testCaseIds: "SITSW-1249",
        timeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    // ... existing build property setup ...

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}
```

After running `make gen-buildfiles DEVICE=am62ax`:
```
examples/kernel/dpl/dpl_demo/am62ax-sk/r5fss0-0_freertos/tests.robot
```

---

### With CFG — multi-core test (e.g., `ipc_notify_echo`)

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "IPC Notify Echo application",
        appName: "ipc_notify_echo",
        testCaseIds: "SITSW-1940",
        withCfg: true,
        cfgPath: "examples/drivers/ipc/ipc_notify_echo/{board}/ipc_notify_echo_sbl_uart_${DEVICE_TYPE}.cfg",
        timeout: 1200,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    // ... existing build property setup ...

    // Only the master core (r5fss0-0) generates the robot file;
    // other cores are loaded by the cfg and do not need their own robot file.
    if (buildOption.cpu === "r5fss0-0") {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    return build_property;
}
```

After running `make gen-buildfiles DEVICE=am62ax`:
```
examples/drivers/ipc/ipc_notify_echo/am62ax-sk/r5fss0-0_freertos/tests.robot
```
