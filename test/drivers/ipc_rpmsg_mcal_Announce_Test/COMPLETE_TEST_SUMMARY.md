# Complete Test Summary: ipc_rpmsg_mcal_2 Empirical Test

## Project Goal

Determine empirically whether `RPMessage_deInit()` + `RPMessage_init()` with different `vringNumBuf` values can work at runtime, thereby eliminating the need for multiple syscfg files.

## Test Structure

The test is now **complete** with both phases built into a single test_ipc_rpmsg.c file.

### Phase 1: Baseline Test (vringNumBuf=8)

**Status:** ✅ Working (verified)

**What it does:**
- All 6 cores boot with cfg3 SysConfig (4-core, vringNumBuf=8)
- Main core runs 10 message exchange iterations
- Remote cores respond with echoes
- Establishes baseline for comparison

**Expected Log:**
```
[TEST ROUND 1] Running with vringNumBuf=8
[TEST ROUND 1] Completed successfully with vringNumBuf=8
```

**Success Criteria:**
- ✅ All 4 remote cores participate
- ✅ 10 complete message exchanges
- ✅ No timeouts or errors
- ✅ C75SS1_0 correctly excluded

### Phase 2: Runtime Reconfiguration (vringNumBuf: 8 → 4)

**Status:** ✅ Implemented (automatic, embedded in test)

**What it does:**
1. After Phase 1 test completes
2. Calls `test_rpmsgDestructObjects()` to clean up endpoints
3. Calls `RPMessage_deInit()` to shutdown IPC driver
4. Waits 500ms for stabilization
5. Calls `RPMessage_init()` with vringNumBuf=4 (new buffer count)
6. Calls `test_rpmsgCreateObjects()` to recreate endpoints
7. Waits 500ms for cores to be ready
8. Runs second 10-iteration message exchange test

**Expected Outcomes:**

#### Outcome A: Failure (Most Likely)
```
[PHASE 2] Testing runtime reconfiguration...
[PHASE 2] Calling RPMessage_deInit()...
[PHASE 2] RPMessage_deInit() completed
[PHASE 2] Calling RPMessage_init() with vringNumBuf=4...
[PHASE 2] RPMessage_init() succeeded with vringNumBuf=4

[TEST ROUND 2] Running with vringNumBuf=4
[ERROR] Timeout waiting for message from core
[PHASE 2] FAILURE: Could not reconfigure vringNumBuf at runtime
```

**Why this happens:** VRING memory layout changes cause descriptor misalignment:
- Buffer count changes from 8 to 4
- Descriptor offsets change: `offset = numBuf * (msgSize + 32) + 32`
- Same physical VRING memory interpreted with different offsets
- Old descriptor data remains, new init reinterprets it
- Message corruption or loss occurs

#### Outcome B: Success (Unlikely)
```
[TEST ROUND 2] Running with vringNumBuf=4
... message exchanges succeed ...
[TEST ROUND 2] Completed with vringNumBuf=4
[PHASE 2] SUCCESS: Runtime reconfiguration test passed!
[PHASE 2] vringNumBuf successfully changed from 8 to 4 at runtime
```

**Implication:** Runtime reconfiguration works, multiple syscfg files unnecessary.

#### Outcome C: Init Error (Possible)
```
[PHASE 2] RPMessage_init() failed with status=-1
[PHASE 2] ERROR: Could not reconfigure vringNumBuf at runtime
```

**Implication:** Driver explicitly prevents runtime buffer count changes (safest failure).

## Test Duration

- Phase 1 test: ~5-10 seconds
- Transition delays: ~2 seconds (500ms × 2)
- Phase 2 test or failure: ~5-10 seconds
- **Total: ~12-22 seconds**

## How to Run the Complete Test

### Step 1: Build

```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2

# Generate SysConfig
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang syscfg PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 syscfg PROFILE=debug

# Build
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 PROFILE=debug
```

### Step 2: Flash

```bash
python3 /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/tools/boot/byteswap.py \
  /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg
```

