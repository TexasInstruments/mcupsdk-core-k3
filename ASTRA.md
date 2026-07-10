# ASTRA Robot File Generation Guide

This guide explains how to enable automated ASTRA CI testing for a new example or test in mcu_plus_sdk. It assumes you have already added the example/test to the SDK (source files, `.syscfg`, `project_<soc>.js`, device registry).

## Supported SoCs

ASTRA robot file generation is supported for:

| SoC | Templates Available |
|-----|---------------------|
| am62x | `tests.robot.xdt`, `tests_sbl.robot.xdt` |
| am62ax | `tests.robot.xdt`, `tests_sbl.robot.xdt` |
| am62px | `tests.robot.xdt`, `tests_sbl.robot.xdt` |
| am62dx | `tests.robot.xdt`, `tests_sbl.robot.xdt` |
| am275x | `tests.robot.xdt`, `tests_sbl.robot.xdt` |

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
| `tests.robot.xdt` | Standard application boot via UART bootloader (bare-metal or RTOS, no SBL flashing) |
| `tests_sbl.robot.xdt` | SBL-based tests: flash an image to OSPI/eMMC/HyperFlash via UartUniFlash (or UartBootloader), reboot, and verify output. Covers both bare-metal SBL and Linux SBL boot flows. |

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

### SBL example — non-Linux boot (`tests_sbl.robot.xdt`):

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
        expectations: [
            { port: "USB2", string: "Starting Sciserver..... PASSED", timeout: 30 },
        ],
    },
};
```

### SBL example — Linux boot (`tests_sbl.robot.xdt`):

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "MCU BIST result after SBL Linux boot",
        appName: "bist_check_result_main",
        testCaseIds: "SITSW-2706",
        cfgPath: "examples/drivers/safety/mcu_bist_result/{board}/{coreName}/mcu_bist_result_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 700,
        expectations: [
            { port: "USB2", string: "Starting Sciserver..... PASSED", timeout: 30 },
            { port: "USB3", string: "All tests have passed", timeout: 30 },
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

## Multiple Test Cases in single application

A single application binary can be linked to multiple JIRA test cases. This is common when:
- One application validates several independent features, each tracked as a separate JIRA ticket.
- Different platforms (HS-FS vs HS-SE) use the same binary but need separate test case IDs.

### JIRA setup

Every test case ID listed in `testCaseIds` **must** have `skip_execution: true` in its **Test Script** field. This tells the test farm to execute the application only once and attribute the result to all listed IDs.

```json
{
    "skip_execution": true
}
```

If any ID is missing `skip_execution: true`, the farm will attempt a separate execution for that ID, causing duplicate or conflicting runs.

### When to consolidate into one robot file

If the application binary and the test execution sequence are identical for all test cases, add all JIRA IDs to the **same** `testCaseIds` field in one robot template. Do not create separate robot templates for the same app/sequence combination — this causes redundant executions on the test farm.

### When sequences differ — use separate robot files with different `appName`

If the same application binary is used but the test sequences differ (different expected output, different commands sent, different ports checked), create a **separate robot template for each sequence** and give each a **unique `appName`**.

ASTRA uses `app_name` as a deduplication key. If two robot files share the same `app_name`, ASTRA will execute only one and skip the other.

Use a parenthetical qualifier to distinguish variants while keeping the base name recognisable:
```
<app_name>(<qualifier>)
```
For example: `sbl_linux_multistage(qnx)`, `sbl_linux_multistage(freertos)`.

```javascript
// Sequence 1 — Linux boot
const robot_template_linux = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_linux.robot",
    options: {
        componentName: "SBL",
        testCaseName: "SBL Linux Multistage",
        appName: "sbl_linux_multistage",         // base app name
        testCaseIds: "SITSW-2001",
        timeout: 660,
    },
};

