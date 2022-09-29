/*
 *  Copyright (C) 2018-2022 Texas Instruments Incorporated
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
 *  \file   Osal_wrapper.c
 *
 *  \brief  This file contains the wrapper layer to link OSAL to DPL
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/device_manager/sciclient_direct/Osal_wrapper.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/nortos/dpl/r5/HwiP_armv7r_vim.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <fs/freertos_fat/portable/nortos/task.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/*Linking the starting point as _vectors in MCU+SDK to _freertosvectors in PDK*/
void _vectors(void);
void* _freertosresetvectors = &_vectors;

static int32_t UART_convertVal(uint32_t ulValue, uint32_t ulPos, \
uint32_t ulBase, uint32_t ulNeg, uint32_t ulCount, char cFill, char *pcBuf);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*static objects created for Osal wrapper layer which are returned as part of
API calls */
static HwiP_Object HwObj;
static SemaphoreP_Object SemObject;
static const char *const g_pcHex = "0123456789abcdef";

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*Osal API's mapped to DPL layer for nortos*/
OsalInterruptRetCode_e Osal_DeleteInterrupt(HwiP_Handle handle,\
int32_t corepacEventNum)
{
    OsalInterruptRetCode_e ret=OSAL_INT_SUCCESS;
    HwiP_Object *Obj = (HwiP_Object*)handle;


    (void)HwiP_destruct(Obj);

    return(ret);
}

void Osal_ClearInterrupt(int32_t corepacEvent,int32_t interruptNum)
{
    HwiP_clearInt(interruptNum);
}

void Osal_DisableInterrupt(int32_t corepacEvent,int32_t interruptNum)
{
    (void)HwiP_disableInt(interruptNum);
}

void Osal_EnableInterrupt(int32_t corepacEvent,int32_t interruptNum)
{
    (void)HwiP_enableInt(interruptNum);
}

void CacheP_Inv(const void * addr, int32_t size)
{
    CacheP_inv((void*)addr, size, CacheP_TYPE_ALL);
    return;
}

void OS_StartTickTimer(void)
{
    return;
}

void OS_StopTickTimer(void)
{
    return;
}

void Sciserver_tirtosEnableIntr()
{
    return;
}

void Sciserver_tirtosDisableIntr()
{
    return;
}

Osal_ThreadType Osal_getThreadType(void)
{
    return (Osal_ThreadType_Main);
}

void CSL_armR5CacheWbInv(const void * addr, int32_t size)
{
    CacheP_wbInv((void*)addr,size,CacheP_TYPE_ALL);
    return;
}

void CSL_armR5StartupIntrEnableVic( uint32_t enable )
{
    if (enable == true)
    {
        HwiP_enableVIC();
    }
    else
    {
        HwiP_disableVIC();
    }
}

int32_t Osal_delay(uint32_t nTicks)
{
    uint64_t sec = (ClockP_ticksToUsec(nTicks)) / 1000000;

    ClockP_sleep((uint32_t)sec);

    return 0;
}


uint64_t TimerP_getTimeInUsecs(void)
{
    return ClockP_getTimeUsec();
}

void Osal_RegisterInterrupt_initParams(OsalRegisterIntrParams_t *interruptRegParams)
{
    if(interruptRegParams!=NULL_PTR) {
        /* Corepac config */
        interruptRegParams->corepacConfig.name=(char *) NULL_PTR;
        interruptRegParams->corepacConfig.corepacEventNum=-1;
        interruptRegParams->corepacConfig.intVecNum=-1;
        interruptRegParams->corepacConfig.isrRoutine=(void (*)(uintptr_t arg)) NULL_PTR;;
        interruptRegParams->corepacConfig.arg=(uintptr_t)NULL_PTR;
        interruptRegParams->corepacConfig.priority=0x20U; /* Default */
        interruptRegParams->corepacConfig.enableIntr=TRUE;


        interruptRegParams->corepacConfig.triggerSensitivity = \
        (uint32_t)OSAL_ARM_GIC_TRIG_TYPE_LEVEL; /* interrupt level triggered */

        /* SOC Mux Config */
        interruptRegParams->socMuxConfig.muxInParams=(MuxIntcP_inParams *) NULL_PTR;
        interruptRegParams->socMuxConfig.muxOutParams=(MuxIntcP_outParams *) NULL_PTR;
    }

    return;
}


