/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \ingroup DRV_DSS_MODULE
 *  \defgroup DRV_DSS_DCTRL_MODULE Display Controller Driver
 *            This is DSS Display Controller driver documentation
 *
 *  @{
 */

/**
 *  \file dss_dctrl.h
 *
 *  \brief DSS Controller Driver API/interface file.
 */

#ifndef DSS_DCTRL_H_
#define DSS_DCTRL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Video Port sync loss callback function prototype.
 *
 * \param vpId     [OUT] Video Port Id.
 * \param appData  [OUT] Application's private data.
 *
 * \return None.
 */
typedef void (*Dss_DctrlSyncLostCbFxn)(uint32_t vpId, void *appData);

/** \brief Forward declaration for instance object. */
typedef struct Dss_DctrlVpSafetyCbData_t Dss_DctrlVpSafetyCbData;

/**
 * \brief Video Port safety error callback function prototype.
 *
 * \param vpId          [OUT] Video Port Id.
 * \param safetyCbData  [OUT] Safety Callback Data.
 *                            Refer #Dss_DctrlVpSafetyCbData_t for details
 * \param appData       [OUT] Application's private data.
 *
 * \return None.
 */
typedef void (*Dss_DctrlSafetyErrCbFxn)(uint32_t vpId,
                                        Dss_DctrlVpSafetyCbData safetyCbData,
                                        void *appData);

/**
 * \brief Video Port line number callback function prototype.
 *
 * \param vpId     [OUT] Video Port Id.
 * \param appData  [OUT] Application's private data.
 *
 * \return None.
 */
typedef void (*Dss_DctrlLineNumCbFxn)(uint32_t vpId, void *appData);

/*
 *  Display controller driver IOCTLs.
 */

/**
 *  \ingroup  DRV_DSS_DCTRL_MODULE
 *  \defgroup DRV_DSS_DCTRL_IOCTL Display Controller IOCTLs
 *  @{
 *
 * These are display controller FVID2 APIs that can be called by the
 * application.
 */

/**
 * \brief Command to set the DSS display path configuration.
 *
 *  All the DSS modules handled by the Display Controller can be
 *  represented by a graph, where node represents a module like video port,
 *  overlay etc. and edge is present between two nodes if they are connected.
 *  All DSS paths can be configured by this IOCTL in one shot. Use macros
 *  defined in <dss_soc.h> for different node ids.
 *
 *  This IOCTL takes list of edges connecting nodes and configures display
 *  paths. It first validates these paths and then configures DSS for the
 *  display paths. It configures all the modules present in the path.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlPathInfo
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_PATH              (DSS_DCTRL_IOCTL_BASE + 0x01U)

/**
 * \brief Command to clear the DSS display path configuration.
 *
 *  This IOCTL takes list of edges connecting nodes and clears the
 *  configuration. It also stops Video Ports.
 *
 *  It does not validates the edge list. It simply disables the edge
 *  connecting nodes. For the Video Ports, it checks for the validity and
 *  then disables the video port if there are no errors.
 *  Use macros defined in <dss_soc.h> for different node ids.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlPathInfo
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_CLEAR_PATH            (DSS_DCTRL_IOCTL_BASE + 0x02U)

/**
 * \brief Command to set Video Port configuration.
 *
 *  This IOCTL is used to set the Video Port configuration if Video Port
 *  is not on. For the enabled Video Port, port has to be stopped first,
 *  then configuration can can be changed. Refer #Dss_DctrlVpParams
 *  for configuration details.
 *  This IOCTL should be called before IOCTL_DSS_DCTRL_SET_PATH.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlVpParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_SET_VP_PARAMS         (DSS_DCTRL_IOCTL_BASE + 0x03U)

/**
 * \brief Command to set configuration of the given overlay.
 *
 *  This IOCTL is used to set the different Overlay parameters. Refer
 *  #Dss_DctrlOverlayParams for configuration details.
 *  Note: In case color bar enable is TRUE then this IOCTL should be called at
 *  the end after doing all other display controller configuration.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlOverlayParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS    (DSS_DCTRL_IOCTL_BASE + 0x04U)

/**
 * \brief Command to set layer/Z-order configuration of the given overlay.
 *
 *  This IOCTL is used to set the layer/Z-order configuration. Refer
 *  #Dss_DctrlOverlayLayerParams for details.
 *  Note: User should pass the layer configuration for all the video pipes which
 *  are present in the DSS in order to set/change the Z order.
 *  In case a particular pipe is disabled, layerNum should be set to
 *  CSL_DSS_OVERLAY_LAYER_INVALID.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlOverlayLayerParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_SET_LAYER_PARAMS      (DSS_DCTRL_IOCTL_BASE + 0x05U)

/**
 * \brief Command to program the CSC coefficients for Video Port.
 *  By default BT 601 coefficients are set.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlVpCscCoeff
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF      (DSS_DCTRL_IOCTL_BASE + 0x06U)

/**
 * \brief Command to set advance Video Port configuration.
 *
 *  This IOCTL is used to program the advance Video Port configuration.
 *  Refer #Dss_DctrlAdvVpParams for configuration details.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlAdvVpParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS     (DSS_DCTRL_IOCTL_BASE + 0x07U)

/**
 * \brief Command to program blank timing parameters of given LCD.
 *
 *  This IOCTL is used to program the blank timing parameters for the LCD.
 *  This IOCTL can be called dynamically at runtime.
 *  Note: The change in timing will take effect from the next vsync.
 *  This API should be called in the vsync callback to the application in the
 *  ISR context or immediately after that in task/swi context. Calling this
 *  IOCTL near the vsync should be avoided as the shadow to work copy could
 *  happens while we are changing the timing parameters and could result in
 *  taking only a part of this configuration for next one frame or delaying the
 *  timing change by next one frame. Subsequent frames will have proper timing.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlLcdBlankTimingParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_LCD_BLANK_TIMING_PARAMS   \
                                              (DSS_DCTRL_IOCTL_BASE + 0x08U)

/**
 * \brief Command to program Safety Check configuration at Video Port Output.
 *
 *  This IOCTL is used to program the safety check configuration parameters.
 *  Note: There are up to four sub-regions within the active video output in
 *  which safety check can be enabled. This IOCTL should be called separately
 *  for each region.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlVpSafetyChkParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS      \
                                              (DSS_DCTRL_IOCTL_BASE + 0x09U)

/**
 * \brief IOCTL to get the number of errors for a given Video Port.
 *
 *  This IOCTL is used to get the count of sync lost errors, security violations
 *  and safety check errors for a given video port.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlVpErrorStats
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS    (DSS_DCTRL_IOCTL_BASE + 0x0AU)

/**
 * \brief IOCTL to set the global DSS parameters.
 *
 *  This IOCTL can be used to set the global mflag and CBA configuration.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlGlobalDssParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS (DSS_DCTRL_IOCTL_BASE + 0x0BU)

/**
 * \brief Command to disable Video Port.
 *
 *  This IOCTL is used to disable the Video Port.
 *  Refer #Dss_DctrlVpParams for configuration details.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlVpParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_STOP_VP               (DSS_DCTRL_IOCTL_BASE + 0x0CU)

/**
 * \brief Command to register Video Port sync lost callback function.
 *
 *  This IOCTL can be used to register a callback when there is a sync loss for
 *  a particular video port. See #Dss_DctrlSyncLostCbFxn for details. This IOCTL
 *  is per Video Port and hence should be called separately for each port.
 *  Note: syncLostCbFxn should be set to NULL in order to unregister
 *  the callback.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlSyncLostCbParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB  (DSS_DCTRL_IOCTL_BASE + 0x0DU)

/**
 * \brief Command to register Video Port line number callback function
 *
 *  This IOCTL can be used to register a callback when there is a line number
 *  interrupt for a particular video port. See #Dss_DctrlLineNumCbFxn for
 *  details. This IOCTL is per Video Port and hence should be called separately
 *  for each port.
 *  Note: lineNumCbFxn should be set to NULL in order to unregister
 *  the callback.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlLineNumCbParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB  (DSS_DCTRL_IOCTL_BASE + 0x0EU)

/**
 * \brief Command to set the DSI specific parameters
 *
 *  Currently used to set number of output lanes.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DctrlDsiParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_SET_DSI_PARAMS       (DSS_DCTRL_IOCTL_BASE + 0x0FU)

/**
 * \brief Command to detect if the DP cable is connected or not.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DCTRL_IS_DP_CONNECTED      (DSS_DCTRL_IOCTL_BASE + 0x10U)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Structure containing DSS path information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_PATH.
 *  This IOCTL takes the array of edges connected between nodes.
 */
typedef struct
{
    uint32_t numEdges;
    /**< Number edge in the edgeInfo array */
    Fvid2_GraphEdgeInfo edgeInfo[DSS_DCTRL_MAX_EDGES];
    /**< List of edges connecting DSS modules. Display controller parses these
     *   edges and enables/disables input/output path in the appropriate DSS
     *   module. This edge tells which module is connected to which module
     *   enabling output in edge start module and input in edge end module.*/
} Dss_DctrlPathInfo;

/**
 * \brief Structure containing DSS sync operations configuration.
 *  This structure is used as a part of \ref Dss_DctrlVpParams.
 */
typedef struct
{
    uint32_t enabled;
    /**< Enable sync operations configuration */
    uint32_t isPrimary;
    /**< Whether this VP is the primary output.
     *   Only operations on the primary VP results in H/W
     *   register operations.
     *   For secondary VPs, the enable / setGo operations
     *   pend on the corresponding operation on the primary VP */
    uint32_t syncVpIds[CSL_DSS_VP_ID_MAX];
    /**< Array of VP Ids for Sync operations */
    uint32_t numSyncVpIds;
    /**< Number of valid VP Ids in #syncVpIds */
} Dss_DctrlSyncOpCfg;

/**
 * \brief Structure containing Video Port information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_VP_PARAMS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    CSL_DssVpLcdOpTimingCfg lcdOpTimingCfg;
    /**< Timing configuration for the LCD output.
     *   See \ref CSL_DssVpLcdOpTimingCfg for details */
    CSL_DssVpLcdSignalPolarityCfg lcdPolarityCfg;
    /**< LCD Polarity Configuration.
     *   See \ref CSL_DssVpLcdSignalPolarityCfg for details */
    CSL_DssVpLcdTdmCfg lcdTdmCfg;
    /**< LCD TDM Configuration. See \ref CSL_DssVpLcdTdmCfg for details */
    Dss_DctrlSyncOpCfg syncOpCfg;
    /**< Sync operation Configuration. See \ref Dss_DctrlSyncOpCfg for details */
} Dss_DctrlVpParams;

