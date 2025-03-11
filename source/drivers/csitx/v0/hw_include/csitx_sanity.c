/**********************************************************************
* Copyright (C) 2012-2019 Cadence Design Systems, Inc.
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**********************************************************************
* WARNING: This file is auto-generated using api-generator utility.
*          api-generator: 13.04.5beed88
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for MIPI CSI Host Controller
**********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10, DRV-4789" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#include <drivers/hw_include/csl_csitx.h>
#include "cps_drv.h"
#include "csitx_structs_if.h"
#include "csitx_sanity.h"

/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_ConfigSF(const CSITX_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct DphyConfig1
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_DphyConfig1SF(const CSITX_DphyConfig1 *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct DphyConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_DphyConfigSF(const CSITX_DphyConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dphyClockMode > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dphyMode > (2U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct DataTypeConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_DataTypeConfigSF(const CSITX_DataTypeConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->lineCountEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lineStartEndEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataType > (63U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->extendedDataType > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->packedEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct VirtualChannelConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_VirtualChannelConfigSF(const CSITX_VirtualChannelConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->frameCountEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct WaitBurstTimeConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_WaitBurstTimeConfigSF(const CSITX_WaitBurstTimeConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct StreamConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_StreamConfigSF(const CSITX_StreamConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->slaveMode > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct RxCompatibilityConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_RxCompatibilityConfigSF(const CSITX_RxCompatibilityConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct EpdConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_EpdConfigSF(const CSITX_EpdConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->enable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->option > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->spSpacers > (0x3FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpSpacers > (0x3FFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct Callbacks
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_CallbacksSF(const CSITX_Callbacks *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct PrivateData
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSITX_PrivateDataSF(const CSITX_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config "Driver/hardware configuration required."
 * @param[out] memReq "Size of the memory allocation required."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction1(const CSITX_Config* config, const CSITX_SysReq* memReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (memReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver state info specific to this instance."
 * @param[in] config "Specifies driver/hardware configuration."
 * @param[in] callbacks "Client-supplied callback functions."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction2(const CSITX_PrivateData* pD, const CSITX_Config* config, const CSITX_Callbacks* callbacks)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_CallbacksSF(callbacks) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data filled by Init."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction3(const CSITX_PrivateData* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] enable "'configuration_request' bit from the CONFIG register is tested. If enable Configuration Request is enabled, false otherwise."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction8(const CSITX_PrivateData* pD, const uint32_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config "Configuration to apply to D-PHY."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction9(const CSITX_PrivateData* pD, const CSITX_DphyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_DphyConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY config."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction10(const CSITX_PrivateData* pD, const CSITX_DphyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config "Configuration to apply to DPHY CFG1."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction11(const CSITX_PrivateData* pD, const CSITX_DphyConfig1* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_DphyConfig1SF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY CFG1 config."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction12(const CSITX_PrivateData* pD, const CSITX_DphyConfig1* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config "Virtual channel configuration."
 * @param[in] number Number of the Virtual channel to configure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction13(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, const CSITX_VcNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_VirtualChannelConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_VC0) &&
        (number != CSITX_VC1) &&
        (number != CSITX_VC2) &&
        (number != CSITX_VC3) &&
        (number != CSITX_VC4) &&
        (number != CSITX_VC5) &&
        (number != CSITX_VC6) &&
        (number != CSITX_VC7) &&
        (number != CSITX_VC8) &&
        (number != CSITX_VC9) &&
        (number != CSITX_VC10) &&
        (number != CSITX_VC11) &&
        (number != CSITX_VC12) &&
        (number != CSITX_VC13) &&
        (number != CSITX_VC14) &&
        (number != CSITX_VC15)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "Virtual channel configuration."
 * @param[in] number Number of the virtual channel
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction14(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, const CSITX_VcNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_VC0) &&
        (number != CSITX_VC1) &&
        (number != CSITX_VC2) &&
        (number != CSITX_VC3) &&
        (number != CSITX_VC4) &&
        (number != CSITX_VC5) &&
        (number != CSITX_VC6) &&
        (number != CSITX_VC7) &&
        (number != CSITX_VC8) &&
        (number != CSITX_VC9) &&
        (number != CSITX_VC10) &&
        (number != CSITX_VC11) &&
        (number != CSITX_VC12) &&
        (number != CSITX_VC13) &&
        (number != CSITX_VC14) &&
        (number != CSITX_VC15)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config "Data type configuration."
 * @param[in] number Number of the Data type to configure.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction15(const CSITX_PrivateData* pD, const CSITX_DataTypeConfig* config, const CSITX_DtNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_DataTypeConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_DT0) &&
        (number != CSITX_DT1) &&
        (number != CSITX_DT2) &&
        (number != CSITX_DT3) &&
        (number != CSITX_DT4) &&
        (number != CSITX_DT5) &&
        (number != CSITX_DT6) &&
        (number != CSITX_DT7) &&
        (number != CSITX_DT8) &&
        (number != CSITX_DT9) &&
        (number != CSITX_DT10) &&
        (number != CSITX_DT11) &&
        (number != CSITX_DT12) &&
        (number != CSITX_DT13) &&
        (number != CSITX_DT14) &&
        (number != CSITX_DT15)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "Data type configuration."
 * @param[in] number Number of the data type
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction16(const CSITX_PrivateData* pD, const CSITX_DataTypeConfig* config, const CSITX_DtNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_DT0) &&
        (number != CSITX_DT1) &&
        (number != CSITX_DT2) &&
        (number != CSITX_DT3) &&
        (number != CSITX_DT4) &&
        (number != CSITX_DT5) &&
        (number != CSITX_DT6) &&
        (number != CSITX_DT7) &&
        (number != CSITX_DT8) &&
        (number != CSITX_DT9) &&
        (number != CSITX_DT10) &&
        (number != CSITX_DT11) &&
        (number != CSITX_DT12) &&
        (number != CSITX_DT13) &&
        (number != CSITX_DT14) &&
        (number != CSITX_DT15)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config "Stream configuration."
 * @param[in] number Pixel interface number.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction17(const CSITX_PrivateData* pD, const CSITX_StreamConfig* config, const CSITX_IfNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_StreamConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_PIXEL_IF0) &&
        (number != CSITX_PIXEL_IF1) &&
        (number != CSITX_PIXEL_IF2) &&
        (number != CSITX_PIXEL_IF3)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "Stream configuration."
 * @param[in] number Pixel interface number.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction18(const CSITX_PrivateData* pD, const CSITX_StreamConfig* config, const CSITX_IfNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_PIXEL_IF0) &&
        (number != CSITX_PIXEL_IF1) &&
        (number != CSITX_PIXEL_IF2) &&
        (number != CSITX_PIXEL_IF3)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] enable "'bypass_mode_enable' bit from the CONFIG register is tested. If enable Bypass Mode Enable is enabled, false otherwise."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction20(const CSITX_PrivateData* pD, const bool* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config DPHY Wait Time Configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction27(const CSITX_PrivateData* pD, const CSITX_WaitBurstTimeConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_WaitBurstTimeConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY Wait Time Configuration."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction28(const CSITX_PrivateData* pD, const CSITX_WaitBurstTimeConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DPHY_CLK_WAKEUP register."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction30(const CSITX_PrivateData* pD, const uint16_t* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DEBUG_PROT_FSM register."
 * @param[in] number Number of the Pixel interface.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction35(const CSITX_PrivateData* pD, const uint32_t* value, const CSITX_IfNumber number)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (number != CSITX_PIXEL_IF0) &&
        (number != CSITX_PIXEL_IF1) &&
        (number != CSITX_PIXEL_IF2) &&
        (number != CSITX_PIXEL_IF3)
        )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] value "D-PHY config."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction40(const CSITX_PrivateData* pD, const uint16_t* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction42(const CSITX_PrivateData* pD, const CSITX_AsfInfo* asfInfo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (asfInfo == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Pointer to the private data initialized by init".
 * @param[out] value "Output value."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction43(const CSITX_PrivateData* pD, const CSITX_DeviceConfig* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[in] config EPD configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction44(const CSITX_PrivateData* pD, const CSITX_EpdConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_EpdConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD "Driver instance data."
 * @param[out] config EPD configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction45(const CSITX_PrivateData* pD, const CSITX_EpdConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver instance data
 * @param[in] config CSIRX compatibility configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction48(const CSITX_PrivateData* pD, const CSITX_RxCompatibilityConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_RxCompatibilityConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver instance data
 * @param[out] config CSIRX compatibility configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSITX_SanityFunction49(const CSITX_PrivateData* pD, const CSITX_RxCompatibilityConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
