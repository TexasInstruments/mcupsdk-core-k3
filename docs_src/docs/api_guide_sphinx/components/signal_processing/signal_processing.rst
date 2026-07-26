Signal Processing
===================

.. toctree::
   :maxdepth: 1
   :hidden:

   calcratio

Introduction
------------

This module contains APIs for signal processing applications supported on |VAR_SOC_NAME|.

It consists of below sub-modules:

.. only:: SOC_AM62DX or SOC_AM275X

   - :doc:`CALCRATIO <calcratio>`

XLIB supported by C7X
----------------------

.. list-table::
   :header-rows: 1

   * - Library
     - Description
   * - AUDIOLIB
     - AUDIOLIB is a software library implementing low-level Audio related Digital Signal Processing (DSP) functions using the C7x ISA.
   * - DSPLIB
     - DSPLIB is a software library implementing low-level Digital Signal Processing (DSP) functions using the C7x ISA.
   * - FFTLIB
     - FFTLIB implements low-level Fast Fourier Transform (FFT) functions using the MMA and C7x ISA.
   * - MATHLIB
     - MATHLIB implements various math operators such as trigonometric, power, exponent, utilizing C7x ISA.
   * - VXLIB
     - VXLIB implements low-level image processing functions using the C7x ISA.
   * - TISP
     - TISP (TI Signal Processing) abstracts the software and hardware complexity of programming the C7x.