/**
 * \brief Structure containing Overlay information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS.
 */
typedef struct
{
    uint32_t overlayId;
    /**< Overlay Id. See \ref CSL_DssOverlayId for values */
    uint32_t colorbarEnable;
    /**< Overlay Color bar Enable. TRUE: Enable FALSE: Disable */
    CSL_DssOverlayCfg overlayCfg;
    /**< Overlay Configuration. See \ref CSL_DssOverlayCfg for details */
} Dss_DctrlOverlayParams;

/**
 * \brief Structure containing Overlay layer information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_LAYER_PARAMS.
 */
typedef struct
{
    uint32_t overlayId;
    /**< Overlay Id. See \ref CSL_DssOverlayId for values */
    uint32_t pipeLayerNum[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Layer to which a particular Video Pipe Id is connected.
     *   For valid values see \ref CSL_DssOverlayLayerNum */
} Dss_DctrlOverlayLayerParams;

/**
 * \brief Structure containing Video Port CSC information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    uint32_t cscPos;
    /**< Position of CSC block wrt GAMMA module.
     *   Refer \ref CSL_DssVpCscPos for values */
    CSL_DssCscCoeff cscCoeff;
    /**< Video Port CSC coefficients.
     *   See \ref CSL_DssCscCoeff for details */
} Dss_DctrlVpCscCoeff;

