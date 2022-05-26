
//! [include]
#include <drivers/mpu_firewall.h>
//! [include]

void samples()
{
//! [mpu]

    MPU_FIREWALL_RegionParams mpuParams;

    /* Initialize the MPU Param structure */
    MPU_FIREWALL_RegionParams_init(&mpuParams);

    /* Set the region parameters */
    mpuParams.id = 4;
    mpuParams.regionNumber = 0;
    mpuParams.startAddress = 0x70000000;
    mpuParams.endAddress = 0x70000100;
    mpuParams.aidConfig = (0x1<<PRIV_ID_R5FSS0_0) | (0x1<<PRIV_ID_R5FSS0_1);
    mpuParams.aidxConfig = 0;
    mpuParams.supervisorReadConfig = 1;
    mpuParams.supervisorWriteConfig = 1;
    mpuParams.supervisorExecConfig = 1;
    mpuParams.userReadConfig = 1;
    mpuParams.userWriteConfig = 1;
    mpuParams.userExecConfig = 1;
    mpuParams.nonSecureConfig = 1;
    mpuParams.debugConfig = 1;

    /* Program the parameters for the region */
    MPU_FIREWALL_setRegion(&mpuParams);

//! [mpu]
}