/*
 *  Copyright (c) 2019-25 Texas Instruments Incorporated
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
 *  \file csirx_sensorCfg.c
 *
 *  \brief Memory allocator API.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "csirx_test.h"
#include "imx390.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * @{
 * Macros to control Fusion board and Camera Sensor version for the capture
 */
/**< Fusion Board Revision.
     '0': for Rev B or older boards.
     '1': for Rev C board. */
#define FUSION_BOARD_VER                     (1U)
/**< D3 IMX390 sensor version.
     '0': for D3_IMX390_CM module.
     '1': for D3_IMX390_RCM module. */
#define D3IMX390_MODULE_VER                  (0U)
/** @} */

#define SENSOR_CFG_SIZE                      (3075)

/**
 * @{
 * I2C Addresses for serialisers/Sensors attached to the UB960
 */
#define UB960_SERIALISER_ADDR                (0x18)
#if (0U == D3IMX390_MODULE_VER)
#define D3IMX390_SENSOR_ADDR                 (0x21)
#endif
#if (1U == D3IMX390_MODULE_VER)
#define D3IMX390_SENSOR_ADDR                 (0x1A)
#endif
/** @} */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SER_ADDR       (0x74U)
#define D3IMX390_UB960_PORT_1_SER_ADDR       (0x76U)
#define D3IMX390_UB960_PORT_2_SER_ADDR       (0x78U)
#define D3IMX390_UB960_PORT_3_SER_ADDR       (0x7AU)
/** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SENSOR_ADDR    (0x40U)
#define D3IMX390_UB960_PORT_1_SENSOR_ADDR    (0x42U)
#define D3IMX390_UB960_PORT_2_SENSOR_ADDR    (0x44U)
#define D3IMX390_UB960_PORT_3_SENSOR_ADDR    (0x46U)
/** @} */

#define  D3IMX390_UB960_DATALANES_4          (0x0U)
#define  D3IMX390_UB960_DATALANES_3          (0x1U)
#define  D3IMX390_UB960_DATALANES_2          (0x2U)
#define  D3IMX390_UB960_DATALANES_1          (0x3U)
#define  D3IMX390_UB960_DATALANE_SHIFT       (0x4U)

/**< Number of channels */
#define APP_CAPT_CH_MAX                      ((uint32_t)4U)

/**< I2C transaction timeout */
#define APP_I2C_TRANSACTION_TIMEOUT          ((uint32_t)2000U)

#define DESERIALIZE_CONFIG_SIZE              (500U)