/**
 * \brief Structure containing advance Video Port information.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    CSL_DssVpLcdAdvSignalCfg lcdAdvSignalCfg;
    /**< Advance Signal Configuration for the LCD.
     *   See \ref CSL_DssVpLcdAdvSignalCfg for details */
} Dss_DctrlAdvVpParams;

/**
 * \brief Structure containing LCD Blank Timing Configuration.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_SET_LCD_BLANK_TIMING_PARAMS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    uint32_t dvoFormat;
    /**< Digital output format. For valid values see \ref Fvid2_DVFormat */
    CSL_DssVpLcdBlankTimingCfg lcdBlankTimingCfg;
    /**< Timing configuration for the LCD.
     *   See \ref CSL_DssVpLcdBlankTimingCfg for details */
} Dss_DctrlLcdBlankTimingParams;

/**
 * \brief Structure containing Safety Check configuration for a particular
 *  region.
 */
typedef struct
{
    uint32_t regionId;
    /**< Safety Region Id */
    uint32_t referenceSign;
    /**< Reference Safety Signature for Data Correctness Check */
    CSL_DssSafetyChkCfg safetyChkCfg;
    /**< Safety Check Configuration. See \ref CSL_DssSafetyChkCfg for details */
} Dss_DctrlRegionSafetyChkCfg;

