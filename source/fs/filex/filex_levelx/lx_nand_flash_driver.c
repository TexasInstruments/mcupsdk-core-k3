/*
 *  Copyright (C) 2018-2024 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "lx_api.h"
#include <tx_api.h>
#include "lx_nand_flash_driver.h"

#include <board/flash.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/SystemP.h>

/* This driver only supports control block enabled. */
#ifndef LX_NAND_ENABLE_CONTROL_BLOCK_FOR_DRIVER_INTERFACE
#error "Control block mode must be enabled."
#endif


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Maximum number of this driver instances. */
#define LX_NAND_DRIVER_MAX_INSTANCE_COUNT             (4u)

/* Maximum supported page size. */
#define LX_NAND_DRIVER_MAX_PAGE_SIZE               (4096u)

/* Maximum supported spare area size. */
#define LX_NAND_DRIVER_MAX_SPARE_SIZE               (256u)

/* Needed spare area field lengths required by LevelX. */
#define LX_NAND_DRIVER_SPARE_DATA1_LENGTH             (4u)
#define LX_NAND_DRIVER_SPARE_DATA2_LENGTH             (2u)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* NAND driver instance. */
typedef struct lx_nand_driver {
    LX_NAND_FLASH *p_nand_flash;
    Flash_Handle flash_handle;
    Flash_Attrs *p_attrs;
    const UINT (*spare_map)[2];
    size_t spare_map_length;
    uint64_t offset;
    uint64_t size;
} lx_nand_driver_t;


/* Global NAND driver data. */
typedef struct lx_nand_driver_data {
    lx_nand_driver_t t_instances[LX_NAND_DRIVER_MAX_INSTANCE_COUNT];
    size_t instance_cnt;
    TX_MUTEX page_buf_mutex;
    bool init;
} lx_nand_driver_data_t;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static lx_nand_driver_data_t g_nand_driver_data = {0};
static uint8_t gt_page_buf[LX_NAND_DRIVER_MAX_PAGE_SIZE + LX_NAND_DRIVER_MAX_SPARE_SIZE]__attribute__((aligned(128u)));


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static UINT  lx_nand_driver_read(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, ULONG *destination, ULONG words);
static UINT  lx_nand_driver_write(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, ULONG *source, ULONG words);
static UINT  lx_nand_driver_block_erase(LX_NAND_FLASH *nand_flash, ULONG block, ULONG erase_count);
static UINT  lx_nand_driver_block_erased_verify(LX_NAND_FLASH *nand_flash, ULONG block);
static UINT  lx_nand_driver_page_erased_verify(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page);
static UINT  lx_nand_driver_block_status_get(LX_NAND_FLASH *nand_flash, ULONG block, UCHAR *bad_block_byte);
static UINT  lx_nand_driver_block_status_set(LX_NAND_FLASH *nand_flash, ULONG block, UCHAR bad_block_byte);
static UINT  lx_nand_driver_extra_bytes_get(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR *destination, UINT size);
static UINT  lx_nand_driver_extra_bytes_set(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR *source, UINT size);
static UINT  lx_nand_driver_system_error(LX_NAND_FLASH *nand_flash, UINT error_code, ULONG block, ULONG page);

static UINT  lx_nand_driver_pages_read(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR* main_buffer, UCHAR* spare_buffer, ULONG pages);
static UINT  lx_nand_driver_pages_write(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR* main_buffer, UCHAR* spare_buffer, ULONG pages);
static UINT  lx_nand_driver_pages_copy(LX_NAND_FLASH *nand_flash, ULONG source_block, ULONG source_page, ULONG destination_block, ULONG destination_page, ULONG pages, UCHAR* data_buffer);

static lx_nand_driver_t *lx_nand_driver_get(LX_NAND_FLASH *p_nand_flash);


/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */

