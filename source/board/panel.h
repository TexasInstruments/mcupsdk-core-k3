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

#ifndef PANEL_H_
#define PANEL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/hw_include/soc_config.h>
#include <kernel/dpl/SemaphoreP.h>
#include <board/ioexp/ioexp_tca6424.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PANEL_INVALID_VALUE (0xFFFFFFFFU)

/**
 * \brief Panel type supported
 */
#define CONFIG_PANEL_TYPE_I2C                       (0x00U)
#define CONFIG_PANEL_TYPE_DSI                       (0x01U)
#define CONFIG_PANEL_TYPE_INVALID                   (0xFFU)

/**
 * \brief Max number pins configured for panel pin control.
 */
#define PANEL_MAX_NUM_PINS_CTRL                     (0xAU)

/**
 *  \defgroup BOARD_PANEL_MODULE APIs for PANEL
 *  \ingroup BOARD_MODULE
 *
 *  This module contains APIs to program and use the Panel module on the board
 *  like HDMI Panel connected over a bridge.
 *  See \ref BOARD_PANEL_PAGE for more details.
 *
 *  @{
 */


/**
 * \brief Handle to the FLash driver returned by Panel_open()
 */
typedef void  *Panel_Handle;

/**
 * \brief Forward declaration of \ref Panel_Config
 */
typedef struct Panel_Config_s Panel_Config;

/**
 * \brief Forward declaration of \ref Panel_Params
 */
typedef struct Panel_Params_s Panel_Params;

/**
 * \name Panel driver implementation callbacks
 *
 * @{
 */

/**
 * \brief Driver implementation to open a specific panel driver.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of panel device needs to be implemented.
 *
 * \param config [in] Panel configuration for the specific panel device
 * \param params [in] User controllable parameters when opening the panel device
 *
 * \return SystemP_SUCCESS on success, else failure
 */
typedef int32_t (*Panel_OpenFxn)(Panel_Config *config, Panel_Params *params);

/**
 * \brief Driver implementation to close a specific panel driver.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of panel device needs to be implemented.
 *
 * \param config    [in] Panel configuration for the specific panel device.
 * \param params    [in] User controllable parameters when opening the panel
 *                       device.
 *
 * \return SystemP_SUCCESS on success, else failure.
 */
typedef void (*Panel_CloseFxn)(Panel_Config *config, Panel_Params *params);

/**
 * \brief Driver implementation to control panel using a specific panel driver
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of panel device needs to be implemented.
 *
 * \param config    [in] Panel configuration for the specific panel device.
 * \param params    [in] User controllable parameters.
 * \param cmd       [in] Specific command to panel control.
 * \param cmdArgs   [in] Pointer to arguments associated with command.
 *
 * \return SystemP_SUCCESS on success, else failure
 */
typedef int32_t (*Panel_ControlFxn)(Panel_Config *config, Panel_Params *params,
                                    uint32_t cmd, void *cmdArgs);

/**
 * \brief Driver implementation to soft reset the panel.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of panel device needs to be implemented.
 *
 * \param config [in] Panel configuration for the specific panel device.
 * \param params [in] User controllable parameters when opening the panel
 *                    device.
 *
 * \return SystemP_SUCCESS on success, else failure.
 */
typedef int32_t (*Panel_ResetFxn)(Panel_Config *config, Panel_Params *params);

/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t deviceI2cInstId;
    /**< I2C device instance ID to use. */
    uint32_t deviceI2cAddr;
    /**< I2C device address for each device */
    uint32_t inpClk;
    /**< input clock. */
    uint32_t hotPlugGpioIntrLine;
    /**< Hot plug GPIO interrupt line no - if supported by encoder. */
    uint32_t clkEdge;
    /**< Specifies the clock edge to be used to latch data on.
     * FALSE spacifies to latch on falling edge, raising edge otherwise.
     */
    uint32_t outputFormat;
} Panel_BridgeParams;

/**
 *  \brief Configuration paramters for encoder.
 */
typedef struct
{
    uint32_t standard;
    /**< Video standard. For valid values see #Fvid2_Standard. */
    uint32_t videoIfMode;
    /**< Select the video mode, like Embedded sync, different type of
      *  Discrete sync modes.
      *  For valid values see #Fvid2_VideoIfMode.*/
    uint32_t videoIfWidth;
    /**<
     *   <b>videoIfWidth</b>:<br>
     *   Video Interface width , valid options are<br>
     *   FVID2_VIFW_8BIT,<br>
     *   FVID2_VIFW_10BIT,<br>
     *   FVID2_VIFW_16BIT,<br>
     *   FVID2_VIFW_24BIT,<br>
     *   For valid values see #Fvid2_VideoIfWidth.<br>.
     */
    uint32_t videoDataFormat;
    /**<
     *  RGB or YUV data format. valid values are given below \n
     *  For valid values see #Fvid2_DataFormat.
     *  For Sil9022a bridge following data formats are supported
     *  <b>videoDataFormat</b>:<br>
     *  Output Data format, valid options are<br>
     *  FVID2_DF_YUV422I_YUYV,<br>
     *  FVID2_DF_RGB24_888,<br>
     */
} Panel_vidOutputParams;

