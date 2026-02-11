/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* This file declares the DPL timer unit test interface, including shared
 * macros, typedefs, global variables, and function declarations used
 * across single-threaded and multi-threaded DPL timer test cases.
 * Tests validate TimerP APIs such as setup, start, stop, period
 * configuration (usec/nsec), one-shot vs continuous mode, prescaler
 * settings, interrupt/callback registration, and multi-instance
 * operation. Both single-thread (st) and multi-thread (mt) test
 * suites are supported via conditional compilation.
 */

 #ifndef TEST_DPL_TIMER_H_
 #define TEST_DPL_TIMER_H_

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include <string.h>
#include <unity.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include "kernel/dpl/SemaphoreP.h"
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_dpl_config.h"

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/


/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/



/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

extern HwiP_Object gTimerHwiObj[];
/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/


#endif /* TEST_DPL_TIMER_H_ */
