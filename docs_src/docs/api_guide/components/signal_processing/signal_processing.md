# Signal Processing {#SIGNAL_PROCESSING_PAGE}

[TOC]

# Introduction

This module contains APIs for signal processing application that are supported on @VAR_SOC_NAME.

It consists of below sub-modules


\cond SOC_AM275X
- \subpage SW_CALCRATIO_PAGE
\endcond

\cond SOC_AM62DX
- \subpage SW_CALCRATIO_PAGE
\endcond

\cond SOC_AM62DX || SOC_AM275X
## XLIB supported by C7X
<table>
<tr>
    <th>library
    <th>Description
</tr>
<tr>
    <td>[AUDIOLIB](audiolib_docs/user_guide/index.html)
    <td>AUDIOLIB is a software library implementing low-level Audio related Digital Signal Processing (DSP) functions using the C7x ISA available on TI's Keystone 3 devices.
</tr>
<tr>
    <td>[DSPLIB](dsplib_docs/user_guide/index.html)
    <td>DSPLIB is a software library implementing low-level Digital Signal Processing (DSP) functions using the C7x ISA available on TI's Keystone 3 devices.
</tr>
<tr>
    <td>[FFTLIB](fftlib_docs/user_guide/index.html)
    <td>FFTLIB is the software library implementing low-level Fast Fourier Transform (FFT) functions using the Matrix Multiplication Accelerator (MMA) and C7x ISA available on TI's Keystone 3 devices.
</tr>
<tr>
    <td>[MATHLIB](mathlib_docs/user_guide/index.html)
    <td>MATHLIB is a low-level C7x software library that implements various math operators such as trigonometric, power, exponent, utilizing C7x ISA available on TI's Keystone 3 devices.
</tr>
<tr>
    <td>[VXLIB](vxlib_docs/user_guide/index.html)
    <td>VXLIB is a software library implementing low-level image processing functions using the C7x ISA.
</tr>
<tr>
    <td>[TISP](tisp_docs/user_guide/index.html)
    <td>TISP (TI signal processing) is a software library that strives to abstract away the software and the hardware complexity of programming the C7x.
</tr>
</table>
\endcond