OsalInterruptRetCode_e Osal_RegisterInterrupt(OsalRegisterIntrParams_t *interruptRegParams, \
HwiP_Handle *hwiPHandlePtr)
{

    OsalInterruptRetCode_e     ret=OSAL_INT_SUCCESS;
    HwiP_Params                hwiInputParams;
    int32_t                    iret;


    /* Program the corepac interrupt */
    if( (interruptRegParams->corepacConfig.isrRoutine == (void (*)(uintptr_t arg)) NULL_PTR) ||
        (interruptRegParams->corepacConfig.corepacEventNum<0)) {
        ret=OSAL_INT_ERR_INVALID_PARAMS;
    }

    HwiP_Params_init(&hwiInputParams);

    hwiInputParams.intNum = interruptRegParams->corepacConfig.intVecNum;
    hwiInputParams.args  = (void*)interruptRegParams->corepacConfig.arg;
    hwiInputParams.priority = interruptRegParams->corepacConfig.priority;
    hwiInputParams.eventId = (uint32_t)interruptRegParams->corepacConfig.corepacEventNum;
    hwiInputParams.callback = (HwiP_FxnCallback)interruptRegParams->corepacConfig.isrRoutine;

    iret =  HwiP_construct(&HwObj,&hwiInputParams);
    if(iret != SystemP_SUCCESS) {
        ret =OSAL_INT_ERR_HWICREATE;
    }

    *hwiPHandlePtr=&HwObj;

    return ret ;
}

SemaphoreP_Handle SemaphoreP_create(uint32_t count,
                                    const SemaphoreP_Params *params)
{
    SemaphoreP_Handle handle = NULL_PTR;

    if(params != NULL_PTR)
    {
        if(params->mode  == SemaphoreP_Mode_BINARY)
        {
            if(SemaphoreP_constructBinary(&SemObject, count) == SystemP_SUCCESS)
            {
                handle = (SemaphoreP_Handle)&SemObject;
            }
        }
        /* counting semaphore needs to be implemented */
    }

    return handle;
}

SemaphoreP_Status SemaphoreP_delete(SemaphoreP_Handle handle)
{
    SemaphoreP_destruct((SemaphoreP_Object *)handle);
    return SemaphoreP_OK;
}


/* Wrapper function for UART-> mapped to CCS logging.*/

static int32_t UART_convertVal(uint32_t ulValue, uint32_t ulPos, uint32_t ulBase, uint32_t ulNeg, uint32_t ulCount, char cFill, char *pcBuf)
{
    uint32_t ulIdx;
    uint32_t count = ulCount;
    uint32_t neg = ulNeg;
    uint32_t pos = ulPos;

    for (ulIdx = 1u;
         (((ulIdx * ulBase) <= ulValue) &&
          (((ulIdx * ulBase) / ulBase) == ulIdx));
         (ulIdx = (ulIdx * ulBase)))
    {
        count--;
    }

    /* If the value is negative, reduce the count of padding
     * characters needed. */
    if (neg != 0U)
    {
        count--;
    }

    /* If the value is negative and the value is padded with
     * zeros, then place the minus sign before the padding. */
    if ((neg != 0U) && ((int8_t)cFill == (int8_t) '0'))
    {
        /* Place the minus sign in the output buffer. */
        pcBuf[pos] = (char) '-';
        pos++;

        /* The minus sign has been placed, so turn off the
         * negative flag. */
        neg = 0;
    }

    /* Provide additional padding at the beginning of the
     * string conversion if needed. */
    if ((count > 1u) && (count < 16u))
    {
        for (count--; count != 0U; count--)
        {
            pcBuf[pos] = cFill;
            pos++;
        }
    }

    /* If the value is negative, then place the minus sign
     * before the number. */
    if (neg != 0U)
    {
        /* Place the minus sign in the output buffer. */
        pcBuf[pos] = (char) '-';
        pos++;
    }

    /* Convert the value into a string. */
    for (; ulIdx != 0U; ulIdx /= ulBase)
    {
        pcBuf[pos] = g_pcHex[(ulValue / ulIdx) % ulBase];
        pos++;
    }

    /* Write the string. */
    (void)UART_dataWrite(pcBuf, pos);

    return 0;
}


#define ENABLE_SYS_FW_LOG   (0u)
void UART_dataWrite(const char* pcBuf, uint32_t u32length)
{
#if (ENABLE_SYS_FW_LOG == 1u)
    uint32_t uIdx;
    /* Send the characters */
    for (uIdx = 0; uIdx < u32length; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if (pcBuf[uIdx] == (char) '\n')
        {
            DebugP_log("\r");
            //UART_putc(((uint8_t)('\r')));
        }

        /* Send the character to the UART output. */
        DebugP_log("%c",pcBuf[uIdx]);
    }
#endif
}

