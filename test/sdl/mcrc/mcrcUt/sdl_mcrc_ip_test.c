 /* Copyright (c) 2021 Texas Instruments Incorporated
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
 *
 */

 /**
 *  \file     sdl_mcrc_ip_test.c
 *
 *  \brief    This file contains mcrc ip functionality test code.
 *
 *  \details  mcrc unit tests
 **/

#include "mcrc_main.h"

int32_t sdl_ip_mcrcNegTest(void)
{
    int32_t               testStatus = SDL_APP_TEST_PASS;
    SDL_MCRC_InstType     instance = MCRC_MCU_NAVSS;
    uint32_t              baseAddr;
    uint32_t              ctrlFlag = 1U;
    SDL_MCRC_DataBusMask_t dataBusMask = SDL_MCRC_DATA_BUS_MASK_ALL;
    SDL_MCRC_DataBusMask_t busEnableMask = SDL_MCRC_DATA_BUS_MASK_ALL;
    uint32_t pIntVecAddr;

    /*  */

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_getBaseaddr(SDL_MCRC_INVALID, &baseAddr)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        instance = MCRC_MCU_NAVSS;
        if (SDL_MCRC_getBaseaddr(instance, NULL)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_dataBusTracingCtrl(SDL_MCRC_INVALID, ctrlFlag, dataBusMask, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_dataBusTracingCtrl(instance, 2U, dataBusMask, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_dataBusTracingCtrl(instance, 1U, dataBusMask, 255U)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_dataBusTracingCtrl(instance, 1U, 255U, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(SDL_MCRC_INVALID, ctrlFlag, dataBusMask, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(SDL_MCRC_INVALID, SDL_MCRC_MAX_CTRL_FLAG_VAL+1U, dataBusMask, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(instance, SDL_MCRC_MAX_CTRL_FLAG_VAL+1U, 0U, 0U)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(SDL_MCRC_INVALID, SDL_MCRC_MAX_CTRL_FLAG_VAL+1U, 0U, 0U)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 2U, dataBusMask, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 1U, dataBusMask, 255U)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 1U, 255U, busEnableMask)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_getHighestPriorityIntrStatus(SDL_MCRC_INVALID, &pIntVecAddr)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
            
    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_MCRC_dataBusTracingCtrl(instance, 1U, dataBusMask, busEnableMask);
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 0U, dataBusMask, busEnableMask)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_MCRC_dataBusTracingCtrl(instance, 1U, dataBusMask, busEnableMask);
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 1U, dataBusMask, SDL_MCRC_MCRC_BUS_SEL_MEN_MASK)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_MCRC_dataBusTracingCtrl(instance, 1U, dataBusMask, busEnableMask);
        if (SDL_MCRC_verifyBusTracingCtrl(instance, 1U, dataBusMask, SDL_MCRC_MCRC_BUS_SEL_MEN_MASK)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
    
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_MCRC_getHighestPriorityIntrStatus(instance, NULL)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        DebugP_log("SDLmcrc_IP_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
     
    return (testStatus);
}

/*****************************************************************************/
int32_t sdl_ip_mcrcPosTest(void)
{
    int32_t               testStatus = SDL_APP_TEST_PASS;
    SDL_MCRC_InstType     instance;
    uint32_t              baseAddr;
    uint32_t              ctrlFlag= 1U;
    SDL_MCRC_DataBusMask_t dataBusMask = SDL_MCRC_DATA_BUS_MASK_ALL;
    SDL_MCRC_DataBusMask_t busEnableMask = SDL_MCRC_DATA_BUS_MASK_ALL;
    uint32_t pIntVecAddr;

    /*  */
    for (instance = MCRC_MCU_NAVSS; instance <= MCRC_MCU_NAVSS; instance++)
    {
        if (testStatus == SDL_APP_TEST_PASS)
        {
            if (SDL_MCRC_getBaseaddr(instance, &baseAddr)!= SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
            }
        }
    
        if (testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
        
        if (testStatus == SDL_APP_TEST_PASS)
        {
            if (SDL_MCRC_dataBusTracingCtrl(instance, ctrlFlag, dataBusMask, busEnableMask)!= SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
            }
        }
    
        if (testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
        
        if (testStatus == SDL_APP_TEST_PASS)
        {
            SDL_MCRC_dataBusTracingCtrl(instance, 1U, 1U, 1U);
            if (SDL_MCRC_verifyBusTracingCtrl(instance, 1U, 1U, 1U)!= SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
            }
        }
        if (testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
        
        if (testStatus == SDL_APP_TEST_PASS)
        {
            if (SDL_MCRC_verifyBusTracingCtrl(instance, ctrlFlag, dataBusMask, busEnableMask)!= SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
            }
        }
        
        if (testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
        
        if (testStatus == SDL_APP_TEST_PASS)
        {
            if (SDL_MCRC_getHighestPriorityIntrStatus(instance, &pIntVecAddr)!= SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
            }
        }
    
        if (testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("SDL _mcrc_IP_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    return (testStatus);
}

