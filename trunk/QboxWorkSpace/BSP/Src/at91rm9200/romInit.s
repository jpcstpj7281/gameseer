/*
 *  armboot - Startup Code for ARM920 CPU-core
 *
 *  Copyright (c) 2001	Marius Gröger <mag@sysgo.de>
 *  Copyright (c) 2002	Alex Züpke <azu@sysgo.de>
 *  Copyright (c) 2002	Gary Jennejohn <gj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#define	_ASMLANGUAGE
#include "vxWorks.h"
#include "sysLib.h"
#include "asm.h"
#include "regs.h"	
#include "config.h"
#include "arch/arm/mmuArmLib.h"
 
    .data
    .globl   VAR(copyright_wind_river)
    .long    VAR(copyright_wind_river)

/* internals */

	.globl	FUNC(romInit)		/* start of system code */
	.globl	VAR(sdata)		/* start of data */
	.globl  _sdata


/* externals */
 
	.extern	FUNC(romStart)	/* system initialization routine */





_sdata:
VAR_LABEL(sdata)
	.asciz	"start of data"
	.balign	4

/* variables */

	.data



	.text
	.balign 4



/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */



/* flash */
#define MC_PUIA		0xFFFFFF10
#define MC_PUP		0xFFFFFF50
#define MC_PUER		0xFFFFFF54
#define MC_ASR		0xFFFFFF04
#define MC_AASR		0xFFFFFF08
#define EBI_CFGR	0xFFFFFF64
#define SMC0_CSR	0xFFFFFF70
#define SMC1_CSR	0xFFFFFF74
#define SMC2_CSR	0xFFFFFF78
#define SMC3_CSR	0xFFFFFF7C


/* clocks */
#define PLLAR		0xFFFFFC28
#define PLLBR		0xFFFFFC2C
#define MCKR		0xFFFFFC30

#define AT91C_BASE_CKGR 0xFFFFFC20
#define CKGR_MOR 0

/* sdram */
#define PIOC_ASR	0xFFFFF870
#define PIOC_BSR	0xFFFFF874
#define PIOC_PDR	0xFFFFF804
#define EBI_CSA		0xFFFFFF60
#define SDRC_CR		0xFFFFFF98
#define SDRC_MR		0xFFFFFF90
#define SDRC_TR		0xFFFFFF94



.globl _start


_ARM_FUNCTION(romInit)
_romInit:
_start:	
	ldr	pc, _start_reset
	ldr	pc, _start_warm
	B .
	B .
	B .
	B .
	B .
	B .
 
	/*.balignl 16,0xdeadbeef*/
	/* copyright notice appears at beginning of ROM (in TEXT segment) */

    /*bootrom version */
    .ascii  "010104"
    .ascii  "BootRom"
	.ascii   "Copyright 1999-2001 ARM Limited"
	.ascii   "\nCopyright 1999-2001 Wind River Systems, Inc."
	.balign 4

/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */


.globl _armboot_start
_armboot_start:
	.word _start


/*
 * the actual reset code
 */

reset:
    /*
    mov r0, #0X0
    ldr r1, =0x55AA55AA 
    str r1, [r0]
    ldr r3, [r0]
    cmp r1, r3 
    beq warm */ /*remap the memory*/

    mov r0, #0xFFFFFF00    
    mov r1, #0x00000001
    str r1, [r0]
    bl  cpu_init_crit

	ldr	r0, __boot_Mtest
	
	sub	sp, r0, #12		/* leave 3 words for abort-stack    */

	bl	BootTest

    mov r0, #BOOT_COLD  /* fall through to warm boot entry */



	/*
	 * set the cpu to SVC32 mode
	 */
	/*we are in CS0 now ,remap*/
	


warm:
    mov r8,r0   

	MRS	r1, cpsr	
	BIC	r1, r1, #MASK_MODE	
	ORR	r1, r1, #MODE_SVC32 | I_BIT | F_BIT	
	MSR	cpsr, r1

	ldr r1, =0xFFFFF124
	ldr r2, =0xffffffff
	str r2,[r1]


    
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */
	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0




	ldr	r0, __boot_stack
	
	sub	sp, r0, #12		/* leave 3 words for abort-stack    */


	MOV	r0, r8 
	
	ldr	pc, _start_armboot

