let common = system.getScript("/common");

let pmicCfg_tps65224 = {
    twd_pulse_us           : 36,   /* Trigger watchdog input signal deglitch time */
    trig_wdog_pin          : "PMIC_TPS6522X_GPIO2_PIN", /* Trigger watchdog input signal GPIO pin number */
    trig_wdog_pinfunc      : "PMIC_TPS6522X_GPIO_PINFUNC_GPIO2_TRIG_WDOG",  /* Trigger watchdog GPIO pin function */
    qa_wdog_pin1           : "PMIC_TPS6522X_GPIO1_PIN", /* Q&A watchdog I2C SDA input GPIO pin number */
    qa_wdog_pin2           : "PMIC_TPS6522X_GPIO2_PIN", /* Q&A watchdog I2C SCL input GPIO pin number */
    qa_wdog_i2c1_pin1func  : "PMIC_TPS6522X_GPIO_PINFUNC_GPIO", /* Q&A watchdog access using I2C1 pin function */
    qa_wdog_i2c1_pin2func  : "PMIC_TPS6522X_GPIO_PINFUNC_GPIO", /* Q&A watchdog access using I2C1 pin function */
    qa_wdog_i2c2_pin1func  : "PMIC_TPS6522X_GPIO_PINFUNC_GPIO1_SDA_I2C2_SDO_SPI", /* Q&A watchdog access using I2C2 pin function */
    qa_wdog_i2c2_pin2func  : "PMIC_TPS6522X_GPIO_PINFUNC_GPIO2_SCL_I2C2_CS_SPI", /* Q&A watchdog access using I2C2 pin function */
    wdog_fail_int_num      : "PMIC_TPS6522X_WD_FAIL_INT", /* Watchdog fail interrupt number */
};

function getPmicConfigArr() {
    return pmicCfg_tps65224;
}

exports = {
    getPmicConfigArr,
};