UINT  lx_nand_driver_create(LX_NAND_FLASH *p_nand_flash, uint32_t flash_instance_id, uint32_t offset,
                            uint32_t size, const UINT spare_map[][2], size_t spare_map_length)
{
    lx_nand_driver_t *p_nand_driver;
    UINT res;

    p_nand_driver = &g_nand_driver_data.t_instances[g_nand_driver_data.instance_cnt];
    g_nand_driver_data.instance_cnt++;

    p_nand_driver->p_nand_flash = p_nand_flash;
    p_nand_driver->p_attrs = Flash_getAttrs(flash_instance_id);
    p_nand_driver->flash_handle = Flash_getHandle(flash_instance_id);
    DebugP_assert(offset % p_nand_driver->p_attrs->blockSize == 0);
    DebugP_assert((size == (uint32_t)-1) || (size % p_nand_driver->p_attrs->blockSize == 0));

    p_nand_driver->spare_map = spare_map;
    p_nand_driver->spare_map_length = spare_map_length;

    p_nand_driver->offset = offset;
    p_nand_driver->size = size == (uint32_t)-1 ? p_nand_driver->p_attrs->flashSize - offset : size;

    if (!g_nand_driver_data.init) {
        g_nand_driver_data.init = true;
        res = tx_mutex_create(&g_nand_driver_data.page_buf_mutex, "lx_nand_driver_buf_mutex", TX_INHERIT);
        if (res != SystemP_SUCCESS) {
            return (LX_ERROR);
        }
    }

    return (LX_SUCCESS);
}


UINT lx_nand_driver_init(LX_NAND_FLASH *p_nand_flash)
{
    lx_nand_driver_t *p_nand_driver;

    p_nand_driver = lx_nand_driver_get(p_nand_flash);

    /* Setup geometry of the NAND flash.  */
    p_nand_flash->lx_nand_flash_total_blocks = p_nand_driver->p_attrs->blockCount - p_nand_driver->offset / p_nand_driver->p_attrs->blockSize;
    p_nand_flash->lx_nand_flash_pages_per_block = p_nand_driver->p_attrs->blockSize / p_nand_driver->p_attrs->pageSize;
    p_nand_flash->lx_nand_flash_bytes_per_page = p_nand_driver->p_attrs->pageSize;

    /* Setup function pointers for the NAND flash services.  */
    p_nand_flash->lx_nand_flash_driver_read = lx_nand_driver_read;
    p_nand_flash->lx_nand_flash_driver_write = lx_nand_driver_write;
    p_nand_flash->lx_nand_flash_driver_block_erase = lx_nand_driver_block_erase;
    p_nand_flash->lx_nand_flash_driver_block_erased_verify = lx_nand_driver_block_erased_verify;
    p_nand_flash->lx_nand_flash_driver_page_erased_verify = lx_nand_driver_page_erased_verify;
    p_nand_flash->lx_nand_flash_driver_block_status_get = lx_nand_driver_block_status_get;
    p_nand_flash->lx_nand_flash_driver_block_status_set = lx_nand_driver_block_status_set;
    p_nand_flash->lx_nand_flash_driver_extra_bytes_get = lx_nand_driver_extra_bytes_get;
    p_nand_flash->lx_nand_flash_driver_extra_bytes_set = lx_nand_driver_extra_bytes_set;
    p_nand_flash->lx_nand_flash_driver_system_error = lx_nand_driver_system_error;

    p_nand_flash->lx_nand_flash_driver_pages_read = lx_nand_driver_pages_read;
    p_nand_flash->lx_nand_flash_driver_pages_write = lx_nand_driver_pages_write;
    p_nand_flash->lx_nand_flash_driver_pages_copy = lx_nand_driver_pages_copy;


    for (size_t spare_map_ix = 0u; spare_map_ix < p_nand_driver->spare_map_length; spare_map_ix++) {
        UINT spare_offset = 0u;
        if (p_nand_flash->lx_nand_flash_spare_data1_length == 0u) {
            if (p_nand_driver->spare_map[spare_map_ix][1] - spare_offset >= LX_NAND_DRIVER_SPARE_DATA1_LENGTH) {
                p_nand_flash->lx_nand_flash_spare_data1_offset = p_nand_driver->spare_map[spare_map_ix][0] + spare_offset;
                p_nand_flash->lx_nand_flash_spare_data1_length = LX_NAND_DRIVER_SPARE_DATA1_LENGTH;
                spare_offset += LX_NAND_DRIVER_SPARE_DATA1_LENGTH;
            }
        }
        if ((p_nand_flash->lx_nand_flash_spare_data1_length > 0u) && (p_nand_flash->lx_nand_flash_spare_data2_length == 0u)) {
            if (p_nand_driver->spare_map[spare_map_ix][1] - spare_offset >= LX_NAND_DRIVER_SPARE_DATA2_LENGTH) {
                p_nand_flash->lx_nand_flash_spare_data2_offset = p_nand_driver->spare_map[spare_map_ix][0] + spare_offset;
                p_nand_flash->lx_nand_flash_spare_data2_length = LX_NAND_DRIVER_SPARE_DATA2_LENGTH;
                break;
            }
        }
    }

    // Make sure that there is enough room in the spare area and that
    // everything is properly initialized.
    DebugP_assert((p_nand_flash->lx_nand_flash_spare_data1_length > 0u) &&
                  (p_nand_flash->lx_nand_flash_spare_data2_length > 0u));

    p_nand_flash->lx_nand_flash_spare_total_length = p_nand_driver->p_attrs->spareAreaSize;

    return (LX_SUCCESS);
}