/**
 * \brief Structure containing safety error callback data.
 *  This structure is returned by the driver .
 */
struct Dss_DctrlVpSafetyCbData_t
{
    uint32_t regionId;
    /**< Region Id for which interrupt has occurred */
    uint32_t capturedSign;
    /**< Captured Safety Signature by Data Correctness Check, set to 0x0 in case
     *   of frame freeze detect */
};

/**
 * \brief Structure containing Safety Check configuration of Video Port.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    uint32_t safetySignSeedVal;
    /**< Safety Signature Seed Value, only one non-zero value is possible in a
     *   particular context. In case user passes multiple non-zero values for
     *   different regions, previous value is overwritten. */
    Dss_DctrlRegionSafetyChkCfg regionSafetyChkCfg;
    /**< Safety Check Configuration for a particular region.
     *   See \ref Dss_DctrlRegionSafetyChkCfg for details */
    Dss_DctrlSafetyErrCbFxn safetyErrCbFxn;
    /**< Safety Error callback function */
    Dss_DctrlVpSafetyCbData safetyCbData;
    /**< Safety Error callback data to be returned to application */
    void *appData;
    /**< Private data of application */
} Dss_DctrlVpSafetyChkParams;

/**
 * \brief Structure containing Error Stats of Video Port.
 *  This structure is used as an argument to IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    uint32_t syncLost;
    /**< SyncLost Error Count of the LCD */
    uint32_t safetyViolation[CSL_DSS_VP_SAFETY_REGION_MAX];
    /**< Safety Violation Count */
    uint32_t securityViolation;
    /**< Security Violation Count */
} Dss_DctrlVpErrorStats;

/**
 * \brief Structure containing global DSS Configuration.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS.
 */
typedef struct
{
    CSL_DssGlobalMFlagCfg globalMflagCfg;
    /**< Global Mflag Configuration.
     *   See \ref CSL_DssGlobalMFlagCfg for details */
    CSL_DssCbaCfg cbaCfg;
    /**< CBA Priority Configuration. See \ref CSL_DssCbaCfg for details */
} Dss_DctrlGlobalDssParams;

/**
 * \brief Structure containing Sync Lost callback parameters.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    Dss_DctrlSyncLostCbFxn syncLostCbFxn;
    /**< Sync lost callback function */
    void *appData;
    /**< Private data of application */
} Dss_DctrlSyncLostCbParams;

