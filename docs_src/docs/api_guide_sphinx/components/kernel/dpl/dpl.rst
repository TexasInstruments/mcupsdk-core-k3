Driver Porting Layer (DPL)
============================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   HwiP
   SemaphoreP
   TaskP
   ClockP
   CycleCountP
   QueueP
   CacheP
   CpuIdP
   MpuP_arm_v7
   MmuP_arm_v8
   AddrTranslateP
   HeapP
   DebugP
   EventP
   TimerP

This module contains APIs which are used by the drivers to make them agnostic of the underlying OS and CPU architecture.

It consists of below sub-modules

- :doc:`HW Interrupts <HwiP>` - APIs for HW Interrupts
- :doc:`Semaphore <SemaphoreP>` - APIs for Semaphore
- :doc:`Task <TaskP>` - APIs for Task
- :doc:`Clock <ClockP>` - APIs for Clock
- :doc:`Cycle Counter <CycleCountP>` - APIs for Counting CPU Cycles
- :doc:`Queue <QueueP>` - APIs for Queue

.. only:: SOC_AM64X or SOC_AM243X or SOC_AM273X or SOC_AWR294X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X

   - :doc:`Cache <CacheP>` - APIs for Cache
   - :doc:`CPUID for ARMv7 (ARM R5) <CpuIdP>` - APIs for CPU ID
   - :doc:`MPU for ARMv7 (ARM R5) <MpuP_arm_v7>` - APIs for MPU for ARMv7 (ARM R5, ARM M4)

.. only:: SOC_AM64X or SOC_AM62AX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM62LX

   - :doc:`MMU for ARMv8 (ARM A53, TI C75) <MmuP_arm_v8>` - APIs for system level define's and function's

.. only:: SOC_AM62LX

   - :doc:`Cache <CacheP>` - APIs for Cache

.. only:: SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

   - :doc:`Region based Address Translate <AddrTranslateP>` - APIs for Region based address translation (RAT) module

- :doc:`Heap <HeapP>` - APIs for Heap management
- :doc:`Debug <DebugP>` - APIs for Debug log's and assert's
- :doc:`Event <EventP>` - APIs for Event
- :doc:`Timer <TimerP>` - APIs for timer setup and control
