# Phase 1: Runtime DeInit/Init Test - vringNumBuf=8 (Baseline)

## Overview
This is the first phase of an empirical test to validate whether `RPMessage_deInit()` + `RPMessage_init()` with different `vringNumBuf` values can work in a multicore environment.

## Phase 1 Objectives

**Primary Goal:** Establish a working baseline with vringNumBuf=8

**What We're Testing:**
- All 4 remote cores (R5FSS0_1, R5FSS1_0, R5FSS1_1, C75SS0_0) communicate with main core
- Message exchange works correctly over IPC
- C75SS1_0 exclusion detection works
- No buffer saturation or corruption

## Test Configuration

- **Folder:** `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2`
- **SysConfig Variant:** cfg3 (4-core, vringNumBuf=8)
- **Message Iterations:** 10 per core
- **Test File:** `test_ipc_rpmsg.c`

## Directory Structure

```
ipc_rpmsg_mcal_2/
├── test_ipc_rpmsg.c                    # Single test file (used by all cores)
├── BUILD_INSTRUCTIONS.md               # Build commands
├── PHASE1_TEST_PLAN.md                # This file
├── am275x-evm/
│   ├── r5fss0-0_freertos/
│   │   ├── example.syscfg              # Main core config
│   │   └── ti-arm-clang/makefile
│   ├── r5fss0-1_freertos/
│   │   ├── example.syscfg              # Remote core config
│   │   └── ti-arm-clang/makefile
│   ├── r5fss1-0_freertos/
│   │   ├── example.syscfg
│   │   └── ti-arm-clang/makefile
│   ├── r5fss1-1_freertos/
│   │   ├── example.syscfg
│   │   └── ti-arm-clang/makefile
│   └── c75ss0-0_freertos/
│       ├── example.syscfg              # C75 DSP core config
│       └── ti-c7000/makefile
```

## Test Execution Flow

### Boot Phase
```
1. SBL loads all 4 cores via UART
2. Each core initializes with RPMessage_init(vringNumBuf=8)
3. Main core (R5FSS0_0) detects C75SS1_0 availability
4. Server tasks start on all cores
```

### Test Phase
```
1. Main core initiates test_rpmsgAnyToAny()
2. For 10 iterations:
   a. Send message to each remote core
   b. Receive echo response
   c. Verify message integrity
3. Remote cores process messages as they arrive
4. Test completes successfully → Phase 1 PASS
```

### Shutdown Phase
```
1. Objects destructed
2. Test marked complete
```

## Expected Output - Phase 1 Success

```
[TEST IPC RPMSG] MCAL IPC test mode
[TEST IPC RPMSG] Remote cores initialized and ready for IPC
[TEST IPC RPMSG] MCAL on R5FSS0_0 will initiate communication

[TEST ROUND 1] Running with vringNumBuf=8
... 10 successful message exchanges ...
[TEST ROUND 1] Completed successfully with vringNumBuf=8

[TEST IPC RPMSG] Test completed - remote cores ready for MCAL app
```

## Potential Failure Points

### Buffer Overflow (DEM Error 0xffe8)
- **Symptom:** Timeout or error during message send
- **Cause:** 10 iterations too many with limited memory
- **Solution:** Reduce gMsgEchoCount if needed

### Endpoint Collision
- **Symptom:** Server endpoint creation fails
- **Cause:** Fixed MCAL endpoints conflict with test endpoints
- **Solution:** Already handled by using MCAL endpoint mapping

### C75SS1_0 Invalid Parameters Error
- **Symptom:** Remote core fails during init
- **Cause:** C75SS1_0 not included in this config but code tries to use it
- **Solution:** gExcludeC75SS1_0 flag handles this at runtime

### SysConfig Generation Failure
- **Symptom:** Missing ti_drivers_config files
- **Cause:** Makefile syscfg target didn't generate files
- **Solution:** Run `make syscfg` manually before building

## Success Criteria - Phase 1

✅ All 4 cores boot successfully
✅ Main core receives echoes from all 4 remote cores
✅ 10 complete message exchange cycles complete
✅ No DEM errors or timeout errors
✅ No assertion failures

## After Phase 1 Passes

Once this baseline test passes consistently, Phase 2 will add:

1. **DeInit Call:** After Phase 1 test completes
   ```c
   RPMessage_deInit();
   ```

2. **Reconfiguration:** Reinitialize with vringNumBuf=4
   ```c
   RPMessage_Params rpmsgParams;
   RPMessage_Params_init(&rpmsgParams);
   rpmsgParams.vringNumBuf = 4;  // Different buffer count
   RPMessage_init(&rpmsgParams);
   ```

3. **Phase 2 Test:** Run message exchange again with new buffer config

4. **Validation:** Check for:
   - VRING memory corruption
   - Descriptor alignment issues
   - Message loss or duplication

## Notes for Testing

- Keep terminal logs for comparison between Phase 1 and Phase 2
- Watch for any spurious errors even if test "passes"
- VRING corruption may manifest as intermittent failures in Phase 2
- Pay special attention to endpoint communication patterns

## File Paths Reference

- **Main Test Code:** 
  - `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/test_ipc_rpmsg.c`

- **SysConfig Files:**
  - R5FSS0_0: `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/r5fss0-0_freertos/example.syscfg`
  - Similar for other cores

- **Expected Build Outputs:**
  - `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2/am275x-evm/[core]_freertos/ti-[compiler]/test_ipc_rpmsg.debug.out`