/**
 * \brief Structure containing line number interrupt callback parameters.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    Dss_DctrlLineNumCbFxn lineNumCbFxn;
    /**< Line number callback function */
    void *appData;
    /**< Private data of application */
} Dss_DctrlLineNumCbParams;

/**
 * \brief Structure containing DSI Output parameters.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DCTRL_SET_DSI_PARAMS.
 */
typedef struct
{
    uint32_t instId;
    /**< DSI Instance ID, currently note used */
    uint32_t numOfLanes;
    /**< Number of outputs lanes for DSI output, max 4 */
    uint32_t laneSpeedInKbps;
    /**< Exact DPHY lane speed from the selected speed band in Megabits per sec.
     *   This parameter is set to default value during init time.
     *   If updated in the application after init, newly set value will be used
     *   for DPHY clock configurations.
     */
} Dss_DctrlDsiParams;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 *  \brief Dss_DctrlPathInfo structure init function.
 *
 *  \param  pathInfo  [IN]Pointer to #Dss_DctrlPathInfo structure.
 *
 */
static inline void Dss_dctrlPathInfoInit(Dss_DctrlPathInfo *pathInfo);

/**
 *  \brief Dss_DctrlVpParams structure init function.
 *
 *  \param  vpParams  [IN]Pointer to #Dss_DctrlVpParams structure.
 *
 */
static inline void Dss_dctrlVpParamsInit(Dss_DctrlVpParams *vpParams);

/**
 *  \brief Dss_DctrlOverlayParams structure init function.
 *
 *  \param  overlayParams  [IN]Pointer to #Dss_DctrlOverlayParams structure.
 *
 */
static inline void Dss_dctrlOverlayParamsInit(
    Dss_DctrlOverlayParams *overlayParams);

/**
 *  \brief Dss_DctrlOverlayLayerParams structure init function.
 *
 *  \param  layerParams  [IN]Pointer to #Dss_DctrlOverlayLayerParams structure.
 *
 */
static inline void Dss_dctrlOverlayLayerParamsInit(
    Dss_DctrlOverlayLayerParams *layerParams);

/**
 *  \brief Dss_DctrlAdvVpParams structure init function.
 *
 *  \param  advVpParams  [IN]Pointer to #Dss_DctrlAdvVpParams structure.
 *
 */
static inline void Dss_dctrlAdvVpParamsInit(Dss_DctrlAdvVpParams *advVpParams);

/**
 *  \brief Dss_DctrlLcdBlankTimingParams structure init function.
 *
 *  \param  lcdBlankTimingParams  [IN]Pointer to #Dss_DctrlLcdBlankTimingParams
 *                                    structure.
 *
 */
static inline void Dss_dctrlLcdBlankTimingParamsInit(
    Dss_DctrlLcdBlankTimingParams *lcdBlankTimingParams);

/**
 *  \brief Dss_DctrlRegionSafetyChkCfg structure init function.
 *
 *  \param  regionSafetyChkCfg  [IN]Pointer to #Dss_DctrlRegionSafetyChkCfg
 *                                  structure.
 *
 */
static inline void Dss_dctrlRegionSafetyChkCfgInit(
    Dss_DctrlRegionSafetyChkCfg *regionSafetyChkCfg);

/**
 *  \brief Dss_DctrlVpSafetyCbData structure init function.
 *
 *  \param  safetyCbData  [IN]Pointer to #Dss_DctrlVpSafetyCbData_t structure.
 *
 */
static inline void Dss_dctrlVpSafetyCbDataInit(
    Dss_DctrlVpSafetyCbData *safetyCbData);

/**
 *  \brief Dss_DctrlVpSafetyChkParams structure init function.
 *
 *  \param  vpSafetyChkParams  [IN]Pointer to #Dss_DctrlVpSafetyChkParams
 *                                 structure.
 *
 */
static inline void Dss_dctrlVpSafetyChkParamsInit(
    Dss_DctrlVpSafetyChkParams *vpSafetyChkParams);