#define UB960_SR_IND_ACC_ADDR                (0xB1)
#define UB960_SR_IND_ACC_DATA                (0xB2)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t App_sensorConfig(CsirxSensorCfg *senCfg);
extern void App_wait(uint32_t wait_in_ms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern I2C_Handle gI2cHandle;
uint16_t gSensorCfg[SENSOR_CFG_SIZE][3] = IMX390_LINEAR_1920X1080_CONFIG;
uint16_t gUb960SensorCfg[][3] = {
    {0x01, 0x02, 0x100},
    {0x1F, 0x05, 0x1},

    {0xB0, 0x1C,0x1},
    {0xB1, 0x16,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x17,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x18,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x19,0x1},
    {0xB2, 0x00,0x1},
    {0xB0, 0x1C,0x1},
    {0xB1, 0x15,0x1},
    {0xB2, 0x0A,0x1},
    {0xB2, 0x00,0x10},

    {0x0D, 0x90, 0x1}, /*I/O to 3V3 - Options not valid with datashee*/
    {0x0C, 0x0F, 0x1}, /*Enable All ports*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0x58, 0x5E, 0x1},
    {0x72, 0x00, 0x1}, /*VC map*/

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB0, 0x08, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x20, 0x00, 0x1}, /*Forwarding and using CSIport 0 */

    /*Sets GPIOS*/
    {0x10, 0x83, 0x1},
    {0x11, 0xA3, 0x1},
    {0x12, 0xC3, 0x1},
    {0x13, 0xE3, 0x1},

    {0x4C, 0x01, 0x1}, /* 0x01 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x00,0x1}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x1},

    {0x4C, 0x12, 0x1}, /* 0x12 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_1_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_1_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x55,0x1}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x1},

    {0x4C, 0x24, 0x1}, /* 0x24 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_2_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_2_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xAA,0x1}, /*VC Map - All to 2 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x38, 0x1}, /* 0x38 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_3_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_3_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xFF,0x1}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x100},
    {0xFFF,0x00, 0x100},
};

uint16_t gUb960PatternGenCfg[][3]={
    {0x32, 0x01, 0x50},
    {0x1F, 0x05, 0x1},
    {0xC9, 0x32, 0x1},
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x92, 0x1},
    {0xB2, 0x40, 0x1},
    {0xB0, 0x01, 0x1},
    {0xB1, 0x01, 0x1},
    {0xB2, 0x01, 0x1},
    {0xB1, 0x02, 0x1},
    {0xB2, 0xF3, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, FVID2_CSI2_DF_RAW12, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x0F, 0x1},
    {0xB1, 0x05, 0x1},
    {0xB2, 0x00, 0x1},
    {0xB1, 0x06, 0x1},
    {0xB2, 0x02, 0x1},
    {0xB1, 0x07, 0x1},
    {0xB2, 0x80, 0x1},/*D0*/
    {0xB1, 0x08, 0x1},
    {0xB2, 0x04, 0x1},
    {0xB1, 0x09, 0x1},
    {0xB2, 0x38, 0x1},
    {0xB1, 0x0A, 0x1},
    {0xB2, 0x08, 0x1},
    {0xB1, 0x0B, 0x1},
    {0xB2, 0x80, 0x1},
    {0xB1, 0x0C, 0x1},
    {0xB2, 0x04, 0x1},
    {0xB1, 0x0D, 0x1},
    {0xB2, 0x7D, 0x1},
    {0xB1, 0x0E, 0x1},
    {0xB2, 0x07, 0x1},
    {0xB1, 0x0F, 0x1},
    {0xB2, 0x08, 0x1},
    {0x33, 0x02, 0x1},
    {0xFFF,0x00, 0x100},
};
uint16_t gUb953SensorCfg[][3] = {
    {0x01, 0x01, 0x80},
    {0x02, 0x72, 0x10},

#if (0U == FUSION_BOARD_VER)
    {0x06, 0x21, 0x1F},
#elif (1U == FUSION_BOARD_VER)
    {0x06, 0x41, 0x1F},
#else
/* Unsupported version */
#endif

#if (0U == D3IMX390_MODULE_VER)
    {0x07, 0x28, 0x1F},
    {0x0D, 0x01, 0x10},
#elif (1U == D3IMX390_MODULE_VER)
    {0x07, 0x15, 0x80},
    {0x0D, 0x03, 0x10},
#else
/* Unsupported version */
#endif
    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x80},
};

