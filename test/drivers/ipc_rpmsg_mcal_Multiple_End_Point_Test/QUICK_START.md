# Quick Start - Phase 1 Build & Test

## One-Liner Build (All Cores)

```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2

# Generate syscfg for all cores
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang syscfg PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug

# Build all cores
for core in r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1; do
  make -C am275x-evm/${core}_freertos/ti-arm-clang PROFILE=debug
done
make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug
```

## Output Binaries Location

```
am275x-evm/r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.debug.out
am275x-evm/r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.debug.out
am275x-evm/r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.debug.out
am275x-evm/r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.debug.out
am275x-evm/c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.debug.out
```

## Create Bootloader Config

Based on: `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg`

Update paths to point to binaries from `ipc_rpmsg_mcal_2` folder instead.

## Expected Success Indicators

✅ All 4 cores boot
✅ Message exchanges work
✅ No timeout/buffer errors
✅ "Test completed" message appears

## Next: Phase 2

After Phase 1 passes, add to `test_ipc_rpmsg.c` after line 98:

```c
/* DeInit and reconfigure to test vringNumBuf change */
RPMessage_deInit();
ClockP_sleep(500);  // Delay for deInit to complete

/* Re-init with different vringNumBuf */
RPMessage_Params newParams;
RPMessage_Params_init(&newParams);
newParams.vringNumBuf = 4;  // Changed from 8
RPMessage_init(&newParams);

/* Second test round */
DebugP_log("\n[TEST ROUND 2] Running with vringNumBuf=4\r\n");
test_rpmsgAnyToAny(NULL);
DebugP_log("[TEST ROUND 2] Completed with vringNumBuf=4\r\n");
```

Then rebuild and test to see if VRING memory corruption occurs.