/**
 *  \brief Panel pin control data.
 */
typedef struct
{
    uint32_t pinIoNum;
    /**< Port number for the pin. */
    uint32_t pinType;
    /**< Pin type : OUTPUT or INPUT */
    uint32_t pinVal;
    /**< Pin set value : HIGH, LOW */
} Panel_PinConfig;

/**
 *  \brief Configuration paramters for panel pin control.
 */
typedef struct
{
    uint32_t pinCtrlI2cInstance;
    /**< I2C instance for pinCtrl */
    uint32_t pinCtrlI2cAddr;
    /**< I2C address for pinCtrl */
    uint32_t numPins;
    /**< Number of pins to be controlled for Panel */
    Panel_PinConfig pinConf[PANEL_MAX_NUM_PINS_CTRL];
    /**< Pin data for pin control */
    TCA6424_Config ioExpConfig;
    /**< IO expander config */
} Panel_PinCtrl;

/**
 * \brief Parameters passed during Panel_open()
 */
typedef struct Panel_Params_s
{
    Panel_BridgeParams      bridgeParams;
    Panel_vidOutputParams   vidOutParams;
} Panel_Params;

/**
 * \brief Driver implementation callbacks
 */
typedef struct
{
    Panel_OpenFxn       openFxn;
    /**< Panel driver implementation specific callback */
    Panel_CloseFxn      closeFxn;
    /**< Panel driver implementation specific callback */
    Panel_ControlFxn    controlFxn;
    /**< Panel driver implementation specific callback */
    Panel_ResetFxn      resetFxn;
    /**< Panel driver implementation specific callback */
} Panel_Fxns;

/**
 * \brief Panel driver configuration, these are filled by
 *  SysCfg based on the panel device that is selected.
 */
typedef struct Panel_Config_s
{
    uint32_t                   panelType;
    /**< Type of Panel interface */
    Panel_Fxns                 *fxns;
    /**< Panel device implementation functions */
    void                       *object;
    /**< Panel driver object, used to maintain driver implementation state */
    void                       *inputParams;
    /**< Pointer to Panel params used for Panel config */
    Panel_PinCtrl              *pinConfig;
    /**< Pointer to Panel pin control structure */
    SemaphoreP_Object          lockSem;
    /**< Semaphore to protect the panel layer calls per instance. */

} Panel_Config;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Open panel driver
 *
 * Global variables `Panel_Config gPanelConfig[]` and `uint32_t gPanelConfigNum`
 * is instantiated by SysCfg to describe the panel configuration based on user
 * selection in SysCfg.
 *
 * \param instanceId [in] Index within `Panel_Config gPanelConfig[]` denoting
 *                        the panel driver to open.
 * \param params    [in] Open parameters.
 *
 * \return Handle to panel driver which should be used in subsequent API call.
 * \return NULL in case of failure.
 */
Panel_Handle Panel_open(uint32_t instanceId, Panel_Params *params);

/**
 * \brief Close panel driver.
 *
 * \param handle    [in] Panel driver handle from \ref Panel_open.
 */
void Panel_close(Panel_Handle handle);

/**
 * \brief Get handle to panel driver.
 *
 * \param instanceId    [in] Index within `Panel_Config gPanelConfig[]`.
 *
 * \return Handle to panel driver.
 * \return NULL in case of failure.
 */
Panel_Handle Panel_getHandle(uint32_t instanceId);

/**
 * \brief Control Panel operation using panel specific commands.
 *
 * Commands can be refered from specific panel interface layer.
 *
 * \param handle    [in] Panel driver handle from \ref Panel_open.
 * \param cmd       [in] Input command to control panel.
 * \param cmdArgs   [in] Pointer to command arguments.
 *
 * \return SystemP_SUCCESS on success, else failure.
 */
int32_t Panel_control(Panel_Handle handle, uint32_t cmd, void *cmdArgs);

/**
 * \brief Do a reset of the panel.
 *
 * \param handle [in] Panel driver handle from \ref Panel_open.
 *
 * \return SystemP_SUCCESS on success, else failure.
 */
int32_t Panel_reset(Panel_Handle handle);

/**
 * \brief Return panel index based on type of panel.
 *
 * \param panelType   [in] Panel type.
 *
 * \return Panel driver instance index corresponding
 *          to the panel type.
 */
uint32_t Panel_getPanelInterfaceIndex(uint32_t panelType);

/**
 * \brief This function initializes the Panel module.
 */
void Panel_init(void);

/**
 * \brief This function de-initializes the Panel module.
 */
void Panel_deinit(void);

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* PANEL_H_ */