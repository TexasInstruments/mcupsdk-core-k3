# ✅ Setup Complete - Phase 1 Ready to Build & Test

## What Has Been Created

**Folder:** `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/`

**Purpose:** Empirical test to determine if `RPMessage_deInit()` + `RPMessage_init()` with different `vringNumBuf` can work at runtime.

## Complete Contents

```
ipc_rpmsg_mcal_2/
├── Documentation
│   ├── README.md                    (Overview & navigation)
│   ├── QUICK_START.md               (Fast build commands)
│   ├── BUILD_INSTRUCTIONS.md        (Detailed build guide)
│   ├── PHASE1_TEST_PLAN.md          (Test objectives)
│   ├── CHECKLIST.md                 (Build/test checklist)
│   └── SETUP_COMPLETE.md            (This file)
│
├── Test Code
│   └── test_ipc_rpmsg.c             (Single file for all cores)
│
└── am275x-evm/
    ├── Boot Config
    │   └── ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg  (✅ Updated to point to ipc_rpmsg_mcal_2)
    │
    ├── 4 R5 Cores (ARM Cortex-R5)
    │   ├── r5fss0-0_freertos/
    │   ├── r5fss0-1_freertos/
    │   ├── r5fss1-0_freertos/
    │   └── r5fss1-1_freertos/
    │       Each contains:
    │       - example.syscfg (cfg3: 4-core, vringNumBuf=8)
    │       - main.c
    │       - ti-arm-clang/ (build dir)
    │
    ├── 2 C75 DSP Cores
    │   ├── c75ss0-0_freertos/
    │   └── c75ss1-0_freertos/
    │       Each contains:
    │       - example.syscfg (cfg3)
    │       - main.c
    │       - ti-c7000/ (build dir)
    │
    └── system_freertos/
        └── makefile (multi-core orchestration)
```

## Phase 1: Baseline Test

**Configuration:** cfg3 (4-core, vringNumBuf=8)

**What It Does:**
1. All 6 cores boot with fixed vringNumBuf=8
2. Main core (R5FSS0_0) initiates 10-iteration message exchange
3. Remote cores respond with echoes
4. Establishes working baseline

**Expected Duration:** ~5-10 seconds for message exchanges

## Build Steps (Copy & Paste Ready)

### Step 1: Generate SysConfig Files

```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2

# R5 cores
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang syscfg PROFILE=debug
done

# C75 cores
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 syscfg PROFILE=debug
```

### Step 2: Build All Cores

```bash
# R5 cores
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang PROFILE=debug
done

# C75 cores
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 PROFILE=debug
```

### Step 3: Flash via UART

```bash
# Bootloader config file (already updated to point to ipc_rpmsg_mcal_2):
python3 /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/tools/boot/byteswap.py \
  /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg
```

## Phase 1 Success Criteria

✅ **All 4 remote cores boot** (R5FSS0_1, R5FSS1_0, R5FSS1_1, C75SS0_0)
✅ **C75SS1_0 excluded** (runtime detection works)
✅ **Message exchanges complete** (10 iterations per core)
✅ **No timeout or buffer errors**
✅ **Boot log shows:** `[TEST ROUND 1] Completed successfully with vringNumBuf=8`

## After Phase 1 Passes

If Phase 1 test succeeds:

1. Edit `test_ipc_rpmsg.c` after line 98 (in `test_ipc_main_core_start()`)
2. Add `RPMessage_deInit()` call
3. Reinitialize with `vringNumBuf=4`
4. Add second test round (Phase 2)
5. Rebuild and test
6. Observe if VRING memory corruption occurs

## Bootloader Config File

**Location:**
```
/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg
```

**What It Does:**
- Loads SBL (bootloader)
- Loads MCAL CFG3 binary to R5FSS0_0 (main core)
- Loads test binary to R5FSS0_1, R5FSS1_0, R5FSS1_1, C75SS0_0
- C75SS1_0 is excluded (commented out)

**Already Updated:** ✅ All paths point to `ipc_rpmsg_mcal_2` binaries (not ipc_rpmsg_mcal)

## Known Configuration Details

- **Buffer Count:** vringNumBuf=8 (Phase 1)
- **Message Size:** vringMsgSize=512 bytes
- **Allocation Strategy:** vringAllocationPDK=true
- **Core Count:** 4-core (C75SS1_0 excluded)
- **Memory Region:** 0x723C0000 (15KB VRING memory)
- **Test Iterations:** 10 messages per core

## Files Ready for Testing

| File | Location | Status |
|------|----------|--------|
| SysConfig (R5FSS0_0) | `r5fss0-0_freertos/example.syscfg` | ✅ |
| SysConfig (R5FSS0_1) | `r5fss0-1_freertos/example.syscfg` | ✅ |
| SysConfig (R5FSS1_0) | `r5fss1-0_freertos/example.syscfg` | ✅ |
| SysConfig (R5FSS1_1) | `r5fss1-1_freertos/example.syscfg` | ✅ |
| SysConfig (C75SS0_0) | `c75ss0-0_freertos/example.syscfg` | ✅ |
| SysConfig (C75SS1_0) | `c75ss1-0_freertos/example.syscfg` | ✅ |
| Test Code | `test_ipc_rpmsg.c` | ✅ |
| Boot Config | `am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg` | ✅ |

## Troubleshooting

If build fails, see [CHECKLIST.md](CHECKLIST.md) for detailed troubleshooting.

Common issues:
- **SysConfig not generating:** Run `make syscfg` manually
- **File not found errors:** Check FILE_PATH in makefiles
- **test_ipc_rpmsg.c not found:** Verify parent folder path is in makefile

## Next: Phase 2 (After Phase 1 Passes)

Phase 2 will test the empirical question: **Can we change vringNumBuf at runtime?**

Expected outcome: Runtime reconfiguration will likely cause descriptor corruption or similar issues, confirming that multiple syscfg files (cfg3, cfg4, cfg5, cfg8) is the correct approach.

---

**Status:** ✅ Ready to build and test!