// #define SYSFW_DEBUG_LOG
void UART_printf(const char *pcString, ...)
{
#if defined (SYSFW_DEBUG_LOG)
    uint32_t ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
    char    *pcStr, pcBuf[16], cFill;
    va_list  vaArgP;
    int32_t temp_var = 0;
    const char *pStr = pcString;

    /* Start the varargs processing. */
    (void)va_start(vaArgP, pcString);

    /* Loop while there are more characters in the string. */
    while (*pStr != (char)0U)
    {
        /* Find the first non-% character, or the end of the string. */
        for (ulIdx = 0;
             (pStr[ulIdx] != (char) '%') &&
             (pStr[ulIdx] != (char) '\0');
             ulIdx++)
        {}

        /* Write this portion of the string. */
        (void)UART_dataWrite(pStr, ulIdx);

        /* Skip the portion of the string that was written. */
        pStr += ulIdx;

        /* See if the next character is a %. */
        if (*pStr == (char) '%')
        {
            /* Skip the %. */
            pStr++;

            /* Set the digit count to zero, and the fill character to space
             * (i.e. to the defaults). */
            ulCount = 0;
            cFill   = (char) ' ';

            /* Determine how to handle the next character. */
            while((*pStr >= (char)'0') && (*pStr <= (char)'9'))
            {
                /* If this is a zero, and it is the first digit, then the
                 * fill character is a zero instead of a space. */
                if ((pStr[-1] == (char) '0') && (ulCount == 0U))
                {
                    cFill = (char) '0';
                }

                /* Update the digit count. */
                ulCount *= 10u;
                ulCount += ((uint32_t)(*pStr)) - (uint32_t) '0';

                /* Get the next character. */
                pStr++;
            }
            switch (*pStr)
            {
                /* Handle the %c command. */
                case (char) 'c':
                {
                    /* Get the value from the varargs. */
                    ulValue = (uint32_t)va_arg(vaArgP, uint32_t);

                    /* Print out the character. */
                    (void)UART_dataWrite((const char *) &ulValue, 1u);

                    /* This command has been handled. */
                    break;
                }

                /* Handle the %d command. */
                case (char) 'd':
                {
                    /* Get the value from the varargs. */
                    ulValue = (uint32_t)va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* If the value is negative, make it positive and indicate
                     * that a minus sign is needed. */
                    if ((int32_t) ulValue < 0)
                    {
                        /* Make the value positive. */
                        temp_var = (0 - ((int32_t)ulValue));
                        ulValue = (uint32_t)temp_var;

                        /* Indicate that the value is negative. */
                        ulNeg = 1u;
                    }
                    else
                    {
                        /* Indicate that the value is positive so that a minus
                         * sign isn't inserted. */
                        ulNeg = 0;
                    }

                    /* Set the base to 10. */
                    ulBase = 10u;

                    /* Convert the value to ASCII. */
                    (void)UART_convertVal(ulValue, ulPos, ulBase, ulNeg, ulCount, cFill, pcBuf);

                    break;
                }

                /* Handle the %s command. */
                case (char) 's':
                {
                    /* Get the string pointer from the varargs. */
                    pcStr = va_arg(vaArgP, char *);

                    /* Determine the length of the string. */
                    for (ulIdx = 0; pcStr[ulIdx] != (char) '\0'; ulIdx++)
                    {}

                    /* Write the string. */
                    (void)UART_dataWrite(pcStr, ulIdx);

                    /* Write any required padding spaces */
                    if (ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        while ((ulCount--)  != 0U)
                        {
                            (void)UART_dataWrite(" ", 1u);
                        }
                    }
                    /* This command has been handled. */
                    break;
                }

                /* Handle the %u command. */
                case (char) 'u':
                {
                    /* Get the value from the varargs. */
                    ulValue = (uint32_t)va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* Set the base to 10. */
                    ulBase = 10u;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    ulNeg = 0;

                    /* Convert the value to ASCII. */
                    (void)UART_convertVal(ulValue, ulPos, ulBase, ulNeg, ulCount, cFill, pcBuf);

                    break;
                }

                /* Handle the %x and %X commands.  Note that they are treated
                 * identically; i.e. %X will use lower case letters for a-f
                 * instead of the upper case letters is should use.  We also
                 * alias %p to %x. */
                case (char) 'x':
                case (char) 'X':
                case (char) 'p':
                {
                    /* Get the value from the varargs. */
                    ulValue = (uint32_t)va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* Set the base to 16. */
                    ulBase = 16u;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    ulNeg = 0;

                    /* Determine the number of digits in the string version of
                     * the value. */
                    (void)UART_convertVal(ulValue, ulPos, ulBase, ulNeg, ulCount, cFill, pcBuf);

                    break;
                }

                /* Handle the %% command. */
                case (char) '%':
                {
                    /* Simply write a single %. */
                    (void)UART_dataWrite(pStr - 1u, 1u);

                    /* This command has been handled. */
                    break;
                }

                /* Handle all other commands. */
                default:
                {
                    /* Indicate an error. */
                    (void)UART_dataWrite("ERROR", 5u);

                    /* This command has been handled. */
                    break;
                }
            }
            pStr++;
        }
    }

    /* End the varargs processing. */
    va_end(vaArgP);
#endif
}

__attribute__((weak)) void vTaskSuspendAll(void)
{

}

__attribute__((weak)) void xTaskResumeAll(void)
{

}

__attribute__((weak)) uint32_t TaskP_disable(void)
{
    vTaskSuspendAll();

    return 0;
}

__attribute__((weak)) void TaskP_restore(uint32_t key)
{
    xTaskResumeAll();
}
