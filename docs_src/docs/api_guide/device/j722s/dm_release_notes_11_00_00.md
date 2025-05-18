# Release Notes 11.00.00 {#DM_RELEASE_NOTES_11_00_00_PAGE}

[TOC]

## Introduction

This release note provides important information about the features and bug fixes in the DM in the MCU+SDK software package for the J722S device.  
This document provides the product information and known issues that are specific to the DM present in MCU+SDK software package.  
   
New features added / supported is listed below and defects fixed are highlighted in **Fixed Issues**. Also please check **Upgrade and Compatibility** for backward compatibility.

## What's New

ID              | Description                                                                      | Module          | Supported Platforms                 
----------------|----------------------------------------------------------------------------------|-----------------|-------------------------------------
SYSFW-7448      | Add feature to show DM version                                                   | SCICLIENT       | J722s                                   

## Upgrade and Compatibility

### PSC
Sciclient_pmGetModuleState() API had a bug where it was reading LPSC control registers to check the status. This bug has been fixed SYSFW-7781 and API is updated to read status registers.

## Device and Validation Information

Refer **Device and Validation Information** in \ref RELEASE_NOTES_11_00_00_PAGE for Device and Validation Information

## Dependent Tools and Compiler Information

Refer **Dependent Tools and Compiler Information** in \ref RELEASE_NOTES_11_00_00_PAGE for Dependent Tools and Compiler Information

## Fixed Issues

ID              | Description                                                                      | Module          | Supported Platforms                 
----------------|----------------------------------------------------------------------------------|-----------------|-------------------------------------
SYSFW-8028      | Enable C7x Frequency change on J722S                                             | PM              | J722s                                
SYSFW-7922      | Main domain reset results in failure                                             | PM              | J722s                                
SYSFW-7781      | Get device API does not return error when the LPSC is in transition state        | PM              | J722s                                

## Known Issues

NA


## Limitations

There are no known limitations for DM.   

Refer **Limitations** in \ref RELEASE_NOTES_11_00_00_PAGE for other limitations.