/**
 *  \brief Dss_DctrlVpErrorStats structure init function.
 *
 *  \param  vpErrorStats  [IN]Pointer to #Dss_DctrlVpErrorStats structure.
 *
 */
static inline void Dss_dctrlVpErrorStatsInit(
    Dss_DctrlVpErrorStats *vpErrorStats);

/**
 *  \brief Dss_DctrlGlobalDssParams structure init function.
 *
 *  \param  globalDssParams  [IN]Pointer to #Dss_DctrlGlobalDssParams structure.
 *
 */
static inline void Dss_dctrlGlobalDssParamsInit(
    Dss_DctrlGlobalDssParams *globalDssParams);

/**
 *  \brief Dss_DctrlSyncLostCbParams structure init function.
 *
 *  \param  syncLostCbParams  [IN]Pointer to #Dss_DctrlSyncLostCbParams structure.
 *
 */
static inline void Dss_dctrlSyncLostCbParamsInit(
    Dss_DctrlSyncLostCbParams *syncLostCbParams);

/**
 *  \brief Dss_DctrlLineNumCbParams structure init function.
 *
 *  \param  lineNumCbParams  [IN]Pointer to #Dss_DctrlLineNumCbParams structure.
 *
 */
static inline void Dss_dctrlLineNumCbParamsInit(
    Dss_DctrlLineNumCbParams *lineNumCbParams);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Dss_dctrlPathInfoInit(Dss_DctrlPathInfo *pathInfo)
{
    uint32_t i;
    if(NULL != pathInfo)
    {
        pathInfo->numEdges = 0U;
        for(i=0U; i<DSS_DCTRL_MAX_EDGES; i++)
        {
            pathInfo->edgeInfo[i].startNode = 0U;
            pathInfo->edgeInfo[i].endNode = 0U;
        }
    }
}

static inline void Dss_DctrlSyncOpCfgInit(Dss_DctrlSyncOpCfg *syncOpCfg)
{
    uint32_t i;

    if(NULL != syncOpCfg)
    {
        syncOpCfg->enabled = FALSE;
        syncOpCfg->isPrimary = TRUE;
        for(i = 0; i < CSL_DSS_VP_ID_MAX; i++)
        {
            syncOpCfg->syncVpIds[i] = CSL_DSS_VP_ID_1;
        }
        syncOpCfg->numSyncVpIds = 0;
    }
}

static inline void Dss_dctrlVpParamsInit(Dss_DctrlVpParams *vpParams)
{
    if(NULL != vpParams)
    {
        vpParams->vpId = CSL_DSS_VP_ID_1;
        CSL_dssVpLcdOpTimingCfgInit(&(vpParams->lcdOpTimingCfg));
        CSL_dssVpLcdSignalPolarityCfgInit(&(vpParams->lcdPolarityCfg));
        CSL_dssVpLcdTdmCfgInit(&(vpParams->lcdTdmCfg));
        Dss_DctrlSyncOpCfgInit(&(vpParams->syncOpCfg));
    }
}

static inline void Dss_dctrlOverlayParamsInit(
    Dss_DctrlOverlayParams *overlayParams)
{
    if(NULL != overlayParams)
    {
        overlayParams->overlayId = CSL_DSS_OVERLAY_ID_1;
        overlayParams->colorbarEnable = FALSE;
        CSL_dssOverlayCfgInit(&(overlayParams->overlayCfg));
    }
}

static inline void Dss_dctrlOverlayLayerParamsInit(
    Dss_DctrlOverlayLayerParams *layerParams)
{
    uint32_t i;
    if(NULL != layerParams)
    {
        layerParams->overlayId = CSL_DSS_OVERLAY_ID_1;
        for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
            layerParams->pipeLayerNum[i] = CSL_DSS_OVERLAY_LAYER_INVALID;
        }
    }
}

