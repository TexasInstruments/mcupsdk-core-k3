# Flash

```{contents}
:depth: 2
:local:
```

::::{only} SOC_AM243X or SOC_AM273X or SOC_AM64X or SOC_AWR294X

The Flash driver provides API to read and write to xSPI based flash devices present in the board.

::::

::::{only} SOC_AM263X

The Flash driver provides API to read and write to QSPI based flash devices present in the board.

::::

The driver takes care of all sequencing necessary to perform writes across pages and
the application need not take care of the programming intricacies.

## Features Supported

- APIs to read and write to a flash offset
- Provides API to return flash attributes like block size, page size etc
- API for block erases


::::{only} SOC_AM62LX or SOC_AM62PX or SOC_AM62X or SOC_AM62DX or SOC_AM275X

## Flash Layout

The NOR flash S28HS512T present in AM62 SoCs allows users to configure flash in different
layouts by writing to the configuration registers, a feature not supported by other NOR flash
devices. Other NOR flash parts from vendors like Micron, Macronix, ISSI, and Winbond only
support uniform flash layouts, where the entire flash is divided into blocks of uniform size,
with blocks further divided into sectors. In these standard flash devices, block erase and
sector erase operations can be performed at any offset, erasing either an entire block or a
sector based on the operation chosen.

In contrast, the S28HS512T supports sector erase operations only in non-uniform mode specifically
on the 4KB sectors. In uniform mode, only block erase operations are allowed, and attempting sector
erase operations has no effect.

The S28HS512T supports four different flash layouts:
- **Uniform**: The entire flash is divided into uniform 256KB blocks.
- **Bottom Hybrid**: The first 256KB of flash is divided into 32 sectors of 4KB each and 1 block
  of 128KB, while the remaining flash is divided into 256KB blocks.
- **Top Hybrid**: The last 256KB of flash is divided into 32 sectors of 4KB each and 1 block of
  128KB, while the remaining flash is divided into 256KB blocks.
- **Split Hybrid**: The first and last blocks are each divided into 16 sectors of 4KB and 1
  block of 192KB, with the middle portion of flash divided into 256KB blocks.

### How To Configure Hybrid Layout

### Flash Layout Configuration

   The S28HS512T NOR flash supports multiple memory layout configurations that affect sector organization
   and erase operations. The driver automatically configures the flash layout during initialization through
   the `Flash_quirkSpansionConfigureLayout` function in `flash_nor_ospi.c`.

   ### Configuring Flash Layout

   To customize the flash layout, modify the layout configuration using `Flash_NorOspiHybridLayoutCfg`
   structure before calling flash open.

   ```c
   typedef struct {
       uint32_t isHybridLayout;     /* 0: Uniform layout, 1: Hybrid layout */
       uint32_t hybridLayoutType;   /* Hybrid layout type (see table below) */
   } Flash_NorOspiHybridLayoutCfg;
   ```

   ### Available Layout Options

   #### Main Layout Types

   | Layout Type | Value | Description |
   |-------------|-------|-------------|
   | Uniform Layout | 0U | Standard uniform sector sizes throughout the entire flash memory |
   | Hybrid Layout | 1U | Mixed sector sizes for more flexible memory management |

   #### Hybrid Layout Configurations

   When `isHybridLayout` is set to 1, you must specify the hybrid layout type using
   `hybridLayoutType`:

   | Hybrid Layout Type | Value | Description |
   |-------------------|-------|-------------|
   | Bottom Hybrid | 0U | Smaller sectors at the bottom (low addresses) of flash memory |
   | Top Hybrid | 1U | Smaller sectors at the top (high addresses) of flash memory |
   | Split Hybrid | 2U | Smaller sectors at both bottom and top of flash memory |

   ### Example Configuration

   For a hybrid layout with smaller sectors at both the bottom and top of memory (Split Hybrid):

   ```c
   /* Get the layout configuration from flash config */
   Flash_NorOspiHybridLayoutCfg *layoutCfg = (Flash_NorOspiHybridLayoutCfg*)(gFlashConfig[CONFIG_FLASH0].layoutCfg);

   /* Configure for split hybrid layout */
   layoutCfg->isHybridLayout = 1U;      /* Hybrid layout */
   layoutCfg->hybridLayoutType = 2U;    /* Split hybrid type */
   ```

   ### Custom Flash Layout Implementation

   Developers can implement their own custom configuration function to accommodate
   specific flash layouts according to flash datasheet specifications.
   This is particularly useful when:

   - Working with flash devices that have non-standard sector arrangements
   - Implementing custom command sequences
   - Supporting specialized flash memory with unique organization requirements

   To add a custom flash configuration function:
   1. Define a layout configuration struct as described in [Configuring Flash Layout](#configuring-flash-layout).
   This struct can be accessed within your quirk function via the `Flash_Config *cfg` parameter.
   The config struct includes a `void* layoutCfg` pointer that references your layout configuration.

   2. Implement your quirk function in `flash_nor_ospi.c` following the required signature:
      ```c
      int32_t YourQuirkFunction(Flash_Config *cfg);
      ```

   3. Register your quirk function by updating the `quirk_function` field in the flash section of your board configuration.

   Example implementation:

   ```c
   /* In flash_nor_ospi.c */
   int32_t myQuirksFxn(Flash_Config *cfg)
   {
       int32_t status = SystemP_SUCCESS;

       /* Access layout configuration if needed */
       MyFlashLayoutCfg *layoutCfg = (MyFlashLayoutCfg *)cfg->layoutCfg;

       /* Your code for handling quirks goes here */
       /* For example: modify flash timing parameters, handle special initialization, etc. */

       return status;
   }
   ```

```{image} ../../images/flash_quirks.png
:align: center
:alt: Flash Quirks Fxn Configuration
```

::::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Option to select flash type based on board

:::{only} SOC_AM64X or SOC_AM243X
   - Supported flash devices
       - S28HS512T
       - S25HL512T
       - MX25LM25645G
:::


:::{only} SOC_AM263X
   - Supported flash devices
       - S25FL128SA
:::


:::{only} SOC_AM273X or SOC_AWR294X
   - Supported flash devices
       - GD25B64C
:::


:::{only} SOC_AM62X
   - Supported flash devices
       - S28HS512T
       - W35N01JW
:::


:::{only} SOC_AM62PX
   - Supported flash devices
       - S28HS512T
:::


:::{only} SOC_AM62AX
   - Supported flash devices
       - W35N01JW
:::


:::{only} SOC_AM62DX or SOC_AM275X or SOC_AM62LX
   - Supported flash devices
       - S28HS512T
:::


## Features NOT Supported

NA

## Important Usage Guidelines

- Typically before writing to an offset, erase the block which corresponds to the offset
- Flash writes can only be done to a page size aligned offset, otherwise the write API returns an error

:::{only} SOC_AM64X or SOC_AM243X
   - The `sbl_ospi` will be typically flashed at location 0x00000000 in the flash memory. So applications using flash should refrain from using this offset. Similarly, the starting of the last block of the flash is used for storing attackVector patterns later used for PHY tuning. So avoid using this offset as well.
:::


:::{only} SOC_AM263X
   - The `sbl_qspi` will be typically flashed at location 0x00000000 in the flash memory. So applications using flash should refrain from using this offset.
:::


## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Flash_sample.c
:language: c
:lines: 3-5
```

### Flash Read API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Flash_sample.c
:language: c
:lines: 15-24
```

### Flash Write API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Flash_sample.c
:language: c
:lines: 49-58
```

### Flash Erase API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Flash_sample.c
:language: c
:lines: 30-43
```

## API Reference

```{doxygenfile} flash.h
```