uint64_t lx_nand_driver_size_get(LX_NAND_FLASH *nand_flash)
{
    lx_nand_driver_t *p_nand_driver;

    p_nand_driver = lx_nand_driver_get(nand_flash);

    DebugP_assert(p_nand_driver->p_attrs != NULL);
    return (p_nand_driver->size);
}


/* Note used by LevelX. */
static UINT lx_nand_driver_read(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, ULONG *destination, ULONG words)
{
    (void)nand_flash;
    (void)block;
    (void)page;
    (void)destination;
    (void)words;

    DebugP_assert(0);
    return (LX_ERROR);
}


static UINT lx_nand_driver_pages_read(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR* main_buffer, UCHAR* spare_buffer, ULONG pages)
{
    lx_nand_driver_t *p_nand_driver;
    ULONG block_offset;
    Flash_Attrs *p_attrs;
    ULONG first_page_num;
    ULONG res;
    int32_t ret;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    block_offset = p_nand_driver->offset / p_attrs->blockSize;
    first_page_num = (block_offset + block) * p_attrs->pageCount + page;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    for (ULONG i = 0u; i < pages; i++) {

        ret = Flash_readPage(p_nand_driver->flash_handle, first_page_num + i, 0u, &gt_page_buf[0], p_attrs->pageSize + p_attrs->spareAreaSize);
        if (ret != SystemP_SUCCESS) {
            (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
            DebugP_logError("Flash_readPage() failed with %u.\n", ret);
            return (LX_ERROR);
        }

        if (main_buffer) {
            memcpy(main_buffer + i * p_attrs->pageSize, &gt_page_buf[0], p_attrs->pageSize);
        }
        if (spare_buffer) {
            memcpy(spare_buffer + i * p_attrs->spareAreaSize, &gt_page_buf[0] + p_attrs->pageSize, p_attrs->spareAreaSize);
        }
    }

    res = tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    return (LX_SUCCESS);
}


/* Note used by LevelX. */
static UINT lx_nand_driver_write(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, ULONG *source, ULONG words)
{
    (void)nand_flash;
    (void)block;
    (void)page;
    (void)source;
    (void)words;

    DebugP_assert(0);
    return (LX_ERROR);
}


static UINT lx_nand_driver_pages_write(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR* main_buffer, UCHAR* spare_buffer, ULONG pages)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    ULONG first_block;
    ULONG start_page;
    int32_t ret;
    UINT res;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    first_block = p_nand_driver->offset / p_attrs->blockSize;
    start_page = (first_block + block) * p_attrs->pageCount + page;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    for (ULONG i = 0u; i < pages; i++) {

        if (main_buffer) {
            memcpy(&gt_page_buf[0], main_buffer + i * p_attrs->pageSize, p_attrs->pageSize);
        }
        if (spare_buffer) {
            memcpy(&gt_page_buf[0] + p_attrs->pageSize, spare_buffer + i * p_attrs->spareAreaSize, p_attrs->spareAreaSize);
        }

        ret = Flash_writePage(p_nand_driver->flash_handle, start_page + i, &gt_page_buf[0], p_attrs->pageSize + p_attrs->spareAreaSize);
        if (ret != SystemP_SUCCESS) {
            (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
            DebugP_logError("Flash_writePage() failed with %u.\n", ret);
            return (LX_ERROR);
        }
    }

    res = tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    return (LX_SUCCESS);
}


static UINT lx_nand_driver_pages_copy(LX_NAND_FLASH *nand_flash, ULONG source_block, ULONG source_page, ULONG destination_block, ULONG destination_page, ULONG pages, UCHAR *data_buffer)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    UINT status = LX_SUCCESS;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    for (UINT i = 0u; i < pages; i++) {

        status = lx_nand_driver_pages_read(nand_flash, source_block, source_page + i, data_buffer, data_buffer + p_attrs->pageSize, 1);
        if (status != LX_SUCCESS) return (status);

        status = lx_nand_driver_pages_write(nand_flash, destination_block, destination_page + i, data_buffer, data_buffer + p_attrs->pageSize, 1);
        if (status != LX_SUCCESS) return (status);
    }

    return (LX_SUCCESS);
}


