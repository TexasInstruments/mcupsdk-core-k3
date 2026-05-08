# ipc_rpmsg_mcal_2: Runtime DeInit/Init Test

This folder contains a test for empirically validating whether `RPMessage_deInit()` followed by `RPMessage_init()` with different `vringNumBuf` values works in practice.

## Test Phases

### Phase 1: vringNumBuf=8 (Initial Test)
- All cores boot with vringNumBuf=8 (cfg3 syscfg)
- Main core (R5FSS0_0) runs test with 8 buffers
- Verify message exchange works correctly
- **Status:** Ready to build and test

### Phase 2: DeInit/Init Transition (Next Phase)
- After Phase 1 passes, add deInit/init logic
- Transition from vringNumBuf=8 to vringNumBuf=4
- Verify message exchange still works with new buffer count
- This will test whether VRING memory reinitialization causes corruption

## Build Instructions

### Prerequisites
```bash
cd /home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal_2
```

### Generate SysConfig Files

For each core:
```bash
cd am275x-evm/r5fss0-0_freertos/ti-arm-clang
make syscfg
cd ../../..

cd am275x-evm/r5fss0-1_freertos/ti-arm-clang
make syscfg
cd ../../..

cd am275x-evm/r5fss1-0_freertos/ti-arm-clang
make syscfg
cd ../../..

cd am275x-evm/r5fss1-1_freertos/ti-arm-clang
make syscfg
cd ../../..

cd am275x-evm/c75ss0-0_freertos/ti-c7000
make syscfg
cd ../../..
```

### Build All Cores
```bash
make PROFILE=debug -C am275x-evm/r5fss0-0_freertos/ti-arm-clang
make PROFILE=debug -C am275x-evm/r5fss0-1_freertos/ti-arm-clang
make PROFILE=debug -C am275x-evm/r5fss1-0_freertos/ti-arm-clang
make PROFILE=debug -C am275x-evm/r5fss1-1_freertos/ti-arm-clang
make PROFILE=debug -C am275x-evm/c75ss0-0_freertos/ti-c7000
```

### Flash via UART
Create bootloader config similar to:
- `/home/uda0507213/ti/jacinto/workarea/mcu_plus_sdk/test/drivers/ipc_rpmsg_mcal/am275x-evm/ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg`

Pointing to binaries from this folder instead.

## Expected Results - Phase 1

✅ All 4 remote cores communicate successfully with main core
✅ Each iteration completes message exchange (10 iterations per test)
✅ No buffer overflow errors (DEM errors)
✅ No endpoint collision errors

## Test File Locations

- **Test Code:** `test_ipc_rpmsg.c`
- **SysConfig:** `am275x-evm/[core]_freertos/example.syscfg`
- **Makefiles:** `am275x-evm/[core]_freertos/ti-[compiler]/makefile`

## Next Steps

After Phase 1 passes, update `test_ipc_rpmsg.c` to add:
1. After Phase 1 test completes: `RPMessage_deInit()`
2. Reinitialization with vringNumBuf=4
3. Second message exchange test round
4. Verify no VRING memory corruption occurs
