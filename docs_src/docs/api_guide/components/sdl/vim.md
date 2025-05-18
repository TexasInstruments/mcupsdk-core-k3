# VIM {#SDL_VIM_PAGE}

[TOC]

The Vectored Interrupt Manager (VIM) aggregates interrupts to a CPU. It is intended for use with a Cortex R5 from ARM in either split or lockstep configuration. The VIM has up to 1024 interrupt inputs per CPU, which may be either level or pulse. Each interrupt has a programmable priority (0-highest through 15-lowest). Each interrupt may also be mapped as anIRQ or FIQ (FIQ is also often denoted as Non-Maskable Interrupt, or NMI).

The file source/sdl/r5/v0/sdl_interrupt.c demonstrates using these APIs in a baremetal environment for interrupt-related functionality.


## Features Supported

 Safety diagnostics are provided for VIMDED module through API’s

1. Register VIMDED handler
2. Set VIMDED vector address
3. Get VIMDED vector address


## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

\code{.c}
#include <sdl/r5/v0/sdl_vim.h>
\endcode

This is function to be called when an Double bit ECC error
happens on the VIM RAM. NOTE: That the regular vector load
will be replaced with this registered function.

\code{.c}

void SDL_ECC_registerVIMDEDHandler(SDL_ECC_VIMDEDVector_t VIMDEDHandler)
{
    SDL_vimRegs     *pVimRegs;

    /* initialize the address */
    pVimRegs        = (SDL_vimRegs *)(SDL_MCU_R5FSS0_VIC_CFG_BASE);

    SDL_VIM_setDedVectorAddr(pVimRegs, (uint32_t)VIMDEDHandler);
}
\endcode

Set the DED interrupt vector address

\code{.c}
void SDL_VIM_setDedVectorAddr( SDL_vimRegs *pRegs, uint32_t dedVectorAddr )
{
    void       *pChkRegs = (void *) pRegs;

    if (pChkRegs != SDL_MCU_ARMSS_VIM_NULL_ADDR)
    {
        SDL_REG32_WR( &pRegs->DEDVEC, (dedVectorAddr & SDL_VIM_DEDVEC_ADDR_MASK) );
    }
}
\endcode

Get the DED interrupt vector address

\code{.c}
int32_t SDL_VIM_getDedVectorAddr( SDL_vimRegs *pRegs, uint32_t *pDedVectorAddr )
{
    int32_t     retVal = SDL_PASS;
    uint32_t    dedVecAddr;
    void       *pChkDedVecAddr = (void *) pDedVectorAddr;
    void       *pChkRegs = (void *) pRegs;
    if ( (pChkRegs == SDL_MCU_ARMSS_VIM_NULL_ADDR) ||
         (pChkDedVecAddr == SDL_MCU_ARMSS_VIM_NULL_ADDR))
    {
        retVal = SDL_EFAIL;
    }

    if (retVal == SDL_PASS)
    {
        dedVecAddr = SDL_REG32_RD( &pRegs->DEDVEC);
       *pDedVectorAddr = dedVecAddr;
    }
    return (retVal);
}
\endcode


## API
\ref SDL_VIM_API