### Step 3: Monitor Boot Log

Watch for:
- Phase 1 completion
- Phase 2 start
- Phase 2 result (success or failure)

## Key Technical Points

### Why Multiple SysConfig Files Exist

1. **VRING Memory is Pre-allocated** at boot time with fixed addresses
2. **Buffer Count Affects Layout**: `vringSize = numBuf * (msgSize + 32) + 32`
3. **Descriptor Offsets Change** when numBuf changes
4. **All Cores Must Match** - constraint documented in driver header
5. **Runtime Changes Risk Corruption** - this test validates why

### What This Test Proves

**If Phase 2 Fails:**
- ✅ Confirms multiple syscfg files (cfg3, cfg4, cfg5, cfg8) are necessary
- ✅ Validates architectural design decision
- ✅ Explains why VRING is statically pre-allocated

**If Phase 2 Succeeds:**
- ✅ Proves runtime reconfiguration is possible
- ✅ Could allow simplified build/test infrastructure
- ✅ Opens possibility for dynamic buffer tuning

## File Structure

```
ipc_rpmsg_mcal_2/
├── test_ipc_rpmsg.c ..................... Both Phase 1 & 2 tests
├── README.md ............................ Project overview
├── PHASE1_TEST_PLAN.md .................. Phase 1 details
├── PHASE2_RUNTIME_RECONFIG.md ........... Phase 2 details
├── COMPLETE_TEST_SUMMARY.md ............. This file
├── SETUP_COMPLETE.md .................... Setup verification
├── QUICK_START.md ....................... Fast commands
├── BUILD_INSTRUCTIONS.md ................ Detailed guide
├── CHECKLIST.md ......................... Build checklist
└── am275x-evm/
    ├── ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg
    ├── r5fss0-0_freertos/
    ├── r5fss0-1_freertos/
    ├── r5fss1-0_freertos/
    ├── r5fss1-1_freertos/
    ├── c75ss0-0_freertos/
    ├── c75ss1-0_freertos/
    └── system_freertos/
```

## Expected Behavior Summary

| Phase | Test | Buffer Count | Duration | Status |
|-------|------|--------------|----------|--------|
| 1 | Message exchange | 8 | ~5-10s | ✅ Working |
| 2 Transition | deInit/init | - | ~2s | New |
| 2 | Message exchange | 4 | ~5-10s or FAIL | ❓ Unknown |

## Success Criteria

### Phase 1 PASS
- [ ] All 4 remote cores boot
- [ ] "[TEST ROUND 1] Completed successfully" in log
- [ ] No errors or timeouts

### Phase 2 Expected
- [ ] deInit/init sequence executes
- [ ] Either Phase 2 test runs OR clear error logged
- [ ] No system crash or hang

### Complete Test PASS
- [ ] Phase 1 succeeds AND
- [ ] Phase 2 either succeeds OR fails gracefully with clear error

## What This Reveals

This empirical test will provide definitive evidence about:

1. **VRING Memory Behavior**: Does reinitialization properly handle memory reuse?
2. **Driver Constraints**: What prevents or enables buffer count changes?
3. **Design Rationale**: Why are multiple syscfg files the current solution?
4. **Future Possibilities**: Could this approach be improved?

All outcomes are scientifically valid and informative.

## Next Steps After Results

**If Phase 2 Fails (Expected):**
- Document findings in memory
- Confirm multiple syscfg approach is correct
- Use results to explain architectural decisions

**If Phase 2 Succeeds (Surprising):**
- Investigate why driver allows reconfiguration
- Consider implications for build system
- Explore if this can be leveraged safely

## Notes

- Phase 2 is **automatic** - runs after Phase 1 with no user intervention
- Test is **self-contained** - single binary tests both phases
- Logging is **explicit** - clear SUCCESS/FAILURE indicators in output
- Results are **definitive** - will answer the key architectural question

---

**Ready to test:** Build and flash using instructions above. The complete empirical evaluation will run automatically.
