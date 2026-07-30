# Changes in linker for Smart Placement

::::{only} SOC_AM275X

**Introduction**

To make smart placement functional ([Smart Placement](../components/tools/smart_placement.md)), linker script needs to be changed to account new section that compiler generates.

This page will show what changes needs to be done.

**Linker changes**

Linker will aggregate all function input sections into designated output sections while sorting the placement of input sections based on the given priority. Following code can be added in the linker file to inorder to do that.

::::{only} SOC_AM275X

    SECTIONS

    {

        .TI.local   : {} >> R5F_TCMA | R5F_TCMB | R50_0_OCRAM | FLASH

        .TI.onchip  : {} >> R50_0_OCRAM | FLASH

        .TI.offchip : {} > FLASH

    }

::::

By default, we should use section splitting as shown above between memory regions to get the full effect of function prioritization.

The above linker lines basically channeling all the functions that are annotated to be in `local` memory into TCM memory and if total size of the functions that are marked `local` is more than the size of R5F_TCMA then all the functions that could be placed in R5F_TCMA will be placed in R5F_TCMA and rest of functions will be moved in R5F_TCMB and even if it still fills R5F_TCMB then remaining function will be moved to MSRAM/OCRAM.

Similar treatment is for all the functions that are marked `onchip`, however, they should never be placed in any TCM otherwise it will be logically wrong.

Also, all functions which are marked `offchip`, should be placed in external FLASH.

It should be noted that although annotating using assembler directive is convenient, one short-coming is that static functions cannot be annotated or if annotated, no effect of it is on its placement. To solve this, C/C++ based annotation has to be used in the definition/declaration of that static function.
::::