_start_armboot:	 .word  ROM_TEXT_ADRS + FUNC(romStart) - FUNC(romInit)
_start_SMRDATA:  .word	ROM_TEXT_ADRS +	SMRDATA -FUNC(romInit)
_start_SMRDATA1: .word	ROM_TEXT_ADRS + SMRDATA1 -FUNC(romInit)
_start_reset: 	 .word	ROM_TEXT_ADRS + reset -FUNC(romInit)
_start_warm:	 .word	ROM_TEXT_ADRS + warm -FUNC(romInit)

	

__boot_stack:	
		.word 	0x20000f00
__boot_Mtest:   
        .word   0x00204000
        


/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */


cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */
	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0


	/*
	 * before relocating, we have to setup RAM timing
	 * because memory timing is board-dependend, you will
	 * find a lowlevel_init.S in your board directory.
	 */
	mov	ip, lr
	bl	lowlevel_init
	mov	lr, ip

	mov	pc, lr


.globl lowlevel_init

lowlevel_init:
	/* Get the CKGR Base Address */
	ldr     r1, =AT91C_BASE_CKGR
	/* Main oscillator Enable register */
#ifdef CFG_USE_MAIN_OSCILLATOR
	ldr     r0, =0x0000FF01		/* Enable main oscillator,  OSCOUNT = 0xFF */
#else
	ldr     r0, =0x0000FF00		/* Disable main oscillator, OSCOUNT = 0xFF */
#endif
	str     r0, [r1, #CKGR_MOR]
	/* Add loop to compensate Main Oscillator startup time */
	ldr     r0, =0x00000010
LoopOsc:
	subs    r0, r0, #1
	bhi     LoopOsc

	/* memory control configuration */
	/* this isn't very elegant, but	 what the heck */
	ldr	r0, _start_SMRDATA
	add	r2, r0, #88
0:
	/* the address */
	ldr	r1, [r0], #4
	/* the value */
	ldr	r3, [r0], #4
	str	r3, [r1]
	cmp	r2, r0
	bne	0b
	/* delay - this is all done by guess */
	ldr	r0, =0x00010000
1:
	subs	r0, r0, #1
	bhi	1b
	ldr r0, _start_SMRDATA1
	add	r2, r0, #176
2:
	/* the address */
	ldr	r1, [r0], #4
	/* the value */
	ldr	r3, [r0], #4
	str	r3, [r1]
	cmp	r2, r0
	bne	2b

	/* everything is fine now */
	mov	pc, lr

	.ltorg

SMRDATA:
	.word MC_PUIA
	.word MC_PUIA_VAL
	.word MC_PUP
	.word MC_PUP_VAL
	.word MC_PUER
	.word MC_PUER_VAL
	.word MC_ASR
	.word MC_ASR_VAL
	.word MC_AASR
	.word MC_AASR_VAL
	.word EBI_CFGR
	.word EBI_CFGR_VAL
	.word SMC0_CSR
	.word SMC0_CSR_VAL
	.word SMC2_CSR
	.word SMC2_CSR_VAL
	.word PLLAR
	.word PLLAR_VAL
	.word PLLBR
	.word PLLBR_VAL
	.word MCKR
	.word MCKR_VAL
	/* SMRDATA is 80 bytes long */
	/* here there's a delay of 100 */
SMRDATA1:
	.word PIOC_ASR
	.word PIOC_ASR_VAL
	.word PIOC_BSR
	.word PIOC_BSR_VAL
	.word PIOC_PDR
	.word PIOC_PDR_VAL
	.word EBI_CSA
	.word EBI_CSA_VAL
	.word SDRC_CR
	.word SDRC_CR_VAL
	.word SDRC_MR
	.word SDRC_MR_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRC_MR
	.word SDRC_MR_VAL1
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRC_MR
	.word SDRC_MR_VAL2
	.word SDRAM1
	.word SDRAM_VAL
	.word SDRC_TR
	.word SDRC_TR_VAL
	.word SDRAM
	.word SDRAM_VAL
	.word SDRC_MR
	.word SDRC_MR_VAL3
	.word SDRAM
	.word SDRAM_VAL
	/* SMRDATA1 is 176 bytes long */
