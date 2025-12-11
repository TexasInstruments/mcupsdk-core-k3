# PBIST {#SDL_PBIST_PAGE}

[TOC]

Built-in Self-test (BIST) is a feature that allows self testing of the memory areas and logic circuitry in an Integrated Circuit (IC) without any external test equipment. In an embedded system, these tests are typically used during boot time or shutdown of the system to check the health of an SoC.

PBIST is used to test the memory regions in the SoC and provides detection for permanent faults. The primary use case for PBIST is when it is invoked at start-up providing valuable information on any stuck-at bits in the memory.

There can be multiple instances of PBIST in the SoC, and each has a number of memory regions associated with it. SDL provides support for PBIST features such as execution of PBIST test-for-diagnostic to test the PBIST logic and execution of PBIST. The same API is used with different configuration parameters to execute each instance. Checking of the status of HW POST PBIST execution is also supported.

Some things to note:

* PBIST is expected to be run at boot-time or once per drive cycle.
* PBIST must be run from a different core than is being tested. This is because the test is destructive in nature. For this reason also, after BIST test it is necessary to reset the module.
* If SW-initiated PBIST is executed after the IP under test is already in use in the system, it is the application's responsibility to perform any necessary context save/restore necessary for the core/IP.

## Features Supported

The PBIST Module of the SDL supports execution of the software-initiated PBIST for the various supported instances. It provides the following services:

* Execution of the PBIST test for a specified instance
* Checking of the PBIST results
* Restore core to system control (PBIST reset and release test mode)
* Return the status of the test

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- Execution of the PBIST tests requires preparation of the IPs under test by bringing them to a certain power and reset state before executing the test. It will be required that the application bring the cores/IPs to the proper state before executing the PBIST. Additionally, there is an "exit sequence" that is required to bring the cores/IPs back to the system control after the PBIST test is executed. This will also be the responsibility of the application. The PBIST examples provided with SDL will give the necessary sequences, which can be used by the application for implementing the sequence.
- The PBIST module uses ESM events to detect completion of the test. The application should not enable these events through SDL_ESM_init in order to prevent interference with the test execution.

## Profiling Data
\cond SOC_AM62X
<table>
  <tr>
    <th>PBIST Instance</th>
    <th>Negative Test Time</th>
    <th>Positive Test Time</th>
    <th>Total Test Time</th>
  </tr>
  <tr>
    <td>GPU</td>
    <td>375 us</td>
    <td>3101 us</td>
    <td>3476 us</td>
  </tr>
  <tr>
    <td>MPU</td>
    <td>523 us</td>
    <td>35350 us</td>
    <td>35873 us</td>
  </tr>
  <tr>
    <td>MAIN</td>
    <td>1572 us</td>
    <td>23279 us</td>
    <td>24851 us</td>
  </tr>
  <tr>
    <td>**All instances**</td>
    <td>**2470 us**</td>
    <td>**61730 us**</td>
    <td>**64200 us**</td>
  </tr>
</table>
\note The above numbers were obtained in the m4fss0-0_nortos setting
\endcond
\cond SOC_AM62PX
<table>
  <tr>
    <th>PBIST Instance</th>
    <th>Negative Test Time</th>
    <th>Positive Test Time</th>
    <th>Total Test Time</th>
  </tr>
  <tr>
    <td>A53 MPU CLUSTER0</td>
    <td>1418 us</td>
    <td>39232 us</td>
    <td>40650 us</td>
  </tr>
  <tr>
    <td>CODEC PBIST3</td>
    <td>171 us</td>
    <td>9238 us</td>
    <td>9409 us</td>
  </tr>
  <tr>
    <td>PBIST1</td>
    <td>1066 us</td>
    <td>17519 us</td>
    <td>18585 us</td>
  </tr>
  <tr>
    <td>WKUP_PBIST1</td>
    <td>490 us</td>
    <td>28992 us</td>
    <td>29482 us</td>
  </tr>
  <tr>
    <td>PBIST_GPU</td>
    <td>417 us</td>
    <td>11042 us</td>
    <td>11459 us</td>
  </tr>
  <tr>
    <td>MAIN PBIST0</td>
    <td>1600 us</td>
    <td>14180 us</td>
    <td>15780 us</td>
  </tr>
  <tr>
    <td>**All instances**</td>
    <td>**5162 us**</td>
    <td>**120203 us**</td>
    <td>**125365 us**</td>
  </tr>
