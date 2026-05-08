# Phase 2: Runtime Reconfiguration Test (vringNumBuf: 8 → 4)

## Overview

Phase 2 has been added directly to `test_ipc_rpmsg.c`. After Phase 1 test completes with vringNumBuf=8, the test will automatically:

1. Destruct all RPMessage endpoints
2. Call `RPMessage_deInit()` to shut down the IPC driver
3. Call `RPMessage_init()` with vringNumBuf=4
4. Recreate all RPMessage endpoints
5. Run a second message exchange test with 4 buffers instead of 8

## What Gets Tested

**Question:** Can we change vringNumBuf from 8 to 4 at runtime?

**Hypothesis:** This will likely fail due to:
- VRING memory layout changes (descriptors, avail queue, used queue offsets change)
- Old descriptor data remaining in memory but reinterpreted with new layout
- Potential multi-core synchronization issues during transition

## Test Flow

```
Phase 1: vringNumBuf=8 (10 iterations)
    ↓
[PHASE 2] Testing runtime reconfiguration...
    ↓
Destruct endpoints
    ↓
RPMessage_deInit()
    ↓
Wait 500ms
    ↓
RPMessage_init(vringNumBuf=4)
    ↓
Create new endpoints
    ↓
Wait 500ms
    ↓
Phase 2: vringNumBuf=4 (10 iterations)
    ↓
Result: SUCCESS or FAILURE logged
```

## Expected Outcomes

### Most Likely: FAILURE

**Symptom:** Timeout, buffer corruption, or invalid parameters error during Phase 2 test

**Why:** VRING memory layout changes cause descriptor misalignment:
- Old VRING memory has data at offsets calculated for 8 buffers
- New init reinterprets same memory with offsets for 4 buffers
- Message descriptors point to wrong memory locations
- Message loss or corruption occurs

**Log Evidence:**
```
[TEST ROUND 2] Running with vringNumBuf=4
[ERROR] Timeout waiting for message response
-OR-
[ERROR] Invalid message header
-OR-
[ERROR] Endpoint communication failed
```

### Unlikely: SUCCESS

**If it works:** Validates that:
- VRING memory is properly cleared
- Descriptor tables are correctly reinitialized
- No stale data interferes with messaging
- Runtime reconfiguration is viable

**Log Evidence:**
```
[TEST ROUND 2] Completed with vringNumBuf=4
[PHASE 2] SUCCESS: Runtime reconfiguration test passed!
```

### Partial: INIT FAILS

**If RPMessage_init() returns error:** Validates that:
- Driver explicitly rejects vringNumBuf changes
- Error handling prevents undefined behavior
- This is the safest failure mode

**Log Evidence:**
```
[PHASE 2] RPMessage_init() failed with status=-1
[PHASE 2] ERROR: Could not reconfigure vringNumBuf at runtime
```

## How to Run Phase 2

Phase 2 is **automatic** when you build and flash the updated test file.

### Build

```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2

# SysConfig (same as Phase 1)
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang syscfg PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 syscfg PROFILE=debug

# Build (automatically gets Phase 2 logic)
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug
make -C am275x-evm/c75ss1-0_freertos/ti-c7000 PROFILE=debug
```

### Flash

Same bootloader config as Phase 1:
```bash
python3 /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/tools/boot/byteswap.py \
  /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg
```

### Expected Total Test Duration

- Phase 1 (vringNumBuf=8): ~5-10 seconds
- Transition delays: ~2 seconds
- Phase 2 (vringNumBuf=4 or FAILURE): ~5-10 seconds or instant error
- **Total:** ~12-22 seconds

## Log Output Examples

### Example 1: Runtime Reconfiguration Succeeds

```
[TEST ROUND 1] Running with vringNumBuf=8
... message exchanges ...
[TEST ROUND 1] Completed successfully with vringNumBuf=8

[PHASE 2] Testing runtime reconfiguration...
[PHASE 2] Calling RPMessage_deInit()...
[PHASE 2] Waiting 500ms for all cores to stabilize...
[PHASE 2] RPMessage_deInit() completed
[PHASE 2] Waiting 500ms before re-initialization...
[PHASE 2] Calling RPMessage_init() with vringNumBuf=4...
[PHASE 2] RPMessage_init() succeeded with vringNumBuf=4
[PHASE 2] Creating new RPMessage objects...
[PHASE 2] Waiting 500ms for all cores to be ready...

[TEST ROUND 2] Running with vringNumBuf=4
... message exchanges ...
[TEST ROUND 2] Completed with vringNumBuf=4
[PHASE 2] SUCCESS: Runtime reconfiguration test passed!
[PHASE 2] vringNumBuf successfully changed from 8 to 4 at runtime
```

### Example 2: Message Corruption During Phase 2

```
[TEST ROUND 1] Completed successfully with vringNumBuf=8

[PHASE 2] Testing runtime reconfiguration...
... deInit and init succeeds ...

[TEST ROUND 2] Running with vringNumBuf=4
... message exchanges start ...
[ERROR] Timeout waiting for message from core R5FSS0_1
[ERROR] TEST_ASSERT_EQUAL_INT32 failed: expected SystemP_SUCCESS, got SystemP_TIMEOUT
```

### Example 3: Init Fails

```
[TEST ROUND 1] Completed successfully with vringNumBuf=8

[PHASE 2] Testing runtime reconfiguration...
[PHASE 2] Calling RPMessage_deInit()...
[PHASE 2] RPMessage_deInit() completed
[PHASE 2] Calling RPMessage_init() with vringNumBuf=4...
[PHASE 2] ERROR: RPMessage_init() failed with status=-1
[PHASE 2] FAILURE: Could not reconfigure vringNumBuf at runtime
```

## Code Location

**File:** `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/test_ipc_rpmsg.c`

**Function:** `test_ipc_main_core_start()` (lines 277-348)

**Phase 2 Logic:** Lines 290-343

## Key Changes from Phase 1

| Aspect | Phase 1 | Phase 2 |
|--------|---------|---------|
| Buffer Count | 8 | 4 |
| Endpoint State | Recreated | Recreated after deInit/init |
| Message Count | 10 | 10 (if successful) |
| Error Handling | Standard | Error status checked explicitly |
| Cleanup | At end | Conditional on success |

## What This Proves

This empirical test will definitively answer:

**Can vringNumBuf be changed at runtime with deInit/init?**

- ✅ YES: Runtime reconfiguration is possible, multiple syscfg files were unnecessary
- ❌ NO: VRING memory corruption or driver errors confirm why multiple syscfg files are required
- ⚠️ PARTIAL: Specific failure mode reveals architectural constraints

All outcomes are valuable for understanding the IPC driver constraints.

## Modifications to test_ipc_rpmsg.c

The following changes were made:

1. Added Phase 2 section in `test_ipc_main_core_start()` after Phase 1 completes
2. Calls `test_rpmsgDestructObjects()` before `RPMessage_deInit()`
3. Adds 500ms delays between critical transitions
4. Creates new `RPMessage_Params` with `vringNumBuf = 4`
5. Calls `RPMessage_init()` with new params
6. Recreates objects via `test_rpmsgCreateObjects()` 
7. Runs second message exchange test
8. Logs success or failure with clear indicators
9. Proper error handling with status checks

No changes needed to remote core logic (they just wait forever after Phase 1).
