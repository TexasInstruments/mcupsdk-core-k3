# Release Notes 11.02.00 {#DM_RELEASE_NOTES_11_02_00_PAGE}

[TOC]

## Introduction

This release note provides important information about the features and bug fixes in the DM in the MCU+SDK software package for the J722S device.
This document provides the product information and known issues that are specific to the DM present in MCU+SDK software package.

New features added / supported is listed below and defects fixed are highlighted in **Fixed Issues**. Also please check **Upgrade and Compatibility** for backward compatibility.

## What's New

ID              | Description                                                                      | Module          | Supported Platforms
----------------|----------------------------------------------------------------------------------|-----------------|-------------------------------------
SYSFW-9173      | Enable LPM capabilities for J722S and J721S2                                     | LPM             | J722s
SYSFW-9142      | Add IRQ_CONTEXT_LOST and CLK_CONTEXT_LOST firmware capability                    | LPM             | J722s

## Upgrade and Compatibility

Replaced SystemP return types with CSL return types in the Sciclient_service API for the sciclient driver running on the WKUP R5 core. The Sciclient_service API in the sciclient driver running on other cores remains unchanged.

Sr No. | Return cases                                | SystemP return type | Updated CSL return type
-------|---------------------------------------------|---------------------|------------------------
1      | Sciclient_service API receives invalid agrs | SystemP_FAILURE     | CSL_EBADARGS
2      | Sciclient_service API process timeout       | SystemP_TIMEOUT     | CSL_ETIMEOUT

## Device and Validation Information

Refer **Device and Validation Information** in \ref RELEASE_NOTES_11_02_00_PAGE for Device and Validation Information

## Dependent Tools and Compiler Information

Refer **Dependent Tools and Compiler Information** in \ref RELEASE_NOTES_11_02_00_PAGE for Dependent Tools and Compiler Information

## Fixed Issues

There are no issues identified and fixed in this release

## Known Issues

NA


## Limitations

There are no known limitations for DM.

Refer **Limitations** in \ref RELEASE_NOTES_11_02_00_PAGE for other limitations.
