# Security {#SECURITY_PAGE}

[TOC]

# Introduction

This page links to sub modules that enable data authentication, integrity and confidentiality.

Security on this device is ensured via the following features:
\cond SOC_AM64X || SOC_AM243X
- Cryptography Services
    - \subpage SECURITY_SA2UL_MODULE_PAGE (Ultra lite Security Accelerator)
        - Description of SA2UL architecture and APIs available to use AES, SHA and RNG engine.
    - \subpage SECURITY_PKA_MODULE_PAGE (Public key accelerator)
        - Description of PKA engine and APIs available to use it.
\endcond
\cond SOC_AM62AX
- Cryptography Services
    - \subpage SECURITY_SA3UL_MODULE_PAGE (Ultra lite Security Accelerator)
        - Description of SA3UL architecture and APIs available to use AES, SHA and RNG engine.
\endcond