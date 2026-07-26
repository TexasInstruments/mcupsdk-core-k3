Safety Checkers Library
=========================

.. toctree::
   :maxdepth: 2
   :hidden:
   :titlesonly:

   safety_checkers/rm_checkers_app
   safety_checkers/pm_checkers_app
   safety_checkers/pm_checkers_warm_reset
   safety_checkers/tifs-safety_checkers
   safety_checkers/safety_app

The high-level design of the Safety checker implementation for the TIFS, RM and PM module. The primary objective of implementing the safety checker is to make sure the detection of the failure modes for TIFS, RM and PM module are handled properly. Also providing the safety examples as a reference which calls the checker APIs to verify the module operations are done properly during the boot.

This page lists all the examples used to demonstrate the usage of productized SC library APIs.

.. only:: SOC_AM62X or SOC_AM62AX or SOC_AM62PX

   **RM Safety Checkers**
      - :doc:`RM SAFETY CHECKERS APP <safety_checkers/rm_checkers_app>`

   **PM Safety Checkers**
      - :doc:`PM SAFETY CHECKERS APP <safety_checkers/pm_checkers_app>`
      - :doc:`PM SAFETY CHECKERS WARM RESET <safety_checkers/pm_checkers_warm_reset>`

   **TIFS Safety Checkers**
      - :doc:`TIFS SAFETY CHECKERS APP <safety_checkers/tifs-safety_checkers>`

   **Safety Checkers App**
      - :doc:`SAFETY APP <safety_checkers/safety_app>`
