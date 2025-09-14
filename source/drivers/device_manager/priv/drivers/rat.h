/*
 * DMSC firmware
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RAT_H
#define RAT_H

#include <config.h>
#include <types/short_types.h>
#include <types/errno.h>

/**
 * \brief Allow limited mapping scheme using a spare memory window we can use
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr - SoC physical address we want to map back in. MUST be 512MB
 *	aligned. must check against RAT_TMP_REGION_INVAL_ADDR_MASK
 *	The provided address also acts as a "cookie" or identifier when freeing
 *	the map.
 * \param mapped_addr - if all is valid, returns a mapped address back
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */
static inline s32 rat_map_tmp_region(u64 addr __attribute__((unused)), u32 *mapped_addr __attribute__((unused)))
{
	return SUCCESS;
}

/**
 * \brief Allow limited mapping scheme using a spare memory window we can use
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr - SoC physical address we want to map back in. MUST be 512MB
 *	aligned. must check against RAT_TMP_REGION_INVAL_ADDR_MASK
 *	The provided address also acts as a "cookie" or identifier when freeing
 *	the map.
 * \param mapped_addr - if all is valid, returns a mapped address back
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */

static inline s32 rat_map_tmp_region_user(u64 addr __attribute__((unused)), u32 *mapped_addr __attribute__((unused)))
{
	return SUCCESS;
}

/**
 * \brief Free and disable a mapping done by rat_map_tmp_region
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr provide the exact address parameter provided to rat_map_tmp_region
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */
static inline s32 rat_unmap_tmp_region(u64 addr __attribute__((unused)))
{
	return SUCCESS;
}


/**
 * \brief Free and disable a mapping done by rat_map_tmp_region
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr provide the exact address parameter provided to rat_map_tmp_region
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */
static inline s32 rat_unmap_tmp_region_user(u64 addr __attribute__((unused)))
{
	return SUCCESS;
}

/**
 * \brief Get the tmp rat mapped address range of the low and high address
 *
 * \param lowAddr Lower address value of the TMP mapped region
 * \param highAddr Higher address region of the TMP mapped region
 * \return SUCCESS if the values are populated correctly.
 *         -EBUSY  if the TMP mapped address is not used.
 */
static inline s32 rat_get_free_map_addr_range(u64 *lowAddr  __attribute__((unused)),
	 u64 *highAddr __attribute__((unused)))
{
	return SUCCESS;
}

/**
 * \brief Get the tmp rat mapped address range of the low and high address
 *
 * \param lowAddr Lower address value of the TMP mapped region
 * \param highAddr Higher address region of the TMP mapped region
 * \return SUCCESS if the values are populated correctly.
 *         -EBUSY  if the TMP mapped address is not used.
 */
static inline s32 rat_get_free_map_addr_range_user(u64 *lowAddr  __attribute__((unused)),
	 u64 *highAddr __attribute__((unused)))
{
	return SUCCESS;
}

#define RAT_TMP_REGION_INVAL_ADDR_MASK  (0x1FFFFFFFU)

#endif
