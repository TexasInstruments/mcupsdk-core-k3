# Safety Checkers Libaray {#SAFETY_CHECKERS_PAGE}

[TOC]
# Introduction

The @VAR_SOC_NAME family of SoCs provides various safety mechanisms and features, as well as recommendations for usage of these safety mechanisms and features. The Safety Checkers Library provides productized APIs for ensuring the safety of TIFS, RM and PM modules. SC provides these interfaces to assist in the development of software applications involving Functional Safety.

The high-level design of the Safety checker implementation for the TIFS, RM and PM module. The primary objective of implementing the safety checker is to make sure the detection of the failure modes for TIFS, RM and PM module are handled properly. Also providing the safety examples as a reference which calls the checker APIs to verify the module operations are done properly during the boot.

\imageStyle{Safety_Checkers.png,width:50%}
\image html Safety_Checkers.png "Safety Checkers Diagram"

SC consists of below sub-modules

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX
- \subpage SAFETY_CHECKERS_PM_PAGE
- \subpage SAFETY_CHECKERS_RM_PAGE
- \subpage SAFETY_CHECKERS_TIFS_PAGE
\endcond
