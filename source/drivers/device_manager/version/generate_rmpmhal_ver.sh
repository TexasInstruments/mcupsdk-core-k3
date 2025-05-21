#!/bin/bash

##
# RM_PM_HAL
#
# Copyright (C) 2021-2025 Texas Instruments Incorporated - http://www.ti.com/
#
# This software is licensed under the  standard terms and conditions in the
# Texas Instruments  Incorporated Technology and Software Publicly Available
# Software License Agreement, a copy of which is included in the software
# download.
##

export RM_PM_HAL_PATH=../rm_pm_hal/rm_pm_hal_src

year=$(date +%Y)
month=$(date +%m)
rm_pm_hal_ver=""

if [ ! -z "$WIN_GITPATH" ]; then
	git_cmd="$WIN_GITPATH/git.exe"

	if [ ! -x "$git_cmd" ]; then
		echo "WARNING: Git is not at indicated location $git_cmd"
	fi
else
	git_cmd="git"
fi

# Include an SCMVERSION if applicable. Make it short. Abbreviate dirty as +.
if "$git_cmd" rev-parse --is-inside-work-tree 2>/dev/null >/dev/null; then
	pushd $RM_PM_HAL_PATH > /dev/null
	rm_pm_hal_ver="$("$git_cmd" describe --match "v*.*.*" --abbrev=0 --dirty | sed -e 's/-dirty$/+/g')"

	if [ -n "$rm_pm_hal_ver" ]
	then
		major_ver=$(echo $rm_pm_hal_ver | cut -d'.' -f1 | sed -E -e 's/[^0-9.]//g' -e 's/^0*//g')
		sub_ver=$(echo $rm_pm_hal_ver | cut -d'.' -f2 | sed -E -e 's/[^0-9.]//g' -e 's/^0*//g')
		patch_ver=$(echo $rm_pm_hal_ver | cut -d'.' -f3 | sed -E -e 's/[^0-9.]//g' -e 's/^0*//g')
	fi
	popd > /dev/null
fi

if [ ${#rm_pm_hal_ver} -gt 11 ]
then
	rm_pm_hal_dm_ver="${rm_pm_hal_ver:0:11}"
else
	rm_pm_hal_dm_ver="${rm_pm_hal_ver}"
fi

if [ -z "$major_ver" ]
then
	major_ver=0
fi
if [ -z "$sub_ver" ]
then
	sub_ver=0
fi
if [ -z "$patch_ver" ]
then
	patch_ver=0
fi

cat << EOF
/**
 * RM_PM_HAL Version Info
 *
 * Copyright (C) 2024-$year Texas Instruments Incorporated - http://www.ti.com/
 *
 * This software is licensed under the  standard terms and conditions in the
 * Texas Instruments  Incorporated Technology and Software Publicly Available
 * Software License Agreement, a copy of which is included in the software
 * download.
 *
 * NOTICE: This file is auto-generated based on version numbers passed in
 * Makefile. Never edit this file by hand.
 */

#ifndef INCLUDE_RMPMHAL_VERSION_H
#define INCLUDE_RMPMHAL_VERSION_H

#define RMPMHAL_SCMVERSION      "$rm_pm_hal_ver"
#define RMPMHAL_DMVERSION       "$rm_pm_hal_dm_ver"
#define RMPMHAL_MAJORVERSION    $major_ver
#define RMPMHAL_SUBVERSION      $sub_ver
#define RMPMHAL_PATCHVERSION    $patch_ver
#define RMPMHAL_ABIMAJOR        3
#define RMPMHAL_ABIMINOR        0

#endif /* INCLUDE_RMPMHAL_VERSION_H */

EOF

