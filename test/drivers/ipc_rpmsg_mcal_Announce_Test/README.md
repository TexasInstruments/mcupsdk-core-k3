# ipc_rpmsg_mcal_2: Runtime DeInit/Init Empirical Test

## Overview

This folder contains an experimental test to determine whether `RPMessage_deInit()` followed by `RPMessage_init()` with different `vringNumBuf` values can work in a multicore IPC environment.

**Question Being Tested:** Can we avoid multiple syscfg files by changing buffer configuration at runtime?

**Theoretical Answer:** No—memory layout changes would cause corruption.

**Experimental Approach:** Let's actually test it and see what happens.

## Quick Navigation

- **Start Here:** [`QUICK_START.md`](QUICK_START.md) — One-liner build commands
- **Full Build Guide:** [`BUILD_INSTRUCTIONS.md`](BUILD_INSTRUCTIONS.md)
- **Detailed Test Plan:** [`PHASE1_TEST_PLAN.md`](PHASE1_TEST_PLAN.md)
- **Execution Checklist:** [`CHECKLIST.md`](CHECKLIST.md)
- **Test Code:** [`test_ipc_rpmsg.c`](test_ipc_rpmsg.c)

## Test Structure

### Phase 1: Baseline (vringNumBuf=8)
✅ **Status:** Setup complete, ready to build

- All cores boot with cfg3 syscfg (4-core, vringNumBuf=8)
- Main core initiates 10-iteration message exchange
- Remote cores respond with echoes
- Goal: Establish working baseline before runtime transition

### Phase 2: Runtime Transition (vringNumBuf=8 → 4)
📅 **Status:** Planned, after Phase 1 passes

- After Phase 1 completes, call `RPMessage_deInit()`
- Reinitialize with vringNumBuf=4
- Run second 10-iteration test
- Observe if VRING memory corruption occurs

## Folder Layout

```
ipc_rpmsg_mcal_2/
├── test_ipc_rpmsg.c                    # Single test for all cores
├── README.md                           # This file
├── QUICK_START.md                      # Fast build guide
├── BUILD_INSTRUCTIONS.md               # Detailed build steps
├── PHASE1_TEST_PLAN.md                # Phase 1 objectives & flow
├── CHECKLIST.md                        # Build/test checklist
└── am275x-evm/
    ├── r5fss0-0_freertos/
    │   ├── example.syscfg              # cfg3: 4-core, vringNumBuf=8
    │   └── ti-arm-clang/makefile
    ├── r5fss0-1_freertos/
    ├── r5fss1-0_freertos/
    ├── r5fss1-1_freertos/
    └── c75ss0-0_freertos/
```

## Key Differences from ipc_rpmsg_mcal

| Aspect | ipc_rpmsg_mcal | ipc_rpmsg_mcal_2 |
|--------|---|---|
| Purpose | Production MCAL integration | Experimental runtime config test |
| Multiple Configs | Yes (cfg3, cfg4, cfg5, cfg8) | No (Phase 1 only: cfg3) |
| Test Philosophy | Different syscfg per config | Single test, config at runtime |
| DeInit/Init | Not used | **Phase 2 will test this** |
| Target | Validate current approach works | **Validate if runtime config works** |

## Build (Phase 1)

```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2

# Generate syscfg for all cores (one-liner)
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do \
  make -C am275x-evm/${core}_freertos/ti-arm-clang syscfg PROFILE=debug; done && \
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug

# Build all cores
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do \
  make -C am275x-evm/${core}_freertos/ti-arm-clang PROFILE=debug; done && \
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug
```

## Success Indicators

### Phase 1 Success
- ✅ All 4 remote cores boot
- ✅ 10 message exchanges complete
- ✅ No timeout/buffer errors
- ✅ "Completed successfully" message appears

### Phase 2 Expected Outcomes

**If it works (unlikely):**
- DeInit/init with different vringNumBuf succeeds
- Messages still exchange correctly
- No hidden corruption

**If it fails (likely):**
- Descriptor table misalignment
- Message loss or corruption
- Random failures during Phase 2 test
- Clear evidence why runtime reconfig doesn't work

## What We'll Learn

This test will provide empirical evidence for one of:

1. **Runtime reconfiguration works** → Could simplify future designs
2. **Runtime reconfiguration causes corruption** → Validates theory, confirms multiple syscfg is correct approach
3. **Runtime reconfiguration partially works** → Reveals specific limitations (could lead to workarounds)

All three outcomes are valuable—they answer the question definitively.

## Relationship to Main Branch

- **Main branch** (`ipc_rpmsg_mcal`): Uses multiple syscfg files (cfg3, cfg4, cfg5, cfg8)
- **This experiment** (`ipc_rpmsg_mcal_2`): Tests runtime reconfiguration
- **Outcome**: Will either validate or refute the main branch's approach

## Files to Reference

- **MCAL Endpoint Config:** See `test_ipc_rpmsg.c:getServerEndPtForCore()`
- **SysConfig Generation:** `am275x-evm/[core]_freertos/ti-[compiler]/makefile` lines 223-228
- **Test Logic:** `test_ipc_rpmsg.c:test_rpmsgAnyToAny()` (lines 208-269)

## Known Issues (Phase 1)

- None (setup phase just completed)

## Troubleshooting

See [`CHECKLIST.md`](CHECKLIST.md) for detailed troubleshooting guide.

---

**Next Step:** Follow [`QUICK_START.md`](QUICK_START.md) to build Phase 1.