static UINT lx_nand_driver_block_erase(LX_NAND_FLASH *nand_flash, ULONG block, ULONG erase_count)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    ULONG block_offset;
    int32_t ret;

    (void)erase_count;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    block_offset = p_nand_driver->offset / p_attrs->blockSize;
    ret = Flash_eraseBlk(p_nand_driver->flash_handle, block_offset + block);
    if (ret != SystemP_SUCCESS) {
        DebugP_logError("Flash_eraseBlk() failed with %u.\n", ret);
        return (LX_ERROR);
    }

    return (LX_SUCCESS);
}



static UINT lx_nand_driver_block_erased_verify(LX_NAND_FLASH *nand_flash, ULONG block)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    uint32_t first_page_num;
    ULONG block_offset;
    int32_t ret;
    UINT res;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    block_offset = p_nand_driver->offset / p_attrs->blockSize;
    first_page_num = (block_offset + block) * p_attrs->pageCount;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    for (ULONG i = 0u; i < p_attrs->pageCount; i++) {

        ret = Flash_readPage(p_nand_driver->flash_handle, first_page_num + i, 0u, &gt_page_buf[0], p_attrs->pageSize + p_attrs->spareAreaSize);
        if (ret != SystemP_SUCCESS) {
            (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
            DebugP_logError("Flash_readPage() failed with %u.\n", ret);
            return (LX_ERROR);
        }

        for (size_t k = 0u; k < (p_attrs->pageSize + p_attrs->spareAreaSize) / 4u; k++) {
            if (((uint32_t *)gt_page_buf)[k] != 0xFFFFFFFF) {
                (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
                DebugP_logError("lx_nand_driver_block_erased_verify() verification failed.\n");
                return (LX_ERROR);
            }
        }
    }

    res = tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    return (LX_SUCCESS);
}


static UINT lx_nand_driver_page_erased_verify(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    ULONG block_offset;
    uint32_t page_num;
    int32_t ret;
    UINT res;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    block_offset = p_nand_driver->offset / p_attrs->blockSize;
    page_num = (block_offset + block) * p_attrs->pageCount + page;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    ret = Flash_readPage(p_nand_driver->flash_handle, page_num, 0u, &gt_page_buf[0], p_attrs->pageSize + p_attrs->spareAreaSize);
    if (ret != SystemP_SUCCESS) {
        (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
        DebugP_logError("Flash_readPage() failed with %u.\n", ret);
        return (LX_ERROR);
    }

    for (size_t k = 0u; k < (p_attrs->pageSize + p_attrs->spareAreaSize) / 4u; k++) {
        if (((uint32_t *)gt_page_buf)[k] != 0xFFFFFFFF) {
            (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
            DebugP_logError("lx_nand_driver_page_erased_verify() verification failed.\n");
            return (LX_ERROR);
        }
    }

    res = tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    return (LX_SUCCESS);
}


static UINT lx_nand_driver_block_status_get(LX_NAND_FLASH *nand_flash, ULONG block, UCHAR *bad_block_byte)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    ULONG page_num;
    ULONG first_block;
    int32_t ret;
    UINT res;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    first_block = p_nand_driver->offset / p_attrs->blockSize;
    page_num = (first_block + block) * p_attrs->pageCount;
    ret = Flash_readPage(p_nand_driver->flash_handle, page_num, p_attrs->pageSize, (uint8_t *)&gt_page_buf[0], 1u);
    if (ret != SystemP_SUCCESS) {
        (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
        DebugP_logError("Flash_readPage() failed with %u.\n", ret);
        return (LX_ERROR);
    }

    *bad_block_byte = gt_page_buf[0];

    if (ret != SystemP_SUCCESS) {
        (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
        return (LX_ERROR);
    }

    /* Return success.  */
    return (LX_SUCCESS);
}


static UINT lx_nand_driver_block_status_set(LX_NAND_FLASH *nand_flash, ULONG block, UCHAR bad_block_byte)
{
    lx_nand_driver_t *p_nand_driver;
    Flash_Attrs *p_attrs;
    ULONG page_num;
    ULONG first_block;
    int32_t ret;
    UINT res;

    p_nand_driver = lx_nand_driver_get(nand_flash);
    p_attrs = p_nand_driver->p_attrs;

    res = tx_mutex_get(&g_nand_driver_data.page_buf_mutex, TX_WAIT_FOREVER);
    if (res != TX_SUCCESS) {
        return (LX_ERROR);
    }

    memset(&gt_page_buf[0], 0xFF, p_attrs->pageSize + p_attrs->spareAreaSize);
    gt_page_buf[p_attrs->pageSize] = bad_block_byte;

    first_block = p_nand_driver->offset / p_attrs->blockSize;
    page_num = (first_block + block) * p_attrs->pageCount;
    ret = Flash_writePage(p_nand_driver->flash_handle, page_num, &gt_page_buf[0], p_attrs->pageSize + p_attrs->spareAreaSize);
    if (ret != SystemP_SUCCESS) {
        (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
        DebugP_logError("Flash_writePage() failed with %u.\n", ret);
        return (LX_ERROR);
    }

    if (ret != SystemP_SUCCESS) {
        (void)tx_mutex_put(&g_nand_driver_data.page_buf_mutex);
        return (LX_ERROR);
    }

    /* Return success.  */
    return (LX_SUCCESS);
}


/* Not used by LevelX. */
static UINT lx_nand_driver_extra_bytes_get(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR *destination, UINT size)
{
    (void)nand_flash;
    (void)block;
    (void)page;
    (void)destination;
    (void)size;

    DebugP_assert(0);
    return (LX_ERROR);
}

/* Not used by LevelX. */
static UINT lx_nand_driver_extra_bytes_set(LX_NAND_FLASH *nand_flash, ULONG block, ULONG page, UCHAR *source, UINT size)
{
    (void)nand_flash;
    (void)block;
    (void)page;
    (void)source;
    (void)size;

    DebugP_assert(0);
    return (LX_ERROR);
}


static UINT lx_nand_driver_system_error(LX_NAND_FLASH *nand_flash, UINT error_code, ULONG block, ULONG page)
{
    LX_PARAMETER_NOT_USED(error_code);
    LX_PARAMETER_NOT_USED(block);
    LX_PARAMETER_NOT_USED(page);
#ifdef LX_NAND_ENABLE_CONTROL_BLOCK_FOR_DRIVER_INTERFACE
    LX_PARAMETER_NOT_USED(nand_flash);
#endif

    /* Custom processing goes here...  all errors except for LX_NAND_ERROR_CORRECTED are fatal.  */
    return (LX_ERROR);
}

static lx_nand_driver_t *lx_nand_driver_get(LX_NAND_FLASH *p_nand_flash)
{
    for (size_t k = 0u; k < LX_NAND_DRIVER_MAX_INSTANCE_COUNT; k++) {
        if (g_nand_driver_data.t_instances[k].p_nand_flash == p_nand_flash) {
            return (&g_nand_driver_data.t_instances[k]);
        }
    }
    return (NULL);
}


