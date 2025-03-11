/*
 *  Copyright (c) Texas Instruments Incorporated 2022-25
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
 *  \file serdes_sensor_config.c
 *
 *  \brief Serializer, Deserializer and sensor configuration APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include "serdes_sensor_config.h"

extern void App_wait(uint32_t wait_in_ms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint16_t gSensorCfg[SENSOR_CFG_SIZE][3] = IMX390_LINEAR_1920X1080_CONFIG;

uint16_t gUb960SensorCfg[][3] = {
    {0x01, 0x02, 0x100},
    {0x1F, 0x00, 0x1},

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
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

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
    {0x65, (D3IMX390_UB960_INST0_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_INST0_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x00,0x1}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x12, 0x1}, /* 0x12 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_INST0_PORT_1_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_INST0_PORT_1_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x55,0x1}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x24, 0x1}, /* 0x24 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_INST0_PORT_2_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_INST0_PORT_2_SENSOR_ADDR << 1U), 0x1},
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
    {0x65, (D3IMX390_UB960_INST0_PORT_3_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_INST0_PORT_3_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xFF,0x1}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x100},
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
    {0x07, 0x28, 0x1F},
    {0x0D, 0x01, 0x10},

    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x80},
};

uint32_t gUb953I2CAddrInst0[APP_CH_MAX] =
{
    D3IMX390_UB960_INST0_PORT_0_SER_ADDR,
    D3IMX390_UB960_INST0_PORT_1_SER_ADDR,
    D3IMX390_UB960_INST0_PORT_2_SER_ADDR,
    D3IMX390_UB960_INST0_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddrInst0[APP_CH_MAX] =
{
    D3IMX390_UB960_INST0_PORT_0_SENSOR_ADDR,
    D3IMX390_UB960_INST0_PORT_1_SENSOR_ADDR,
    D3IMX390_UB960_INST0_PORT_2_SENSOR_ADDR,
    D3IMX390_UB960_INST0_PORT_3_SENSOR_ADDR
};
uint32_t gUb953I2CAddrInst1[APP_CH_MAX] =
{
    D3IMX390_UB960_INST1_PORT_0_SER_ADDR,
    D3IMX390_UB960_INST1_PORT_1_SER_ADDR,
    D3IMX390_UB960_INST1_PORT_2_SER_ADDR,
    D3IMX390_UB960_INST1_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddrInst1[APP_CH_MAX] =
{
    D3IMX390_UB960_INST1_PORT_0_SENSOR_ADDR,
    D3IMX390_UB960_INST1_PORT_1_SENSOR_ADDR,
    D3IMX390_UB960_INST1_PORT_2_SENSOR_ADDR,
    D3IMX390_UB960_INST1_PORT_3_SENSOR_ADDR
};

/* I2c Handle to access deserializer */
I2C_Handle gI2cHandle;
bool gI2cInstOpened = BFALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t CsirxApp_sensorConfig(CsiLoopback_RxInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t timeOut = 0;
    int32_t status;
    uint32_t cnt, sensorIdx;
    uint8_t i2cInst = 0U, i2cAddr = 0U, regAddr8, regVal;
    uint16_t regAddr;
    uint32_t *ub953I2cAddr, portNum = 0U;
    uint32_t *sensorI2cAddr;
    uint8_t i2cswitchreg;

    Board_enableCSII2c(BOARD_CSI_I2C_MUX_INSTANCE);
    i2cswitchreg = 0x03;
    gI2cHandle = I2C_getHandle(BOARD_CSI_I2C_SWITCH_INSTANCE);
    Board_i2c8BitRegWrSingle(gI2cHandle, 0x70,&i2cswitchreg,0x20);
    Board_fpdUb960GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);

    if(CSIRX_INSTANCE_ID_0 == appInstObj->instId)
    {
        ub953I2cAddr = gUb953I2CAddrInst0;
        sensorI2cAddr = gSensorI2CAddrInst0;
    }
    else if(CSIRX_INSTANCE_ID_1 == appInstObj->instId)
    {
        ub953I2cAddr = gUb953I2CAddrInst1;
        sensorI2cAddr = gSensorI2CAddrInst1;
    }
    if ((0U == i2cInst) && (0U == i2cAddr))
    {
        retVal = FVID2_EFAIL;
    }
    else
    {
        for (cnt = 0U;
             cnt < sizeof(gUb960SensorCfg)/(sizeof(gUb960SensorCfg[0]));
             cnt ++)
        {
            regAddr8 = gUb960SensorCfg[cnt][0] & 0xFF;
            if(0x5E == regAddr8) // Can we change the value with macro D3IMX390_INST2_PORT_3_SENSOR_ADDR and in structutue array gUb960SensorCfg
            {
                if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_CM_MODULE) << 1) & 0xFF ;
                }
                else if (D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_RCM_MODULE) << 1) & 0xFF ;
                }
            }
            else if(0x65 == regAddr8)
            {
                regVal = ((ub953I2cAddr[portNum]) << 1) & 0xFF ;
            }
            else if(0x66 == regAddr8)
            {
                regVal = ((sensorI2cAddr[portNum]) << 1) & 0xFF ;
                portNum++;
            }
            else
            {
                regVal = gUb960SensorCfg[cnt][1] & 0xFF;
            }
            timeOut = gUb960SensorCfg[cnt][2];
            status = Board_i2c8BitRegWr(gI2cHandle, i2cAddr, regAddr8, &regVal, 1,
                                     APP_I2C_TRANSACTION_TIMEOUT);
            if (0 != status)
            {
                GT_3trace(AppTrace,
                          GT_INFO,
                          APP_NAME ": Failed to Set UB960 register %x: Value:%x\n instance %d\n",
                          gUb960SensorCfg[cnt][0],
                          gUb960SensorCfg[cnt][1],
                          appInstObj->instId
                         );
                break;
            }
            else
            {
                App_wait(timeOut);
            }
        }

        for (sensorIdx = 0U ; sensorIdx < APP_CH_NUM ; sensorIdx++)
        {
            if (0 == status)
            {
                /* UB960 Port configuration */
                i2cAddr = ub953I2cAddr[sensorIdx];
                for (cnt = 0U;
                     cnt < sizeof(gUb953SensorCfg)/(sizeof(gUb953SensorCfg[0]));
                     cnt ++)
                {
                    regAddr8 = gUb953SensorCfg[cnt][0] & 0xFF;
                    if(0x07 == regAddr8)
                    {
                        if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal = 0x28;
                            timeOut = 0x1F;
                        }
                        else if (D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal =  0x25;
                            timeOut = 0x80;
                        }
                   }
                   else if(0x0D == regAddr8)
                   {
                       if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                       {
                            regVal =  0x01;
                            timeOut = 0x10;
                       }
                       else if (D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                       {
                            regVal =  0x03;
                            timeOut = 0x10;
                       }
                   }
                   else
                   {
                        regVal = gUb953SensorCfg[cnt][1] & 0xFF;
                        timeOut = gUb953SensorCfg[cnt][2];
                   }
                   status = Board_i2c8BitRegWr(gI2cHandle,
                                              i2cAddr,
                                              regAddr8,
                                              &regVal,
                                              1,
                                              APP_I2C_TRANSACTION_TIMEOUT);

                   if (0 != status)
                   {
                       GT_3trace(AppTrace, GT_INFO,
                                 APP_NAME
                                 ": Failed to Set UB953 register %x: Value:%x for CSIRX instance %d\n",
                                 gUb953SensorCfg[cnt][0],
                                 gUb953SensorCfg[cnt][1],
                                 appInstObj->instId);
                      break;
                   }
                   else
                   {
                       App_wait(timeOut);
                   }
                }
             }
             else
             {
                 break;
             }
         }

         if (0 == status)
         {
              GT_1trace(AppTrace, GT_INFO,
                        APP_NAME ": Configuring IMX390 Sensor for CSIRX instance %d\r\n",appInstObj->instId);
         }
         for (sensorIdx = 0U ; sensorIdx < APP_CH_NUM ; sensorIdx++)
         {
             if (0 == status)
             {
                  /* Sensor 0 configuration */
                  i2cAddr = sensorI2cAddr[sensorIdx];
                  for (cnt = 0U; cnt < SENSOR_CFG_SIZE; cnt ++)
                  {
                      regAddr = gSensorCfg[cnt][0];
                      regVal = gSensorCfg[cnt][1];

                      status = Board_i2c16BitRegWr(gI2cHandle,
                                                   i2cAddr,
                                                   regAddr,
                                                   &regVal,
                                                   1,
                                                   0,
                                                   APP_I2C_TRANSACTION_TIMEOUT);
                      if (0 != status)
                      {
                          GT_3trace(AppTrace, GT_INFO,
                                    APP_NAME
                                    ": Failed to Set Sensor register %x: Value:0x%x for CSIRX instance %d\n",
                                    regAddr,
                                    regVal,
                                    appInstObj->instId);
                          break;
                      }
                  }
              }
              else
              {
                  break;
              }
         }
         if (0 == status)
         {
               Board_fpdUb960GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
               if (CSIRX_INSTANCE_ID_1 == appInstObj->instId)
               {
                   i2cAddr = 0x36U;
               }
               regAddr8 = 0x33;
               regVal = 0x3;
               status = Board_i2c8BitRegWr(gI2cHandle,
                                           i2cAddr,
                                           regAddr8,
                                           &regVal,
                                           1,
                                           APP_I2C_TRANSACTION_TIMEOUT);

               if (0 != status)
               {
                   GT_1trace(AppTrace, GT_INFO,
                             APP_NAME ": Failed to enable CSI port for CSIRX instance %d\n", appInstObj->instId);
               }
               else
               {
                   GT_1trace(AppTrace, GT_INFO,
                             APP_NAME ": Sensor Configuration done for CSIRX instance %d!!!\r\n",appInstObj->instId);
               }
         }
         else
         {
                GT_1trace(AppTrace, GT_INFO,
                          APP_NAME ": Sensor Configuration Failed for CSIRX instance %d!!!\r\n",appInstObj->instId);
         }
    }

    return (retVal);
}



