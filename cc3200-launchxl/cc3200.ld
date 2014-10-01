/*****************************************************************************
* freertos_demo.ld
*
* GCC Linker script for the CC3200
*
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

MINIMUM_HEAP_SIZE  = 16K;
MINIMUM_STACK_SIZE = 2K;

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x20004000, LENGTH = 0x00030000
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.intvecs))
        *(.text*)
        *(.rodata*)
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(8);
        _etext = .;
    } > SRAM

    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
    } > SRAM

    __init_data = .;

    .data : AT(__init_data)
    {
        _data = .;
        *(.data*)
    . = ALIGN (8);
        _edata = .;
    } > SRAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
  
    /* This is to define the start of the heap, and make sure we have a minimum size */
    .heap :
    {
        . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
        _heap_start = .;    /* define a global symbol at heap start */
        . = . + MINIMUM_HEAP_SIZE;
    } > SRAM

    /* This just checks there is enough RAM for the stack */
    .stack :
    {
        . = ALIGN(4);
        . = . + MINIMUM_STACK_SIZE;
        . = ALIGN(4);
    } > SRAM
}