uint32_t gUb953I2CAddr[APP_CAPT_CH_MAX] =
{
    D3IMX390_UB960_PORT_0_SER_ADDR,
    D3IMX390_UB960_PORT_1_SER_ADDR,
    D3IMX390_UB960_PORT_2_SER_ADDR,
    D3IMX390_UB960_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddr[APP_CAPT_CH_MAX] =
{
    D3IMX390_UB960_PORT_0_SENSOR_ADDR,
    D3IMX390_UB960_PORT_1_SENSOR_ADDR,
    D3IMX390_UB960_PORT_2_SENSOR_ADDR,
    D3IMX390_UB960_PORT_3_SENSOR_ADDR
};

/** \brief Log enable for CSIRX Unit Test  application */
extern uint32_t gAppTrace;
extern uint32_t CsirxDrv_getBpp(uint32_t dt);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t ub960IndRegWrite(uint8_t i2cAddr, uint8_t regAddr8, uint8_t regVal)
{
    int32_t status = 0;
    status = Board_i2c8BitRegWr(gI2cHandle,
                                i2cAddr,
                                UB960_SR_IND_ACC_ADDR,
                                &regAddr8,
                                1,
                                APP_I2C_TRANSACTION_TIMEOUT);
    if(0 == status)
    {
            status = Board_i2c8BitRegWr(gI2cHandle,
                                        i2cAddr,
                                        UB960_SR_IND_ACC_DATA,
                                        &regVal,
                                        1,
                                        APP_I2C_TRANSACTION_TIMEOUT);

    }
    return status;
}

int32_t updateFrameWidthPattenGenGen(uint8_t i2cAddr, CsirxSensorCfg *senCfg)
{
    uint8_t regVal;
    int32_t retVal = 0;
    regVal = (senCfg->frameWidth*(CsirxDrv_getBpp(senCfg->dt)/8) & 0xFF00) >> 8 ;
    retVal = ub960IndRegWrite(i2cAddr, 0x4U,regVal);
    if(0 == retVal)
    {
        regVal = (senCfg->frameWidth*(CsirxDrv_getBpp(senCfg->dt)/8) & 0xFF);
        retVal = ub960IndRegWrite(i2cAddr, 0x5U,regVal);
    }
    return retVal;
}

int32_t updateFrameHeightPatternGen(uint32_t i2cAddr, CsirxSensorCfg *senCfg)
{
    uint8_t regVal;
    int32_t retVal = 0;
    regVal = (senCfg->frameHeight & 0xFF00) >> 8;
    retVal = ub960IndRegWrite(i2cAddr, 0x8U,regVal);
    if(0 == retVal)
    {
	    regVal = (senCfg->frameHeight & 0x00FF);
	    retVal = ub960IndRegWrite(i2cAddr, 0x9U,regVal);
    }
    return retVal;
}

int32_t updateFrameDataType(uint32_t i2cAddr, CsirxSensorCfg *senCfg)
{
    uint8_t regVal;
    int32_t retVal = 0;
    regVal = senCfg->dt;
    retVal = ub960IndRegWrite(i2cAddr, 0x3U,regVal);
    return retVal;
}

int32_t App_sensorConfig(CsirxSensorCfg *senCfg)
{
    int32_t retVal = FVID2_SOK;
    int32_t status;
    uint32_t cnt = 0U, sensorIdx,chIterNum = 0U ;
    uint8_t i2cAddr = 0U, regAddr8, regVal;
    uint16_t regAddr;
    int32_t ret = 0;
    uint16_t deSerConfig[DESERIALIZE_CONFIG_SIZE][3] = {};
#if !UB960_USE_PATTERN_GENERATOR
    uint8_t i2cswitchreg;
#endif
    Board_enableCSII2c(BOARD_CSI_I2C_MUX_INSTANCE);
    i2cswitchreg = 0x03;
    gI2cHandle = I2C_getHandle(BOARD_CSI_I2C_SWITCH_INSTANCE);
    Board_i2c8BitRegWrSingle(gI2cHandle, 0x70,&i2cswitchreg,0x20);

    Board_fpdUb960GetI2CAddr(&i2cAddr, 0 );

    if(1U == senCfg->usePatternGen)
    {
        memcpy(deSerConfig, gUb960PatternGenCfg, (sizeof(gUb960PatternGenCfg)));
    }
    else
    {
        memcpy(deSerConfig, gUb960SensorCfg, (sizeof(gUb960SensorCfg)));
    }

    while(0xFFF != deSerConfig[cnt][0])
    {
        regAddr8 = deSerConfig[cnt][0] & 0xFF;
        regVal   = deSerConfig[cnt][1] & 0xFF;
        if(0x72U == regAddr8)
        {
            regVal = senCfg->vcNum[chIterNum];
            chIterNum++;
        }

        status = Board_i2c8BitRegWr(gI2cHandle, i2cAddr, regAddr8, &regVal, 1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (0 != status)
        {
            GT_2trace(gAppTrace,
                      GT_INFO,
                      APP_NAME ": Failed to Set UB960 register %x: Value:%x\n",
                      deSerConfig[cnt][0],
                      deSerConfig[cnt][1]);
            break;
        }
        else
        {
            App_wait(deSerConfig[cnt][2]);
        }
        cnt++;
    }

    if(1 == senCfg->usePatternGen)
    {
         updateFrameWidthPattenGenGen(i2cAddr,senCfg);
         updateFrameHeightPatternGen(i2cAddr,senCfg);
         updateFrameDataType(i2cAddr,senCfg);
    }
    else
    {
        for (sensorIdx = 0U ; sensorIdx < senCfg->numCh ; sensorIdx++)
        {
            if (0 == status)
            {
                /* UB960 Port configuration */
                i2cAddr = gUb953I2CAddr[sensorIdx];
                for (cnt = 0U;
                     cnt < sizeof(gUb953SensorCfg)/(sizeof(gUb953SensorCfg[0]));
                     cnt ++)
                {
                    regAddr8 = gUb953SensorCfg[cnt][0] & 0xFF;
                    regVal   = gUb953SensorCfg[cnt][1] & 0xFF;
                    status = Board_i2c8BitRegWr(gI2cHandle,
                                                i2cAddr,
                                                regAddr8,
                                                &regVal,
                                                1,
                                                APP_I2C_TRANSACTION_TIMEOUT);
                    if (0 != status)
                    {
                        GT_2trace(gAppTrace, GT_INFO,
                                  APP_NAME
                                  ": Failed to Set UB953 register %x: Value:%x\n",
                                  gUb953SensorCfg[cnt][0],
                                  gUb953SensorCfg[cnt][1]);
                        break;
                    }
                    else
                    {
                        App_wait(gUb953SensorCfg[cnt][2]);
                    }
                }
            }
            else
            {
                break;
            }
        }

        for (sensorIdx = 0U ; sensorIdx < senCfg->numCh ; sensorIdx++)
        {
            if (0 == status)
            {
                     /* Sensor 0 configuration */
                 i2cAddr = gSensorI2CAddr[sensorIdx];
                 for (cnt = 0U; cnt < SENSOR_CFG_SIZE; cnt ++)
                 {
                     regAddr = gSensorCfg[cnt][0];
                     regVal = gSensorCfg[cnt][1];

                     status = Board_i2c8BitRegWr(gI2cHandle,
                                                  i2cAddr,
                                                  regAddr,
                                                  &regVal,
                                                  1,
                                                  APP_I2C_TRANSACTION_TIMEOUT);
                     if (0 != status)
                     {
                         GT_2trace(gAppTrace, GT_INFO,
                                   APP_NAME
                                   ": Failed to Set Sensor register %x: Value:0x%x\n",
                                        regAddr,
                                        regVal);
                              break;
                     }
                }
            }
            else
            {
                 break;
            }
        }
    }

    if (0 == status)
    {
        Board_fpdUb960GetI2CAddr(&i2cAddr, 0U);
        regAddr8 = 0x33;
        regVal = 0x3;
        if (4U == senCfg->numDataLanes)
        {
            regVal |= (D3IMX390_UB960_DATALANES_4 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (3U == senCfg->numDataLanes)
        {
            regVal |= (D3IMX390_UB960_DATALANES_3 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (2U == senCfg->numDataLanes)
        {
            regVal |= (D3IMX390_UB960_DATALANES_2 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (1U == senCfg->numDataLanes)
        {
            regVal |= (D3IMX390_UB960_DATALANES_1 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        status = Board_i2c8BitRegWr(gI2cHandle,
                                    i2cAddr,
                                    regAddr8,
                                    &regVal,
                                    1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (0 != status)
        {
            GT_0trace(gAppTrace, GT_INFO,
                      APP_NAME ": Failed to enable CSI port\n");
        }

        if (0 != ret)
        {
            GT_0trace(gAppTrace, GT_INFO,
                      APP_NAME ": ERROR in Sensor Configuration!!!\r\n");
        }

    }
    else
    {
        GT_0trace(gAppTrace, GT_INFO,
                  APP_NAME ": Sensor Configuration Failed!!!\r\n");
    }

    return (retVal);
}

