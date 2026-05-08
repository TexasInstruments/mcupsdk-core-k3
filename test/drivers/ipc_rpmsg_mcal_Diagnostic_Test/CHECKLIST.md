# Phase 1 Execution Checklist

## Pre-Build Verification

- [x] Folder structure created
- [x] test_ipc_rpmsg.c copied and modified
- [x] example.syscfg (cfg3) copied to all cores
- [x] Makefiles updated with correct include paths
- [x] Documentation created (PHASE1_TEST_PLAN.md, QUICK_START.md, etc.)

## Build Phase

- [ ] SysConfig files generated for all cores
  - [ ] r5fss0-0: `make -C am275x-evm/r5fss0-0_freertos/ti-arm-clang syscfg PROFILE=debug`
  - [ ] r5fss0-1: `make -C am275x-evm/r5fss0-1_freertos/ti-arm-clang syscfg PROFILE=debug`
  - [ ] r5fss1-0: `make -C am275x-evm/r5fss1-0_freertos/ti-arm-clang syscfg PROFILE=debug`
  - [ ] r5fss1-1: `make -C am275x-evm/r5fss1-1_freertos/ti-arm-clang syscfg PROFILE=debug`
  - [ ] c75ss0-0: `make -C am275x-evm/c75ss0-0_freertos/ti-c7000 syscfg PROFILE=debug`

- [ ] All cores compiled successfully
  - [ ] r5fss0-0: `make -C am275x-evm/r5fss0-0_freertos/ti-arm-clang PROFILE=debug`
  - [ ] r5fss0-1: `make -C am275x-evm/r5fss0-1_freertos/ti-arm-clang PROFILE=debug`
  - [ ] r5fss1-0: `make -C am275x-evm/r5fss1-0_freertos/ti-arm-clang PROFILE=debug`
  - [ ] r5fss1-1: `make -C am275x-evm/r5fss1-1_freertos/ti-arm-clang PROFILE=debug`
  - [ ] c75ss0-0: `make -C am275x-evm/c75ss0-0_freertos/ti-c7000 PROFILE=debug`

- [ ] Binaries generated in each core's directory
  - [ ] test_ipc_rpmsg.debug.out present in all 5 core directories

## Flash & Boot Phase

- [ ] Bootloader config created based on cfg3 template
  - [ ] Path: Similar to `ipc_rpmsg_test_sbl_uart_hs_fs_cfg3.cfg`
  - [ ] Updated to point to binaries from `ipc_rpmsg_mcal_2` folder

- [ ] UART connection ready
  - [ ] Serial terminal open on correct port/baud rate
  - [ ] Ready to capture boot logs

- [ ] Flash via UART SBL
  - [ ] Command executed with updated config
  - [ ] All 4 cores load successfully

## Test Execution Phase

### Expected Boot Log Indicators

- [ ] SBL prints boot messages
- [ ] All 4 cores load and start executing
- [ ] C75SS1_0 detection occurs (should be excluded)
  - [ ] Message: "[IPC] C75SS1_0 excluded - Using 4-core configuration"
  
### Expected Test Log Indicators

- [ ] Main core prints: "[TEST IPC RPMSG] MCAL IPC test mode"
- [ ] Message: "[TEST ROUND 1] Running with vringNumBuf=8"
- [ ] Each remote core prints: "[IPC] Core R5FSS0_1: Remote core waiting..."
- [ ] Main core completes 10 message exchanges
  - [ ] No timeout errors
  - [ ] No buffer overflow errors
- [ ] Message: "[TEST ROUND 1] Completed successfully with vringNumBuf=8"
- [ ] No assertion failures
- [ ] Clean test completion: "Test completed - remote cores ready"

## Post-Test Analysis

- [ ] Review complete boot log for errors
- [ ] Count message exchanges (should see 10 + acknowledgments)
- [ ] Check for any DEM errors (0xffe8 or others)
- [ ] Verify all 4 cores participated
- [ ] No hangs or timeouts occurred

## Phase 1 Success Criteria

✅ Phase 1 is PASS if:
- All 4 cores boot successfully
- Message exchange completes 10 iterations
- No errors in logs
- Test prints completion message

## If Phase 1 FAILS

Document:
- [ ] What error occurred?
- [ ] Which core failed?
- [ ] Error message text
- [ ] Which log file/timestamp?

Possible causes:
- SysConfig generation failed → redo `make syscfg`
- Build failed → check compiler flags in makefile
- VRING memory out of bounds → reduce gMsgEchoCount
- Endpoint collision → check getServerEndPtForCore() mapping
- C75SS1_0 still being accessed → verify gExcludeC75SS1_0 logic

## Phase 1 Troubleshooting

### Symptom: DEM Error 0xffe8
- Likely: 10 iterations too many
- Fix: Reduce gMsgEchoCount to 5 in test_ipc_rpmsg.c line 46

### Symptom: Endpoint collision errors
- Check: test endpoints 11, 12 not conflicting with MCAL endpoints (13-17)
- These are already configured correctly in the test file

### Symptom: C75SS1_0 "invalid parameters" error
- Check: gExcludeC75SS1_0 detection in test_rpmsgCreateObjects()
- Verify: Send attempt with 0 timeout at line ~121

### Symptom: Build fails on syscfg
- Fix: Manually run: `make -C [core] syscfg PROFILE=debug`
- Verify: generated/ folder contains ti_drivers_config files

## After Phase 1 PASS

Proceed to Phase 2:
1. Update test_ipc_rpmsg.c (add deInit/init logic)
2. Rebuild all cores
3. Flash and test again
4. Observe if any new errors appear with vringNumBuf=4
5. Document findings in new memory note