// Sequence 2 — QNX boot (different sequence, same binary)
const robot_template_qnx = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_qnx.robot",
    options: {
        componentName: "SBL",
        testCaseName: "SBL Linux Multistage QNX",
        appName: "sbl_linux_multistage(qnx)",    // qualifier in parentheses — ASTRA runs this separately
        testCaseIds: "SITSW-2002",
        timeout: 660,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    // ...
    if (buildOption.cpu === "r5fss0-0") {
        build_property.templates = [
            ...(build_property.templates || []),
            robot_template_echo,
            robot_template_dma,
        ];
    }
    return build_property;
}
```

Each template generates its own robot file. ASTRA treats them as independent tests because their `app_name` tags differ.

### JavaScript configuration

List all IDs space-separated in `testCaseIds`:
- **Max 10 IDs per line.** Use JavaScript `+` string concatenation to split longer lists. The continuation string must start with a space to preserve the separator.
- **IDs must be in ascending numerical order.**

```javascript
const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "UART",
        testCaseName: "UART Echo Test",
        appName: "uart_echo",
        testCaseIds: "SITSW-2001 SITSW-2002 SITSW-2003 SITSW-2004 SITSW-2005 SITSW-2006 SITSW-2007 SITSW-2008 SITSW-2009 SITSW-2010" +
                     " SITSW-2011 SITSW-2012",
        timeout: 300,
    },
};
```

### Generated robot file

All IDs appear on the `[Tags]` line:

```
[Tags]    core:r5fss0-0_freertos    component:UART    app_name:uart_echo    SITSW-2001    SITSW-2002    ...
```

ASTRA reports a separate result for each ID. Because all IDs share the same robot test execution, they pass or fail together.

---

## Step 4: Template Options Reference

### Common options (all templates)

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `componentName` | string | `"SBL"` | ASTRA component tag (e.g., `"IPC"`, `"UART"`, `"DPL"`) |
| `testCaseName` | string | `componentName + " application"` | Human-readable test case name. **No consecutive spaces allowed.** |
| `appName` | string | `property.name` | ASTRA `app_name` tag. Must match JIRA Test Application Name exactly. |
| `testCaseIds` | string | `"SITSW-XXXXX"` | Space-separated JIRA test case IDs. See formatting rules below. |
| `timeout` | number | varies | Total test timeout in seconds |
| `expectTimeout` | number | varies | Per-string wait timeout in seconds (can be overridden per element in `expectations`) |

### `tests.robot.xdt` additional options

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `withCfg` | boolean | `false` | Use `WITH CFG` boot (requires `cfgPath`) instead of `WITH ARGS` |
| `cfgPath` | string | — | Path to `.cfg` file relative to SDK root. Required when `withCfg: true`. Supports `{board}` and `${DEVICE_TYPE}` placeholders. |
| `logPort` | string | auto | Override the computed log port (normally derived from CPU type, see Port Mapping) |
| `expectedString` | string | `"All tests have passed"` | Expected string on `logPort` — used when `expectations` is not set |
| `expectPort` | string | auto | Override the port for `expectedString` |
| `expectations` | array | `null` | Sequential multi-port checks. When set, overrides `expectedString`/`expectPort`. See below. |
| `interactPrompt` | string | `null` | Wait for this string on `logPort`, then send `interactSend` commands |
| `interactSend` | array | `[]` | Commands to send when `interactPrompt` is matched |
| `secondPort` | string | `null` | A second UART port to monitor alongside `logPort` |

### `tests_sbl.robot.xdt` additional options

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `cfgPath` | string | **required** | Path to flash config file, SDK-relative. Supports `{board}`, `{coreName}`, `${DEVICE_TYPE}`. |
| `bootMode` | string | varies by SoC | Boot mode after flashing (e.g., `"OSPI_NAND_BOOT_MODE"`, `"OSPI_NOR_BOOT_MODE"`, `"EMMC_BOOT_MODE"`, `"XSPI_1S_BOOT_MODE"`). Pass `null` to skip reboot. |
| `useBootloader` | boolean | `false` | Use `UartBootloader` instead of `UartUniFlash` for flashing |
| `useNFS` | boolean | `false` | Call NFS setup before boot expectations (Linux boot flows) |
| `expectations` | array | `[]` | Sequential port/string checks after boot. See below. |
| `boardExpectations` | object | — | Per-board `expectations` map: `{ "<board>": [{...}] }`. When set, the entry matching the current build's board is used; falls back to `expectations` if the board has no entry. |
| `stressIterations` | number | `null` | Repeat the boot+check cycle N times (stress test mode) |

> **Note:** `cfgFileName` is no longer supported. Always use `cfgPath` with the full SDK-relative path and `{board}` / `{coreName}` / `${DEVICE_TYPE}` placeholders as needed.

---

### `expectations` array

`expectations` defines an ordered list of UART checks to perform after the application boots. Each element specifies a port and either a string to wait for or a command to send and verify.

**Element fields:**

| Field | Required | Description |
|-------|----------|-------------|
| `port` | yes | UART port variable name: `"USB0"`, `"USB2"`, `"USB3"`, `"ACM0"` |
| `string` | yes | String to expect on the port (or the expected response after `send`) |
| `send` | no | If set, sends this command on `port` and verifies `string` is returned |
| `timeout` | no | Per-element wait timeout in seconds. Overrides global `expectTimeout` (supported on am62x/ax/dx/px `tests_sbl`). |

The robot connects to each distinct port in the list before rebooting, then checks them in order after boot.

**Example — expect on two ports after Linux SBL boot:**

```javascript
expectations: [
    { port: "USB2", string: "Starting Sciserver..... PASSED", timeout: 30 },
    { port: "USB3", string: "All tests have passed", timeout: 30 },
],
```

**Example — send a command and verify the response:**

```javascript
expectations: [
    { port: "USB0", string: "login:" },
    { port: "USB0", send: "root", string: "#" },
    { port: "USB0", send: "cat /proc/version", string: "Linux" },
],
```

**Example — per-board expectations using `boardExpectations`:**

Use when different boards have different port assignments or expected strings for the same test.

```javascript
boardExpectations: {
    "am62x-sk":     [{ port: "USB2", string: "All tests have passed" }],
    "am62x-sip-sk": [{ port: "USB2", string: "All tests have passed" }],
    "am62x-sk-lp":  [{ port: "USB2", string: "All tests have passed" }],
},
```

When `boardExpectations` is set, the template picks the entry matching the current board. If no entry matches, it falls back to the `expectations` array (if set).

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

The template derives `logPort` automatically from the CPU name. Use `logPort: "<port>"` in options only when you need to override the default.

### am62ax

| Port | UART | Cores (auto logPort) |
|------|------|----------------------|
| USB0 | UART0 | a53ss0-0 |
| USB2 | WKUP_UART | r5fss0-0 (DM) |
| USB3 | MCU_UART | mcu-r5fss0-0, c75ss0-0 |

### am62dx

| Port | UART | Cores (auto logPort) |
|------|------|----------------------|
| USB0 | UART4 | — (override only: `logPort: "USB0"`) |
| USB1 | UART0 | a53ss0-0 (SBL + A53 app log) |
| USB2 | WKUP_UART | r5fss0-0 (DM) |
| USB3 | MCU_UART | mcu-r5fss0-0, c75ss0-0 |

> **Note:** USB0 (MAIN_UART4) is not the SBL boot port. USB1 (MAIN_UART0) is both the SBL boot port and default A53 app log. Use `logPort: "USB0"` only when syscfg assigns UART4 to c75ss0-0.

### am62px

| Port | UART | Cores (auto logPort) |
|------|------|----------------------|
| USB0 | UART0 | a53ss0-0 |
| USB2 | WKUP_UART | wkup-r5fss0-0 |
| USB3 | MCU_UART | mcu-r5fss0-0 |

### am62x

| Port | UART | Cores (auto logPort) |
|------|------|----------------------|
| USB0 | UART0 | a53ss0-0 |
| USB2 | WKUP_UART | r5fss0-0 |
| USB3 | MCU_UART | m4fss0-0 |

### am275x

| Port | UART | Cores (auto logPort) |
|------|------|----------------------|
| ACM0 | UART0 | r5fss0-0, r5fss0-1, r5fss1-0 (all R5F cores) |
| USB2 | WKUP_UART | wkup-r5fss0-0 |
| USB0 | UART2 | c75ss0-0 |

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
