Safety Checkers Library
=========================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   safety_checkers_pm
   safety_checkers_rm
   safety_checkers_tifs
   safety_app

The |VAR_SOC_NAME| family of SoCs provides various safety mechanisms and features, as well as recommendations for usage of these safety mechanisms and features. The Safety Checkers Library provides productized APIs for ensuring the safety of TIFS, RM and PM modules. SC provides these interfaces to assist in the development of software applications involving Functional Safety.

The high-level design of the Safety checker implementation for the TIFS, RM and PM module. The primary objective of implementing the safety checker is to make sure the detection of the failure modes for TIFS, RM and PM module are handled properly. Also providing the safety examples as a reference which calls the checker APIs to verify the module operations are done properly during the boot.

.. image:: ../../images/safety_checkers/Safety_Checkers.png
   :alt: Safety Checkers Diagram

SC consists of below sub-modules

.. only:: SOC_AM62X or SOC_AM62AX or SOC_AM62PX

   - :doc:`PM_SAFETY_CHECKERS <safety_checkers_pm>`
   - :doc:`RM_SAFETY_CHECKERS <safety_checkers_rm>`
   - :doc:`TIFS_SAFETY_CHECKERS <safety_checkers_tifs>`

Following example demonstrates the usage of RM, PM and TIFS safety checkers.

.. only:: SOC_AM62X or SOC_AM62AX or SOC_AM62PX

   - :doc:`SAFETY_APP <safety_app>`

Safety Modules API Reference:

- :doc:`PM Safety Checkers <safety_checkers_pm>` - PM Safety Checkers Library
- :doc:`RM Safety Checkers <safety_checkers_rm>` - RM Safety Checkers Library
- :doc:`TIFS Safety Checkers <safety_checkers_tifs>` - TIFS Safety Checkers Library
