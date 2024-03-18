#  Safety Checkers Library {#EXAMPLES_SAFETY_CHECKERS}

The high-level design of the Safety checker implementation for the TIFS, RM and PM module. The primary objective of implementing the safety checker is to make sure the detection of the failure modes for TIFS, RM and PM module are handled properly. Also providing the safety examples as a reference which calls the checker APIs to verify the module operations are done properly during the boot.

This page lists all the examples used to demonstrate the usage of productized SC library APIs.

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX
-# RM Safety Checkers
  -# \subpage EXAMPLES_RM_CHECKERS_APP
-# PM Safety Checkers
  -# \subpage EXAMPLES_PM_CHECKERS_APP
  -# \subpage EXAMPLES_PM_CHECKERS_WARM_RESET
-# TIFS Safety Checkers
  -# \subpage EXAMPLES_SAFETY_CHECKERS_TIFS
-# Safety Checkers App
  -# \subpage EXAMPLES_SAFETY_APP
\endcond
