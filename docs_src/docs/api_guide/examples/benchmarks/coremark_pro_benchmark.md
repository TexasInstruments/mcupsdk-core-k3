# Coremark-Pro Benchmark {#EXAMPLES_COREMARK_PRO}

[TOC]

CoreMark®-PRO is a comprehensive, advanced processor benchmark that works with and enhances the market-proven industry-standard EEMBC CoreMark® benchmark.
While CoreMark stresses the CPU pipeline, CoreMark-Pro tests the entire processor, adding comprehensive support for multicore technology, a combination of integer and floating-point workloads, and data sets for utilizing larger memory subsystems.
The CoreMark-PRO benchmark contains five prevalent integer workloads and four popular floating-point workloads.


The integer workloads include:

* JPEG compression
* ZIP compression
* XML parsing
* SHA-256 Secure Hash Algorithm
* A more memory-intensive version of the original CoreMark (CORE)

The floating-point workloads include:

* Radix-2 Fast Fourier Transform (FFT)
* Gaussian elimination with partial pivoting derived from LINPACK
* A simple neural-net
* A greatly improved version of the Livermore loops benchmark using the following 24 FORTRAN kernels converted to C

Each workload must be compiled individual(as each workload uses different dataset), flashed to the device, verified, and then the score computed manually
The CoreMark-PRO score is a weighted geometric mean of each workload

All the workload applications are present in examples/benchmarks/coremark_pro_benchmark folder.

# Supported Combinations {#EXAMPLES_COREMARK_PRO_COMBOS}
\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/coremark_pro_benchmark

\endcond

\cond SOC_AM62LX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/coremark_pro_benchmark

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE


## Compute The Overall Score

The score for CoreMark-PRO is a scaled geometric mean of scaled workload scores. Each workload is
normalized to a reference value.

The overall score can be computed with the following steps:

- Change the working directory to `{SDK_PATH}/tools/coremarkPro_bechmark`.

- Run the following command with the score obtained from each workload to compute overall benchmark score

    \note Change the score according to the workload and use corresponding argument.(--args score)

    \code
         python3 coremarkPro.py --core .28 --cjpeg 40.40 --lin 16.30 --loops .71 --parser 5.75 --radix 77.54 --sha 81.72 --zip 27.13 --nnet 1.87
    \endcode

## Sample output for Coremark pro benchmark example

\cond SOC_AM62X
\code
-  Info: Starting Run...
-- Workload:linear_alg-mid-100x100-sp=1046644201
-- linear_alg-mid-100x100-sp:time(ns)=6134575
-- linear_alg-mid-100x100-sp:contexts=1
-- linear_alg-mid-100x100-sp:iterations=100
-- linear_alg-mid-100x100-sp:time(secs)= 6.13457
-- linear_alg-mid-100x100-sp:secs/workload=0.0613458
-- linear_alg-mid-100x100-sp:workloads/sec=  16.301
-- Done:linear_alg-mid-100x100-sp=1046644201
\endcode
\endcond

\cond SOC_AM62LX
\code
-  Info: Starting Run...
-- Workload:linear_alg-mid-100x100-sp=1046644201
-- linear_alg-mid-100x100-sp:time(ns)=6134575
-- linear_alg-mid-100x100-sp:contexts=1
-- linear_alg-mid-100x100-sp:iterations=100
-- linear_alg-mid-100x100-sp:time(secs)= 6.13457
-- linear_alg-mid-100x100-sp:secs/workload=0.0613458
-- linear_alg-mid-100x100-sp:workloads/sec=  16.301
-- Done:linear_alg-mid-100x100-sp=1046644201
\endcode
\endcond
