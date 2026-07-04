# Region based Address Translate {#KERNEL_DPL_ADDR_TRANSLATE_PAGE}

[TOC]

## Features Supported

- APIs to setup region based address translation using RAT HW on supported SOCs
- APIs to translate 48b SOC view system addr to 32b local CPU view address.
- When no address mapping is specified, no translation is done.

## Features NOT Supported

NA

## Important Usage Guidelines

- The translation API \ref AddrTranslateP_getLocalAddr is meant to be used to translate SOC specified peripheral MMR base
  addresses to local CPU accesible addresses, within device drivers. The API internally searches through a small array to find the address translations, hence to be efficient, this API should typically be called once during driver init to find the local address that CPU should use.

## Errata i2449 — RAT MMR Parity Workaround (R5F only)

Values stored in Pulsar RAT MMRs are not parity protected in hardware. A bit flip in a RAT MMR would not be detected, allowing an unnoticed address translation corruption. This affects both transient (soft) and permanent (hard) errors.

### Workaround

The software workaround is to periodically read back the RAT MMR values and compare them against the intended configuration. The SDK implements this via \ref AddrTranslateP_readbackVerify.

**Automatic check at init:** \ref AddrTranslateP_readbackVerify is called automatically at the end of \ref AddrTranslateP_init as a post-write check, confirming the initial register writes succeeded.

**Periodic runtime check:** Applications requiring functional safety must call \ref AddrTranslateP_readbackVerify periodically at runtime (for example from a periodic timer task or watchdog service routine) to detect any bit flip that occurs after initialization.

```c
/* Example: call from a 1ms periodic safety task */
int32_t status = AddrTranslateP_readbackVerify();
if(status != SystemP_SUCCESS)
{
    /* RAT MMR mismatch detected — handle the error */
}
```
\cond SOC_AM64X || SOC_AM243X || SOC_AM62AX || SOC_AM62DX
- This module is not normally required on R5F CPUs since all peripherals are typically mapped within the 32b address
  space of R5F.
\endcond
\cond SOC_AM64X || SOC_AM243X || SOC_AM62X
- This module is needed for M4F to access peripherals on the MainSS side of the SOC.
\endcond

## Example Usage

Include the below file to access the APIs,
\snippet AddrTranslateP_sample.c include

Example to translate a system address to local CPU address,
\snippet AddrTranslateP_sample.c addr_translate

## API

\ref KERNEL_DPL_ADDR_TRANSLATE
