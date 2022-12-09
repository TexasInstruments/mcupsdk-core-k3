#!/bin/bash

##
# RM_PM_HAL
#
# Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
#
# This software is licensed under the  standard terms and conditions in the
# Texas Instruments  Incorporated Technology and Software Publicly Available
# Software License Agreement, a copy of which is included in the software
# download.
##

export RM_PM_HAL_PATH=src/rm_pm_hal

year=$(date +%Y)
month=$(date +%m)

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
	pushd . > /dev/null
	cd $RM_PM_HAL_PATH
	git_ver=$("$git_cmd" describe --abbrev=5 --dirty | sed -e 's/-dirty$/+/g')
	popd > /dev/null
	if [ -n "$git_ver" ]; then
		git_ver="${git_ver}"
	fi
else
	git_ver=""
fi

# Override git version if an explicit non-empty RMPMHAL_SCMVERSION is specified
RMPMHAL_SCMVERSION=${1}
if [ -n "$RMPMHAL_SCMVERSION" ]; then
    git_ver="${RMPMHAL_SCMVERSION}"
fi

cat << EOF
/**
 * RM_PM_HAL Version Info
 *
 * Copyright (C) $year Texas Instruments Incorporated - http://www.ti.com/
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

#define RMPMHAL_SCMVERSION	"$git_ver"

#endif /* INCLUDE_RMPMHAL_VERSION_H */

EOF

