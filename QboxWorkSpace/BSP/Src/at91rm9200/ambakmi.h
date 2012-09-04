/* Copyright 1999-2000 Wind River Systems, Inc. All Rights Reserved */

/*
modification history
--------------------
01a,05jul01,m_h  Created
*/

/*
 * DESCRIPTION - Definitions for the AMBA PrimeCell KMI PS2
 *               Keyboard and mouse driver for ARM bsp's
 * 
 */

/* includes */
#include "tyLib.h"

#ifndef __INCambakmih
#define __INCambakmih

#if __cplusplus
extern "C"
{
#endif

#define USE_BSP_API

/* IOCTL codes */
#define CONIOCURCONSOLE     1009
#define CONIOCONVERTSCAN    1010
#define CONIOLEDS           1011

/* misc definitions */
#define WAIT_MAX        100     /* Maximum wait time for keyboard */

#define STP             0x0001  /* capslock flag */
#define NUM             0x0002  /* numeric lock flag */
#define CAPS            0x0004  /* scroll lock stop output flag */


#ifndef KBD_BASE_ADR
#define KBD_BASE_ADR      ambaKbdRegBase
#endif

#ifndef MOUSE_BASE_ADR
#define MOUSE_BASE_ADR    ambaMseRegBase
#endif

/* -------------------------------------------------------------------------------
 *  KMI keyboard/mouse definitions
 * -------------------------------------------------------------------------------
 */
/* PS2 Keyboard interface */

#define KMI0_BASE              KBD_BASE_ADR		
#define KEYB_CR                (KBD_BASE_ADR)
#define KEYB_STAT              (KBD_BASE_ADR + 0x4)
#define KEYB_DATA              (KBD_BASE_ADR + 0x8)
#define KEYB_CLK               (KBD_BASE_ADR + 0xC)

/* PS2 Mouse interface */
#define KMI1_BASE              MOUSE_BASE_ADR
#define MOUSE_CR               MOUSE_BASE_ADR
#define MOUSE_STAT             (MOUSE_BASE_ADR+0x4)
#define MOUSE_DATA             (MOUSE_BASE_ADR+0x8)
#define MOUSE_CLK              (MOUSE_BASE_ADR+0xC)

/* KMI_CR control register bits */
#define KMI_CR_FKMIC            0x01
#define KMI_CR_FKMID            0x02
#define KMI_CR_KMIEN            0x04
#define KMI_CR_TXIEN            0x08
#define KMI_CR_RXIEN            0x10
#define KMI_CR_TYPE             0x20

#define KMI_DIVISOR   0x02  /* 24Mhz->8MHz = div by 3  */

/* KMI interrupts */
/* Note: this stuff is also in integrator.h */
#define INT_LVL_KEYBOARD	3	/* keyboard interrupt */
#define INT_LVL_MOUSE		4	/* mouse interrupt */
#define INT_VEC_KEYBOARD	IVEC_TO_INUM(INT_LVL_KEYBOARD)
#define INT_VEC_MOUSE		IVEC_TO_INUM(INT_LVL_MOUSE)

#define KBD_OUT(addr, val)      *((volatile unsigned int *)addr) = (val)
#define KBD_IN(addr)            *((volatile unsigned int *)addr)
#define MS_OUT(addr, val)       *((volatile unsigned int *)addr) = (val)
#define MS_IN(addr)             *((volatile unsigned int *)addr)

#ifndef COMMAND_AMBA_KB
#define COMMAND_AMBA_KB        KEYB_CR
#define DATA_AMBA_KB           KEYB_DATA
#define STATUS_AMBA_KB         KEYB_STAT
#endif /* COMMAND_AMBAKMI */

#ifndef COMMAND_AMBA_MS
#define COMMAND_AMBA_MS        MOUSE_CR
#define DATA_AMBA_MS           MOUSE_DATA
#define STATUS_AMBA_MS         MOUSE_STAT
#endif /* COMMAND_AMBAKMI */

/* Following interrupt structure is specifically for the
 * integrator
 */
#ifndef MSE_INT_LVL
#define MSE_INT_LVL           INT_VEC_MOUSE
#endif /* MSE_INT_LVL */

#ifndef MSE_INT_VEC
#define MSE_INT_VEC           INUM_TO_IVEC(INT_VEC_MOUSE)
#endif /* MSE_INT_VEC */

#ifndef KBD_INT_LVL
#define KBD_INT_LVL           INT_VEC_KEYBOARD
#endif /* KBD_INT_LVL */

#ifndef KBD_INT_VEC
#define KBD_INT_VEC           INUM_TO_IVEC(INT_VEC_KEYBOARD)
#endif /* KBD_INT_VEC */

/* general KMI register macros */
#define KMI_CR(b)	((volatile unsigned int *)b) 
#define KMI_STAT(b)    ((volatile unsigned int *)(b+0x4))
#define KMI_DATA(b)    ((volatile unsigned int *)(b+0x8))
#define KMI_CLK(b)     ((volatile unsigned int *)(b+0xC))

/* KMI constants */
#define KMI_TXEMPTY                     0x40
#define KMI_TXBUSY                      0x20
#define KMI_RXFULL                      0x10
#define KMI_RXBUSY                      0x08
#define KMI_PARITY                      0x04

/* typedefs */
typedef struct
    {
    TY_DEV          ty_dev;
    } MSE_DEVICE;


/* pc console device descriptor */

typedef struct
    {
    TY_DEV  tyDev;
    UINT16  kbdFlags;       /* 16 bit keyboard flags */
    } KBD_DEVICE;

extern STATUS ambaKbdDevCreate(char *  name);
extern STATUS ambaKBWrite (unsigned char data);
extern STATUS ambaKBRead (unsigned char *data);
extern STATUS ambaKBCommand (unsigned char data);
extern STATUS kbdDevCreate(char *name);

extern STATUS ambaPs2DevCreate(char *  name);
extern STATUS ambaMsWrite (unsigned char data);
extern STATUS ambaMsRead (unsigned char *data);
extern STATUS ambaMsCommand (unsigned char data);

#if __cplusplus
} /* extern "C" */
#endif
#endif /* __INCambakmih */
