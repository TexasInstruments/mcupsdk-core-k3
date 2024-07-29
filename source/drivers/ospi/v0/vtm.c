/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

/**
 *  \file vtm.c
 *
 *  \brief File containing VTM Driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "cslr_vtm.h"
#include "vtm.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/ospi.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/cslr_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VTM_TEMPERATURE_SENSOR_CONTINUOUS_MODE_SET                  (0x1U)
#define VTM_TEMPERATURE_SENSOR_CONTINUOUS_MODE_RESET                (0x0U)

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

/**
 *  \brief This array stores temperature values, the register value
 *  read from VTM driver is mapped to the temperature value from the array
 */
const int32_t gPVTPolynomials[] = {
    -41523, -41210, -40898, -40586, -40274, -39963, -39651, -39340,
    -39029, -38718, -38408, -38098, -37788, -37478, -37168, -36859,
    -36550, -36241, -35933, -35624, -35316, -35008, -34701, -34393, -34086,
    -33779, -33472, -33166, -32859, -32553, -32247, -31942, -31636, -31331,
    -31026, -30722, -30417, -30113, -29809, -29505, -29202, -28899, -28596,
    -28293, -27990, -27688, -27386, -27084, -26782, -26481, -26179, -25878,
    -25578, -25277, -24977, -24677, -24377, -24078, -23778, -23479, -23180,
    -22882, -22583, -22285, -21987, -21689, -21392, -21095, -20797, -20501,
    -20204, -19908, -19612, -19316, -19020, -18725, -18430, -18135, -17840,
    -17545, -17251, -16957, -16663, -16370, -16077, -15783, -15491, -15198,
    -14906, -14613, -14321, -14030, -13738, -13447, -13156, -12865, -12575,
    -12284, -11994, -11704, -11415, -11125, -10836, -10547, -10259, -9970,
    -9682, -9394, -9106, -8819, -8531, -8244, -7957, -7671, -7384, -7098, -6812,
    -6527, -6241, -5956, -5671, -5386, -5102, -4817, -4533, -4250, -3966, -3683,
    -3399, -3117, -2834, -2551, -2269, -1987, -1706, -1424, -1143, -862, -581,
    -300, -20, 260, 540, 820, 1099, 1378, 1657, 1936, 2215, 2493, 2771, 3049,
    3326, 3604, 3881, 4158, 4434, 4711, 4987, 5263, 5539, 5814, 6089, 6364,
    6639, 6914, 7188, 7462, 7736, 8010, 8283, 8556, 8829, 9102, 9374, 9647,
    9919, 10191, 10462, 10733, 11005, 11275, 11546, 11816, 12087, 12357, 12626,
    12896, 13165, 13434, 13703, 13971, 14240, 14508, 14776, 15043, 15311, 15578,
    15845, 16111, 16378, 16644, 16910, 17176, 17441, 17707, 17972, 18237, 18501,
    18766, 19030, 19294, 19557, 19821, 20084, 20347, 20610, 20872, 21135, 21397,
    21658, 21920, 22181, 22443, 22703, 22964, 23225, 23485, 23745, 24005, 24264,
    24523, 24782, 25041, 25300, 25558, 25816, 26074, 26332, 26589, 26846, 27103,
    27360, 27617, 27873, 28129, 28385, 28640, 28896, 29151, 29406, 29660, 29915,
    30169, 30423, 30677, 30930, 31183, 31437, 31689, 31942, 32194, 32446, 32698,
    32950, 33201, 33452, 33703, 33954, 34205, 34455, 34705, 34955, 35204, 35454,
    35703, 35952, 36200, 36449, 36697, 36945, 37192, 37440, 37687, 37934, 38181,
    38427, 38674, 38920, 39166, 39411, 39657, 39902, 40147, 40391, 40636, 40880,
    41124, 41368, 41611, 41855, 42098, 42341, 42583, 42826, 43068, 43310, 43551,
    43793, 44034, 44275, 44516, 44756, 44997, 45237, 45477, 45716, 45956, 46195,
    46434, 46672, 46911, 47149, 47387, 47625, 47862, 48100, 48337, 48573, 48810,
    49046, 49282, 49518, 49754, 49989, 50225, 50460, 50694, 50929, 51163, 51397,
    51631, 51865, 52098, 52331, 52564, 52797, 53029, 53261, 53493, 53725, 53956,
    54188, 54419, 54650, 54880, 55110, 55341, 55570, 55800, 56030, 56259, 56488,
    56716, 56945, 57173, 57401, 57629, 57856, 58084, 58311, 58538, 58764, 58991,
    59217, 59443, 59669, 59894, 60119, 60344, 60569, 60794, 61018, 61242, 61466,
    61690, 61913, 62136, 62359, 62582, 62804, 63026, 63249, 63470, 63692, 63913,
    64134, 64355, 64576, 64796, 65016, 65236, 65456, 65675, 65894, 66113, 66332,
    66551, 66769, 66987, 67205, 67423, 67640, 67857, 68074, 68291, 68507, 68723,
    68939, 69155, 69371, 69586, 69801, 70016, 70230, 70445, 70659, 70873, 71086,
    71300, 71513, 71726, 71939, 72151, 72364, 72576, 72787, 72999, 73210, 73422,
    73632, 73843, 74053, 74264, 74474, 74683, 74893, 75102, 75311, 75520, 75729,
    75937, 76145, 76353, 76561, 76768, 76975, 77182, 77389, 77595, 77802, 78008,
    78213, 78419, 78624, 78829, 79034, 79239, 79443, 79647, 79851, 80055, 80259,
    80462, 80665, 80868, 81070, 81273, 81475, 81676, 81878, 82079, 82281, 82482,
    82682, 82883, 83083, 83283, 83483, 83682, 83882, 84081, 84280, 84478, 84677,
    84875, 85073, 85270, 85468, 85665, 85862, 86059, 86255, 86452, 86648, 86844,
    87039, 87234, 87430, 87625, 87819, 88014, 88208, 88402, 88596, 88789, 88982,
    89175, 89368, 89561, 89753, 89945, 90137, 90329, 90520, 90712, 90903, 91093,
    91284, 91474, 91664, 91854, 92044, 92233, 92422, 92611, 92800, 92988, 93176,
    93364, 93552, 93739, 93927, 94114, 94301, 94487, 94673, 94860, 95045, 95231,
    95417, 95602, 95787, 95971, 96156, 96340, 96524, 96708, 96892, 97075, 97258,
    97441, 97624, 97806, 97988, 98170, 98352, 98533, 98714, 98895, 99076, 99257,
    99437, 99617, 99797, 99977, 100156, 100335, 100514, 100693, 100871, 101050,
    101228, 101405, 101583, 101760, 101937, 102114, 102291, 102467, 102643,
    102819, 102995, 103170, 103346, 103521, 103695, 103870, 104044, 104218,
    104392, 104566, 104739, 104912, 105085, 105258, 105430, 105603, 105775,
    105946, 106118, 106289, 106460, 106631, 106802, 106972, 107142, 107312,
    107482, 107651, 107820, 107989, 108158, 108327, 108495, 108663, 108831,
    108998, 109166, 109333, 109500, 109666, 109833, 109999, 110165, 110331,
    110496, 110661, 110827, 110991, 111156, 111320, 111484, 111648, 111812,
    111975, 112139, 112301, 112464, 112627, 112789, 112951, 113113, 113274,
    113436, 113597, 113758, 113918, 114079, 114239, 114399, 114559, 114718,
    114877, 115036, 115195, 115354, 115512, 115670, 115828, 115986, 116143,
    116300, 116457, 116614, 116770, 116926, 117082, 117238, 117394, 117549,
    117704, 117859, 118014, 118168, 118322, 118476, 118630, 118783, 118937,
    119090, 119242, 119395, 119547, 119699, 119851, 120003, 120154, 120305,
    120456, 120607, 120757, 120907, 121057, 121207, 121357, 121506, 121655,
    121804, 121953, 122101, 122249, 122397, 122545, 122692, 122839, 122986,
    123133, 123280, 123426, 123572, 123718, 123863, 124009, 124154, 124299,
    124443, 124588, 124732, 124876, 125020, 125163, 125306, 125449, 125592,
    125735, 125877, 126019, 126161, 126303, 126444, 126585, 126726, 126867,
    127008, 127148, 127288, 127428, 127567, 127707, 127846, 127985, 128123,
    128262, 128400, 128538, 128676, 128813, 128950, 129087, 129224, 129361,
    129497, 129633, 129769, 129905, 130040, 130175, 130310, 130445, 130579,
    130713, 130847, 130981, 131115, 131248, 131381, 131514, 131647, 131779,
    131911, 132043, 132175, 132306, 132438, 132569, 132699, 132830, 132960,
    133090, 133220, 133350, 133479, 133608, 133737, 133866, 133994, 134123,
    134251, 134378, 134506, 134633, 134760, 134887, 135014, 135140, 135266,
    135392, 135518, 135643, 135768, 135893, 136018, 136143, 136267, 136391,
    136515, 136638, 136762, 136885, 137008, 137130, 137253, 137375, 137497,
    137619, 137740, 137862, 137983, 138103, 138224, 138344, 138464, 138584,
    138704, 138823, 138943, 139062, 139180, 139299, 139417, 139535, 139653,
    139770, 139888, 140005, 140122, 140238, 140355, 140471, 140587, 140703,
    140818, 140933, 141048, 141163, 141278, 141392, 141506, 141620, 141734,
    141847, 141960, 142073, 142186, 142298, 142411, 142523, 142634, 142746,
    142857, 142968, 143079, 143190, 143300, 143410, 143520, 143630, 143740,
    143849, 143958, 144067, 144175, 144283, 144391, 144499, 144607, 144714,
    144821, 144928, 145035, 145142, 145248, 145354, 145459, 145565, 145670,
    145775, 145880, 145985, 146089, 146193, 146297, 146401, 146504, 146608,
    146711, 146813, 146916, 147018, 147120, 147222, 147324, 147425, 147526,
    147627, 147728, 147828, 147928, 148028, 148128, 148228, 148327, 148426,
    148525, 148623, 148722, 148820, 148918, 149015, 149113, 149210, 149307,
    149404, 149500, 149596, 149692, 149788, 149884, 149979, 150074, 150169, 150264, 150358, 150452,
    150546, 150640, 150733, 150827, 150920, 151013, 151105, 151197, 151290,
    151381, 151473, 151564, 151656, 151747, 151837, 151928, 152018, 152108,
    152198, 152287, 152377, 152466, 152555, 152643, 152732, 152820, 152908,
    152995, 153083, 153170, 153257, 153344, 153430, 153517, 153603, 153689,
    153774, 153860, 153945, 154030, 154114, 154199, 154283, 154367, 154451,
    154534, 154618, 154701, 154784, 154866, 154949, 155031, 155113, 155194,
    155276, 155357, 155438, 155519, 155599, 155680, 155760, 155839, 155919,
    155998, 156078, 156156, 156235, 156314, 156392, 156470, 156547, 156625,
    156702, 156779, 156856, 156933, 157009, 157085, 157161
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Internal functions */
static uint32_t VTM_getBestValue(int32_t code0, int32_t code1, int32_t code2);
static void VTM_setContinousMode(const CSL_vtm_cfg2Regs_TMPSENS *sensorConfig,
                                 uint32_t modeSetVal);
static int32_t VTM_getADCDataOutCode(const CSL_vtm_cfg1Regs_TMPSENS \
                                     *sensorConfig);
static int32_t VTM_getSensorCount(const CSL_vtm_cfg1Regs *config1);
static void VTM_resetSensorSetup(const CSL_vtm_cfg2Regs_TMPSENS *sensorConfig,
                                 uint32_t modeSetVal);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void VTM_printPolynomialLookUpTable()
{
	int32_t iterate;

	DebugP_log("The contents of derived array\n\r");
	DebugP_log("Code   Temperature\n\r");

	for (iterate = 0; iterate < VTM_TABLE_SIZE; iterate++)
    {
		DebugP_log("%d  %d\n\r", iterate, gPVTPolynomials[iterate]);
    }
}

int32_t VTM_getAverageTemperature(float *temperature)
{
    int32_t status = SystemP_SUCCESS;
    int32_t sensorCount;
    int32_t code;
    float avgTemp = 0;
    const CSL_vtm_cfg1Regs *config1;
    const CSL_vtm_cfg2Regs *config2;

    if(temperature != NULL)
    {
        config1 = (CSL_vtm_cfg1Regs *)CSL_WKUP_VTM0_MMR_VBUSP_CFG1_BASE;
        config2 = (CSL_vtm_cfg2Regs *)CSL_WKUP_VTM0_MMR_VBUSP_CFG2_BASE;

        sensorCount = VTM_getSensorCount(config1);

        for(uint32_t count = 0U; count < sensorCount; count++)
        {
            VTM_setContinousMode(&config2->TMPSENS[count], \
                                 VTM_TEMPERATURE_SENSOR_CONTINUOUS_MODE_SET);
            code = VTM_getADCDataOutCode(&config1->TMPSENS[count]);
            avgTemp += gPVTPolynomials[code];
            VTM_resetSensorSetup(&config2->TMPSENS[count], \
                                 VTM_TEMPERATURE_SENSOR_CONTINUOUS_MODE_RESET);
        }

        *temperature = avgTemp / (sensorCount * 1000);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/* ========================================================================== */
/*                       Internal Function Definitions                        */
/* ========================================================================== */

static uint32_t VTM_getBestValue(int32_t code0, int32_t code1, int32_t code2)
{
	int32_t diff01 = abs(code0 - code1);
	int32_t diff02 = abs(code0 - code2);
	int32_t diff12 = abs(code1 - code2);

	if (diff01 <= diff02 && diff01 <= diff12)
    {
        return (code0 + code1) / 2;
    }

	if (diff02 <= diff01 && diff02 <= diff12)
    {
        return (code0 + code2) / 2;
    }

	return (code1 + code2) / 2;

}

static void VTM_resetSensorSetup(const CSL_vtm_cfg2Regs_TMPSENS *sensorConfig,
                                 uint32_t modeSetVal)
{
    if(sensorConfig != NULL)
    {
        CSL_REG32_FINS(&sensorConfig->CTRL, VTM_CFG2_TMPSENS_CTRL_CLRZ, \
                       modeSetVal);
    }
}

static void VTM_setContinousMode(const CSL_vtm_cfg2Regs_TMPSENS *sensorConfig,
                                 uint32_t modeSetVal)
{
    if(sensorConfig != NULL)
    {
        CSL_REG32_FINS(&sensorConfig->CTRL, VTM_CFG2_TMPSENS_CTRL_CONT, \
                       modeSetVal);
    }
}

static int32_t VTM_getADCDataOutCode(const CSL_vtm_cfg1Regs_TMPSENS  \
                                     *sensorConfig)
{
    int32_t tempCode = 0;
    int32_t code0 = 0;
    int32_t code1 = 0;
    int32_t code2 = 0;

    code0 = (int32_t)CSL_REG32_FEXT(&sensorConfig->STAT, \
                     VTM_CFG1_TMPSENS_STAT_DATA_OUT);

    code1 = (int32_t)CSL_REG32_FEXT(&sensorConfig->STAT, \
                     VTM_CFG1_TMPSENS_STAT_DATA_OUT);

    code2 = (int32_t)CSL_REG32_FEXT(&sensorConfig->STAT, \
                     VTM_CFG1_TMPSENS_STAT_DATA_OUT);

    tempCode = VTM_getBestValue(code0, code1, code2);

    return tempCode;
}

static int32_t VTM_getSensorCount(const CSL_vtm_cfg1Regs *config1)
{
    int32_t count = 0U;

    if(config1 != NULL)
    {
        count = (int32_t)CSL_REG32_FEXT(&config1->DEVINFO_PWR0, \
                                        VTM_CFG1_DEVINFO_PWR0_TMPSENS_CT);
    }

    return count;
}
