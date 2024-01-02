/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#include <board/flash.h>
#include <board/flash/gpmc/flash_nand_gpmc.h>



#define APP_GPMC_FLASH_OFFSET_BASE  (0x000000)
#define APP_GPMC_DATA_SIZE          (0x40000)

uint8_t gGpmcTxBuf[APP_GPMC_DATA_SIZE] ;
/* read buffer MUST be cache line aligned when using DMA, we aligned to 128B though 32B is enough */
uint8_t gGpmcRxBuf[APP_GPMC_DATA_SIZE] __attribute__((aligned(128)));



void gpmc_flash_io_fill_buffers();
int32_t gpmc_flash_io_compare_buffers();

void gpmc_flash_io_main(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t offset;
    uint32_t blk, page;
    Flash_Attrs *flashAttrs;

    flashAttrs = Flash_getAttrs(CONFIG_FLASH0);

    /* Fill buffers with known data,
     * find block number from offset,
     * erase block, write the data, read back from a specific offset
     * and finally compare the results.
     */
    offset = APP_GPMC_FLASH_OFFSET_BASE;
    gpmc_flash_io_fill_buffers();
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTxBuf, APP_GPMC_DATA_SIZE);
    Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gGpmcRxBuf, APP_GPMC_DATA_SIZE);
    status |= gpmc_flash_io_compare_buffers();

    offset = APP_GPMC_FLASH_OFFSET_BASE + (flashAttrs->blockSize*2048);
    gpmc_flash_io_fill_buffers();
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTxBuf, APP_GPMC_DATA_SIZE);
    Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gGpmcRxBuf, APP_GPMC_DATA_SIZE);
    status |= gpmc_flash_io_compare_buffers();

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

}

void gpmc_flash_io_fill_buffers()
{
    uint32_t i;

    for(i = 0U; i < APP_GPMC_DATA_SIZE; i++)
    {
        gGpmcTxBuf[i] = i % 256;
        gGpmcRxBuf[i] = 0U;
    }
}

int32_t gpmc_flash_io_compare_buffers()
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i;

    for(i = 0U; i < APP_GPMC_DATA_SIZE; i++)
    {
        if(gGpmcTxBuf[i] != gGpmcRxBuf[i])
        {
            status = SystemP_FAILURE;
            DebugP_logError("GPMC read data mismatch !!!\r\n");
            break;
        }
    }
    return status;
}

