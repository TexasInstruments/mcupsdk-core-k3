
#include <stdio.h>
//! [include]
#include <board/pmic.h>
#include <board/pmic/pmic_i2c.h>

#define CONFIG_PMIC0            (0U)
#define MAIN_I2C (0U)
#define CONFIG_PMIC_NUM_INSTANCES (1U)

/* PMIC Driver handles - opened during Board_pmicOpen() */
PMIC_Handle gPmicHandle[CONFIG_PMIC_NUM_INSTANCES];

/* PMIC LLD Driver handles - opened during Pmic_init() */
Pmic_CoreHandle_t gPmicCoreHandle[CONFIG_PMIC_NUM_INSTANCES];

Pmic_CoreCfg_t gPmicCoreCfg[CONFIG_PMIC_NUM_INSTANCES] =
{
    {
        .pmicDeviceType      = PMIC_DEV_BURTON_TPS6522X,
        .slaveAddr           = 0x48,
        .nvmSlaveAddr        = 0x49,
        .qaSlaveAddr         = 0x12,
        .i2c1Speed           = PMIC_I2C_STANDARD_MODE,
        .pFnPmicCommIoRead   = &PMIC_i2cRead,
        .pFnPmicCommIoWrite  = &PMIC_i2cWrite,
        .validParams         = (PMIC_CFG_DEVICE_TYPE_VALID_SHIFT   | PMIC_CFG_COMM_MODE_VALID_SHIFT    | \
                                PMIC_CFG_SLAVEADDR_VALID_SHIFT     | PMIC_CFG_QASLAVEADDR_VALID_SHIFT  | \
                                PMIC_CFG_NVMSLAVEADDR_VALID_SHIFT  | PMIC_CFG_COMM_IO_RD_VALID_SHIFT   | \
                                PMIC_CFG_COMM_IO_WR_VALID_SHIFT    | PMIC_CFG_I2C1_SPEED_VALID_SHIFT   | \
                                PMIC_CFG_CRITSEC_START_VALID_SHIFT | PMIC_CFG_CRITSEC_STOP_VALID_SHIFT),
        .instType            = PMIC_MAIN_INST,
        .commMode            = PMIC_INTF_SINGLE_I2C,
        .pFnPmicCritSecStart = &PMIC_critSecStartFn,
        .pFnPmicCritSecStop  = &PMIC_critSecStopFn,
    },
};

/* PMIC Config */
PMIC_Config gPmicConfig[CONFIG_PMIC_NUM_INSTANCES] =
{
   {
        .pmicConfigData  = (Pmic_CoreCfg_t *)&gPmicCoreCfg[CONFIG_PMIC0],
        .pmicCoreHandle  = (Pmic_CoreHandle_t *)&gPmicCoreHandle[CONFIG_PMIC0],
   },
};

/* PMIC params */
PMIC_Params gPmicParams[CONFIG_PMIC_NUM_INSTANCES] =
{
    {
        .mainDrvinstance = MAIN_I2C,
    },
};

uint32_t gPmicConfigNum = CONFIG_PMIC_NUM_INSTANCES;

//! [include]

void open(void)
{
//! [open]
    PMIC_init();
    gPmicHandle[CONFIG_PMIC0] = NULL;
    gPmicHandle[CONFIG_PMIC0] = PMIC_open(CONFIG_PMIC0, &gPmicParams[CONFIG_PMIC0]);
    if (!gPmicHandle[CONFIG_PMIC0])
    {
        DebugP_assert(FALSE);
    }
//! [open]
}

void close(void)
{
//! [close]
    PMIC_close(gPmicHandle[CONFIG_PMIC0]);
//! [close]
}

void pmic_gpio_config(void)
{
//! [pmic_gpio_config]
    /* Configure a GPIO pin in the PMIC */
    int32_t        status = PMIC_ST_SUCCESS;
    Pmic_GpioCfg_t gpioCfg =
    {
        .pinDir = PMIC_GPIO_INPUT,
        .pinFunc = PMIC_TPS6522X_GPIO_PINFUNC_GPIO6_NERR_MCU,
        .pullCtrl = PMIC_GPIO_PULL_DOWN,
        .deglitchEnable = PMIC_GPIO_DEGLITCH_ENABLE,
    };
    status = Pmic_gpioSetConfiguration(gPmicConfig[CONFIG_PMIC0].pmicCoreHandle, \
                                       PMIC_TPS6522X_GPIO6_PIN, gpioCfg);
    if (PMIC_ST_SUCCESS != status)
    {
        DebugP_assert(FALSE);
    }
//! [pmic_gpio_config]
}