static inline void Dss_dctrlAdvVpParamsInit(Dss_DctrlAdvVpParams *advVpParams)
{
    if(NULL != advVpParams)
    {
        advVpParams->vpId = CSL_DSS_VP_ID_1;
        CSL_dssVpLcdAdvSignalCfgInit(&(advVpParams->lcdAdvSignalCfg));
    }
}

static inline void Dss_dctrlLcdBlankTimingParamsInit(
    Dss_DctrlLcdBlankTimingParams *lcdBlankTimingParams)
{
    if(NULL != lcdBlankTimingParams)
    {
        lcdBlankTimingParams->vpId = CSL_DSS_VP_ID_1;
        CSL_dssVpLcdBlankTimingCfgInit(&(lcdBlankTimingParams->lcdBlankTimingCfg));
    }
}

static inline void Dss_dctrlRegionSafetyChkCfgInit(
    Dss_DctrlRegionSafetyChkCfg *regionSafetyChkCfg)
{
    if(NULL != regionSafetyChkCfg)
    {
        regionSafetyChkCfg->regionId = CSL_DSS_VP_SAFETY_REGION_0;
        regionSafetyChkCfg->referenceSign = 0U;
        CSL_dssSafetyChkCfgInit(&(regionSafetyChkCfg->safetyChkCfg));
    }
}

static inline void Dss_dctrlVpSafetyCbDataInit(
    Dss_DctrlVpSafetyCbData *safetyCbData)
{
    if(NULL != safetyCbData)
    {
        safetyCbData->regionId = CSL_DSS_VP_SAFETY_REGION_0;
        safetyCbData->capturedSign = 0U;
    }
}

static inline void Dss_dctrlVpSafetyChkParamsInit(
    Dss_DctrlVpSafetyChkParams *vpSafetyChkParams)
{
    if(NULL != vpSafetyChkParams)
    {
        vpSafetyChkParams->vpId = CSL_DSS_VP_ID_1;
        vpSafetyChkParams->safetySignSeedVal = 0U;
        Dss_dctrlRegionSafetyChkCfgInit(&(vpSafetyChkParams->regionSafetyChkCfg));
        vpSafetyChkParams->safetyErrCbFxn = NULL;
        Dss_dctrlVpSafetyCbDataInit(&(vpSafetyChkParams->safetyCbData));
        vpSafetyChkParams->appData = NULL;
    }
}

static inline void Dss_dctrlVpErrorStatsInit(Dss_DctrlVpErrorStats *vpErrorStats)
{
     uint32_t i;
    if(NULL != vpErrorStats)
    {
        vpErrorStats->vpId = CSL_DSS_VP_ID_1;
        vpErrorStats->syncLost = 0U;
        for(i=0U; i<CSL_DSS_VP_SAFETY_REGION_MAX; i++)
        {
            vpErrorStats->safetyViolation[i] = 0U;
        }
        vpErrorStats->securityViolation = 0U;
    }
}

static inline void Dss_dctrlGlobalDssParamsInit(
    Dss_DctrlGlobalDssParams *globalDssParams)
{
    if(NULL != globalDssParams)
    {
        CSL_dssGlobalMFlagCfgInit(&(globalDssParams->globalMflagCfg));
        CSL_dssCbaCfgInit(&(globalDssParams->cbaCfg));
    }
}

static inline void Dss_dctrlSyncLostCbParamsInit(
    Dss_DctrlSyncLostCbParams *syncLostCbParams)
{
    if(NULL != syncLostCbParams)
    {
        syncLostCbParams->vpId = CSL_DSS_VP_ID_1;
        syncLostCbParams->syncLostCbFxn = NULL;
        syncLostCbParams->appData = NULL;
    }
}

static inline void Dss_dctrlLineNumCbParamsInit(
    Dss_DctrlLineNumCbParams *lineNumCbParams)
{
    if(NULL != lineNumCbParams)
    {
        lineNumCbParams->vpId = CSL_DSS_VP_ID_1;
        lineNumCbParams->lineNumCbFxn = NULL;
        lineNumCbParams->appData = NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DCTRL_H_ */

/** @} */
