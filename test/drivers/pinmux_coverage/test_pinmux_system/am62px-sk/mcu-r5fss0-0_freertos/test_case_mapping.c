 /**
 *  \file test_case_mapping.c
 *
 *  \brief This file contains mapping of test case IDs to test functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "system_test_utils.h"
#include "test_pinmux_system.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
testCase_t gTestCase[] =
{
    {TestPinmux_configMultiplePins, 11252},
    {TestPinmux_configVerifyModeChange, 11253},
    {TestPinmux_configAllSettingsBits, 11254},
    {NULL, 0}
};