</table>
\note The above numbers were obtained in the mcu-r5fss0-0_nortos setting
\endcond
\cond SOC_AM62AX
<table>
  <tr>
    <th>PBIST Instance</th>
    <th>Negative Test Time</th>
    <th>Positive Test Time</th>
    <th>Total Test Time</th>
  </tr>
  <tr>
    <td>A53 MPU CLUSTER0</td>
    <td>351 us</td>
    <td>35120 us</td>
    <td>35471 us</td>
  </tr>
  <tr>
    <td>CODEC PBIST3</td>
    <td>212 us</td>
    <td>11390 us</td>
    <td>11602 us</td>
  </tr>
  <tr>
    <td>C7X256V0 PBIST</td>
    <td>216 us</td>
    <td>14616 us</td>
    <td>14832 us</td>
  </tr>
  <tr>
    <td>VPAC INST</td>
    <td>124 us</td>
    <td>30099 us</td>
    <td>30223 us</td>
  </tr>
  <tr>
    <td>MAIN PBIST0</td>
    <td>1004 us</td>
    <td>15857 us</td>
    <td>16861 us</td>
  </tr>
  <tr>
    <td>**All instances**</td>
    <td>**1907 us**</td>
    <td>**107082 us**</td>
    <td>**108989 us**</td>
  </tr>
</table>
\note The above numbers were obtained in the mcu-r5fss0-0_nortos setting
\endcond
\cond SOC_AM62DX
<table>
  <tr>
    <th>PBIST Instance</th>
    <th>Negative Test Time</th>
    <th>Positive Test Time</th>
    <th>Total Test Time</th>
  </tr>
  <tr>
    <td>A53 MPU CLUSTER0</td>
    <td>339 us</td>
    <td>35129 us</td>
    <td>35468 us</td>
  </tr>
  <tr>
    <td>C7X256V0 PBIST</td>
    <td>220 us</td>
    <td>12454 us</td>
    <td>12674 us</td>
  </tr>
  <tr>
    <td>MAIN PBIST0</td>
    <td>1039 us</td>
    <td>15890 us</td>
    <td>16929 us</td>
  </tr>
  <tr>
    <td>**All instances**</td>
    <td>**1598 us**</td>
    <td>**63473 us**</td>
    <td>**65071 us**</td>
  </tr>
</table>
\note The above numbers were obtained in the mcu-r5fss0-0_nortos setting
\endcond
\cond SOC_AM275X
<table>
  <tr>
    <th>PBIST Instance</th>
    <th>Negative Test Time</th>
    <th>Positive Test Time</th>
    <th>Total Test Time</th>
  </tr>
  <tr>
    <td>Pulsar1</td>
    <td>524 us</td>
    <td>877 us</td>
    <td>1401 us</td>
  </tr>
  <tr>
    <td>C7X0</td>
    <td>358 us</td>
    <td>5646 us</td>
    <td>6004 us</td>
  </tr>
  <tr>
    <td>C7X1</td>
    <td>355 us</td>
    <td>5647 us</td>
    <td>6002 us</td>
  </tr>
  <tr>
    <td>DM2</td>
    <td>76 us</td>
    <td>765 us</td>
    <td>841 us</td>
  </tr>
  <tr>
    <td>Main IP</td>
    <td>1022 us</td>
    <td>1643 us</td>
    <td>2665 us</td>
  </tr>
  <tr>
    <td>**All instances**</td>
    <td>**2335 us**</td>
    <td>**14578 us**</td>
    <td>**16913 us**</td>
  </tr>
</table>
\note The above numbers were obtained in the r5fss0-0_nortos setting
\endcond

## Example Usage

The following shows an example of SDL PBIST API usage by the application to execute the PBIST test and test-for-diagnostic.

Include the below file to access the APIs

\code{.c}
#include <sdl/sdl_pbist.h>
\endcode

Note: Do not initialize the ESM to detect PBIST completion events

Before executing the following PBIST tests, the IP under test must be brought to a certain power and reset state. The included PBIST example shows the sequence needed for each of the PBIST instances.

Once the core(s) are brought to the required state, the following APIs can be run.

Run the PBIST test-for-diagnostic:

\code{.c}

bool PBISTResult;

status = SDL_PBIST_selfTest(SDL_PBIST_INST_MPU, SDL_PBIST_NEG_TEST, timeoutVal, &PBISTResult);
if ((status != SDL_PASS) || (PBISTResult == false))
{
    // test failed
}

\endcode

Perform the PBIST test

\code{.c}

bool PBISTResult;

status = SDL_PBIST_selfTest(SDL_PBIST_INST_MPU, SDL_PBIST_TEST, timeoutVal, &PBISTResult);
if ((status != SDL_PASS) || (PBISTResult == false))
{
    // test failed
}

\endcode

## API

\ref SDL_PBIST_MODULE