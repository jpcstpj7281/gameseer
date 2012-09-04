/* pcic.c - Intel 82365SL PCMCIA host bus adaptor chip library */

/* Copyright 1984-1996 Wind River Systems, Inc. */
/* Copyright (c) 1994 David A. Hinds -- All Rights Reserved */
#include "copyright_wrs.h"

/*
modification history
--------------------
01h,01apr98,hdn	 set PCIC_ENA_MEMCS16 if MAP_16BIT is specified.
01g,19jan98,hdn  removed taskDelay().
01f,01nov96,hdn  fixed PCIC_PORT().
01e,29mar96,jdi  doc: fixed error.
01d,28mar96,jdi  doc: cleaned up language and format.
01c,08mar96,hdn  added more descriptions.
01b,22feb96,hdn  cleaned up
01a,19jan95,hdn  written based on David Hinds's version 2.2.3.
*/


/*
DESCRIPTION
This library contains routines to manipulate the CompactFlash functions on the
AT91RM9200DK board.

The initialization routine pcicInit() is the only global function and is
included in the PCMCIA chip table `pcmciaAdapter'.  If pcicInit() finds
the PCIC chip, it registers all function pointers of the PCMCIA_CHIP
structure.

*/


#include "vxWorks.h"
#include "taskLib.h"
#include "intLib.h"
#include "sysLib.h"
#include "drv/pcmcia/pcmciaLib.h"
#include "drv/pcmcia/pcic.h"
#include "drv/pcmcia/pd67.h"
#include "drv/pcmcia/vg468.h"
#include "drv/pcmcia/ricoh.h"


/* defines */

#define PCIC_PORT(slot)		(pcicBase + (2*((slot) >> 2)))
#define PCIC_REG(slot, reg)	((((slot) & 3) * 0x40) + reg)


/* imports */

IMPORT PCMCIA_CTRL	pcmciaCtrl;


/* globals */

int pcicBase;


/* locals */

LOCAL SEMAPHORE	pcicMuteSem;
/*#include "at91_lowlevel.c"
#include "at91_pcmcia.c"*/
#include "at91_pcmcia.h"


struct irqs at91_pcmcia_irqs[] = {
	{ AT91C_ID_PIOB, AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2 | AT91C_CF_PB2_IOIS16 | AT91C_CF_PB3_STSCHG | AT91C_CF_PB4_RDY, "AT91 PCMCIA IRQ" },
};
static void at91_pcmcia_interrupt(int irq)
{

 
 if (AT91_SYS->PIOB_ISR & AT91_SYS->PIOB_IMR & at91_pcmcia_irqs[0].bits) /* debug only */
    {
    /*  udelay(100);
      DEBUG(3, "%s(): servicing IRQ %d\n", __FUNCTION__, irq);
      schedule_task(&at91_pcmcia_task);*/
      //at91_pcmcia_task_handler(0);
    }

    
}
static int at91_pcmcia_low_level_init()
{
	int ret = 0;
	unsigned long access;

	/* do the formalities */
	AT91_SYS->PIOC_PDR = AT91C_PC6_NWAIT | AT91C_PC7_A23 | AT91C_PC9_A25_CFRNW |
		AT91C_PC10_NCS4_CFCS | AT91C_PC11_NCS5_CFCE1 | AT91C_PC12_NCS6_CFCE2;
	AT91_SYS->PIOC_ASR = AT91C_PC6_NWAIT | AT91C_PC7_A23 | AT91C_PC9_A25_CFRNW |
		AT91C_PC10_NCS4_CFCS | AT91C_PC11_NCS5_CFCE1 | AT91C_PC12_NCS6_CFCE2;		/* set up for periph A */

	AT91_SYS->PIOB_PER = AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2 | AT91C_CF_PB2_IOIS16 | AT91C_CF_PB3_STSCHG
			| AT91C_CF_PB4_RDY | AT91C_CF_PB5_RESET | AT91C_CF_PB6_ENABLE;		/* enable the pio */
	AT91_SYS->PIOB_OER = AT91C_CF_PB5_RESET | AT91C_CF_PB6_ENABLE;		/* enable it */
	AT91_SYS->PIOB_CODR = AT91C_CF_PB5_RESET | AT91C_CF_PB6_ENABLE;		/* clear it */

	/* Setup Compact Flash, enable the address range of CS4 */

	AT91_SYS->EBI_CSA |= ((unsigned int) 0x1 <<  4) ; /*AT91C_EBI_CS4A_SMC_COMPACTFLASH;*/

#define SM_RWH	(4 << 28)	/* hold time, was 2 */
#define SM_RWS	(6 << 24)	/* setup time, was 6 */
#define SM_TDF	(1 << 8)	/* data float time, */
#define SM_NWS	(32)		/* wait states, NOTE: 0=1.5, 1=2.5, etc */

	/* debug only */
	access = (AT91_SYS->PIOB_PDSR & AT91C_CF_PB2_IOIS16) ? AT91C_SMC2_DBW_8 : AT91C_SMC2_DBW_16 | AT91C_SMC2_BAT;	/* access type (8 or 16-bit) */
	AT91_SYS->EBI_SMC2_CSR[4] = SM_RWH | SM_RWS | AT91C_SMC2_ACSS_STANDARD |
		AT91C_SMC2_DBW_16 | AT91C_SMC2_BAT | AT91C_SMC2_WSEN | SM_NWS;

	printk("AT91 CF driver v1.0\n");
#if 1

    intConnect(INT_VEC_PIOB, (VOIDFUNCPTR)at91_pcmcia_interrupt, 0);
    /* Disable interrupt. */
    intEnable(AT91C_ID_PIOB);		
			
#endif
/* socket init */
	AT91_SYS->PIOB_ODR = at91_pcmcia_irqs[0].bits;	/* disable output */
	access = AT91_SYS->PIOB_ISR;			/* read to reset int's for this port */
	AT91_SYS->PIOB_IER = at91_pcmcia_irqs[0].bits;	/* enable it */
	
	return ret ? -1 : AT91_PCMCIA_MAX_SOCK;		/* return the number of sockets */
}




/* forward declarations */

LOCAL STATUS	pcicReset	(int sock);
LOCAL int	pcicStatus	(int sock);
LOCAL int	pcicFlagGet	(int sock);
LOCAL STATUS	pcicFlagSet	(int sock, int flag);
LOCAL STATUS	pcicCscOn	(int sock, int irq);
LOCAL STATUS	pcicCscOff	(int sock, int irq);
LOCAL int	pcicCscPoll	(int sock);
LOCAL int	pcicIrqGet	(int sock);
LOCAL STATUS	pcicIrqSet	(int sock, int irq);
LOCAL STATUS	pcicIowinGet	(int sock, PCMCIA_IOWIN *io);
LOCAL STATUS	pcicIowinSet	(int sock, PCMCIA_IOWIN *io);
LOCAL STATUS	pcicMemwinGet	(int sock, PCMCIA_MEMWIN *mem);
LOCAL STATUS	pcicMemwinSet	(int sock, PCMCIA_MEMWIN *mem);
LOCAL int	pcicGet		(int sock, int reg);
LOCAL int	pcicGet2	(int sock, int reg);
LOCAL void	pcicSet		(int sock, int reg, char value);
LOCAL void	pcicSet2	(int sock, int reg, short value);
LOCAL void	pcicBset	(int sock, int reg, char mask);
LOCAL void	pcicBclr	(int sock, int reg, char mask);


/*******************************************************************************
*
* pcicInit - initialize the PCIC chip
*
* This routine initializes the PCIC chip.
*
* RETURNS: OK, or ERROR if the PCIC chip cannot be found.
*/

STATUS pcicInit
    (
    int	    ioBase,		/* IO base address */
    int	    intVec,		/* interrupt vector */
    int	    intLevel,		/* interrupt level */
    FUNCPTR showRtn		/* show routine */
    )
    {
    PCMCIA_CTRL *pCtrl	= &pcmciaCtrl;
    PCMCIA_CHIP *pChip	= &pCtrl->chip;
    BOOL done		= FALSE;
    int ix;
    int value;
    int sock;
 #ifdef   __DK__ 
    pcicBase = ioBase;
    at91_pcmcia_low_level_init();
/*    skt->irq        = irq_info.irq;
    skt->k_state    = state[i];
    skt->phys_attr  = AT91_PCMCIA_AT_BASE(i);
    skt->phys_mem   = AT91_PCMCIA_CM_BASE(i);
    skt->virt_io    = (void*) AT91_PCMCIA_IO_BASE(i) ; 
*/
        

    pChip->name = "AT91RM9200 CF" ;
    pChip->type = 0 ;
#if 0
    for (sock = 0; sock < PCIC_MAX_SOCKS; sock++)
	{
	value = pcicGet (sock, PCIC_IDENT);

	at91_pcmcia_init(sock);
	pChip->name = "AT91RM9200 CF" ;
	pChip->type = 0 ;

	
	    
	pcicSet (sock, PCIC_CSCINT, sock);
	}



    if (sock == 0)
	return (ERROR);
#endif
    semMInit (&pcicMuteSem, SEM_Q_PRIORITY | SEM_DELETE_SAFE | 
	      SEM_INVERSION_SAFE);
    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
#if 0
    /* Check for bogus clones that ignore top bit of index register */

    if ((sock == 4) && (pcicGet (0, PCIC_CSCINT) == 2))
	sock = 2;
    
    /* Check for Ricoh chips */

    value = pcicGet (0, RF5C_CHIP_ID);
    if ((value == RF5C_CHIP_RF5C296) || (value == RF5C_CHIP_RF5C396))
	{
	pChip->name = "RICOH Clone";
	pChip->type = PCIC_RICOH;
	}

    /* Check for Cirrus CL-PD67xx chips */

    pcicSet (0, PD67_CHIP_INFO, 0);
    value = pcicGet (0, PD67_CHIP_INFO);
    if ((value & PD67_INFO_CHIP_ID) == PD67_INFO_CHIP_ID)
	{
	value = pcicGet (0, PD67_CHIP_INFO);
	if ((value & PD67_INFO_CHIP_ID) == 0)
	    {
	    if (value & PD67_INFO_SLOTS)
		{
		pChip->name = "Cirrus CL-PD672x";
		pChip->type = PCIC_PD672X;
		}
	    else
		{
		pChip->name = "Cirrus CL-PD6710";
		pChip->type = PCIC_PD6710;
		sock = 1;
	        }
	    }
        }

    for (ix = 0; ix < sock; ix++)
	{
        pcicSet (sock, PCIC_CSCINT, 0);
        pcicSet (sock, PCIC_GENCTL, 0);
        pcicSet (sock, PCIC_GBLCTL, 0);
	}
   #endif 
    pChip->reset	= (FUNCPTR) pcicReset;
    pChip->status	= (FUNCPTR) pcicStatus;
    pChip->flagGet	= (FUNCPTR) pcicFlagGet;
    pChip->flagSet	= (FUNCPTR) pcicFlagSet;
    pChip->cscOn	= (FUNCPTR) pcicCscOn;
    pChip->cscOff	= (FUNCPTR) pcicCscOff;
    pChip->cscPoll	= (FUNCPTR) pcicCscPoll;
    pChip->irqGet	= (FUNCPTR) pcicIrqGet;
    pChip->irqSet	= (FUNCPTR) pcicIrqSet;
    pChip->iowinGet	= (FUNCPTR) pcicIowinGet;
    pChip->iowinSet	= (FUNCPTR) pcicIowinSet;
    pChip->memwinGet	= (FUNCPTR) pcicMemwinGet;
    pChip->memwinSet	= (FUNCPTR) pcicMemwinSet;
    pChip->type		= PCMCIA_PCIC;
    pChip->socks	= sock;
    pChip->installed	= TRUE;
    pChip->intLevel	= intLevel;
    pChip->memWindows	= PCIC_MEM_WINDOWS;
    pChip->ioWindows	= PCIC_IO_WINDOWS;
    pChip->showRtn	= showRtn;

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
#else
	return (ERROR);
#endif    
    }
  
/*******************************************************************************
*
* pcicStatus - Get status of the socket.
*
* This routine gets status of the socket.
* This routine can be called in interrupt level.
*
* RETURNS: The status of the socket.
*/

LOCAL int pcicStatus
    (
    int sock			/* socket no. */
    )
    {
    BOOL intMode	= intContext ();
    unsigned int status		= 0;
    char value;

    if (!intMode)
        semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
	
/*    at91_pcmcia_get_status(sock, &status);*/
    if (!(AT91_SYS->PIOB_PDSR & (AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2))) {
		status |=PC_IS_CARD|PC_POWERON|PC_DETECT ;
		
	}
	if( AT91F_CF_Card_OK()!=1) status=0;

	
#if 0	
    value  = pcicGet (sock, PCIC_STATUS);

    if ((value & PCIC_CS_DETECT) == PCIC_CS_DETECT)	/* CD1=1 and CD2=1 */
        status = PC_IS_CARD;

    if ((value & PCIC_CS_DETECT) != PCIC_CS_DETECT)	/* CD1=0 or CD2=0 */
        status = PC_NO_CARD;

    if (pcicGet (sock, PCIC_INTCTL) & PCIC_PC_IOCARD)
	status |= (value & PCIC_CS_STSCHG) ? 0 : PC_STSCHG;
    else
	{
	status |= (value & PCIC_CS_BVD1) ? 0 : PC_BATDEAD;
	status |= (value & PCIC_CS_BVD2) ? 0 : PC_BATWARN;
        }
    status |= (value & PCIC_CS_WRPROT) ? PC_WRPROT : 0;
    status |= (value & PCIC_CS_READY) ? PC_READY : 0;
    status |= (value & PCIC_CS_POWERON) ? PC_POWERON : 0;
#endif
    if (!intMode)
        semGive (&pcicMuteSem);		 	/* mutual execlusion stop */
	
    return (status);
    }

/*******************************************************************************
*
* pcicFlagGet - Get configuration flag from the socket.
*
* This routine gets configuration flag from the socket.
*
* RETURNS: The configuration flag of the socket.
*/

LOCAL int pcicFlagGet
    (
    int sock			/* socket no. */
    )
    {
    PCMCIA_CTRL *pCtrl	= &pcmciaCtrl;
    PCMCIA_CHIP *pChip	= &pCtrl->chip;
    char value;
    char vcc;
    char vpp;
    int flag=0;

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
    if (!(AT91_SYS->PIOB_PDSR & (AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2))) {
		flag |=PC_VCC_3V ;
		
	}

	
/*    at91_pcmcia_get_flags(sock, &flag);*/
#if 0
    value = pcicGet (sock, PCIC_POWER);
    vcc	  = value & PCIC_VCC_MASK;
    vpp	  = value & PCIC_VPP_MASK;

    flag  = (value & PCIC_PWR_AUTO) ? PC_PWR_AUTO : 0;
    switch (pChip->type)
	{
	case PCIC_PD672X:
	case PCIC_PD6710:
	    if (pcicGet (sock, PD67_MISC_CTL_1) & PD67_MC1_VCC_3V)
		{
		flag |= (value & PCIC_VCC_5V) ? PC_VCC_3V : 0;
		flag |= (vpp & PCIC_VPP_5V) ? PC_VPP_5V : 0;
		flag |= (vpp & PCIC_VPP_12V) ? PC_VPP_12V : 0;
		}
	    else
		{
		flag |= (value & PCIC_VCC_5V) ? PC_VCC_5V : 0;
		flag |= (vpp & PCIC_VPP_5V) ? PC_VPP_5V : 0;
		flag |= (vpp & PCIC_VPP_12V) ? PC_VPP_12V : 0;
		}
	    break;

	case PCIC_VG468:
	    if (value & PCIC_VCC_5V)
		{
		flag = PC_VCC_5V;
		flag |= (vpp & PCIC_VPP_5V) ? PC_VPP_5V : 0;
		flag |= (vpp & PCIC_VPP_12V) ? PC_VPP_12V : 0;
		}
	    break;

	default:
            flag |= (vcc & PCIC_VCC_3V) ? PC_VCC_3V : 0;
            flag |= (vcc & PCIC_VCC_5V) ? PC_VCC_5V : 0;
            flag |= (vpp & PCIC_VPP_5V) ? PC_VPP_5V : 0;
            flag |= (vpp & PCIC_VPP_12V) ? PC_VPP_12V : 0;
            break;
	}

    value = pcicGet (sock, PCIC_INTCTL);
    flag |= (value & PCIC_PC_IOCARD) ? PC_IOCARD : 0;
    flag |= (value & PCIC_PC_RESET) ? 0 : PC_RESET;
#endif

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (flag);
    }

/*******************************************************************************
*
* pcicFlagSet - Set configuration flag into the socket.
*
* This routine sets configuration flag into the socket.
*
* RETURNS: OK (always).
*/

LOCAL STATUS pcicFlagSet
    (
    int sock,			/* socket no. */
    int flag			/* configuration flag */
    )
    {
    PCMCIA_CTRL *pCtrl	= &pcmciaCtrl;
    PCMCIA_CHIP *pChip	= &pCtrl->chip;
    char value;
/*    socket_state_t state;
    
    memset(&state,0,sizeof(state));
    at91_pcmcia_get_socket(sock,&state);
  */  
    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */



#if 0
    value  = pcicGet (sock, PCIC_POWER);
    value &= ~(PCIC_PWR_AUTO | PCIC_VCC_MASK | PCIC_VPP_MASK);
    value |= (flag & PC_PWR_AUTO) ? PCIC_PWR_AUTO : 0;

    switch (pChip->type)
	{
	case PCIC_PD672X:
	case PCIC_PD6710:
	    if (flag & PC_VPP_MASK)
		{
		if (flag & PC_VPP_12V)
		    value |= PCIC_VPP_12V;
		else if ((flag & PC_VPP_5V) && (flag & PC_VCC_5V))
		    value |= PCIC_VPP_5V;
		}
	    if (flag & PC_VCC_MASK)
		{
		if (flag & PC_VCC_3V)
		    {
		    value |= PCIC_VCC_5V | PCIC_PWR_OUT;
		    pcicBset (sock, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
		    }
		else if (flag & PC_VCC_5V)
		    {
		    value |= PCIC_VCC_5V | PCIC_PWR_OUT;
		    pcicBclr (sock, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
		    }
		}
	    break;

	case PCIC_VG468:
            value |= (flag & PC_VCC_5V) ? PCIC_VCC_5V | PCIC_PWR_OUT : 0;
            value |= (flag & PC_VPP_5V) ? PCIC_VPP_5V : 0;
            value |= (flag & PC_VPP_12V) ? PCIC_VPP_12V : 0;
	    break;

	default:
            value |= (flag & PC_VCC_3V) ? PCIC_VCC_3V | PCIC_PWR_OUT : 0;
            value |= (flag & PC_VCC_5V) ? PCIC_VCC_5V | PCIC_PWR_OUT : 0;
            value |= (flag & PC_VPP_5V) ? PCIC_VPP_5V : 0;
            value |= (flag & PC_VPP_12V) ? PCIC_VPP_12V : 0;
	    break;
	}

    pcicSet (sock, PCIC_POWER, value);


    value = pcicGet (sock, PCIC_INTCTL);
    value &= ~(PCIC_PC_IOCARD | PCIC_PC_RESET);
    /* Note that the reset signal is inverted */
    value |= (flag & PC_RESET) ? 0 : PCIC_PC_RESET;
    value |= (flag & PC_IOCARD) ? PCIC_PC_IOCARD : 0;
    pcicSet (sock, PCIC_INTCTL, value);
#endif

/*    at91_pcmcia_set_socket(sock, &state);*/
	if(flag&PC_RESET) 
	
		AT91_SYS->PIOB_SODR = AT91C_CF_PB5_RESET;	/* set it */
	else
		AT91_SYS->PIOB_CODR = AT91C_CF_PB5_RESET;	/* clear it */
		
    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicCscOn - Enables the card status change interrupt.
*
* This routine enables the card status change interrupt.
*
* RETURNS: OK (always).
*/

LOCAL STATUS pcicCscOn
    (
    int sock,			/* socket no. */
    int irq			/* IRQ level for CSC */
    )
    {

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

    /* Turn on all card status change interrupts */
/*
    pcicSet (sock, PCIC_CSCINT, (irq << 4) | PCIC_CSC_ANY);
    pcicBclr (sock, PCIC_INTCTL, PCIC_INTR_ENA);
*/
    AT91_SYS->PIOB_ODR = at91_pcmcia_irqs[0].bits;	/* disable output */
    AT91_SYS->PIOB_IER = at91_pcmcia_irqs[0].bits;	/* enable  it */

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicCscOff - Disable the card status change interrupt.
*
* This routine Disables the card status change interrupt.
*
* RETURNS: OK (always).
*/

LOCAL STATUS pcicCscOff
    (
    int sock,			/* socket no. */
    int irq			/* IRQ level for CSC */
    )
    {

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

    /* Turn off all card status change interrupts */
#if 0
    pcicSet (sock, PCIC_CSCINT, (irq << 4) | 0x00);
#endif
    AT91_SYS->PIOB_ODR = at91_pcmcia_irqs[0].bits;	/* disable output */
    AT91_SYS->PIOB_IDR = at91_pcmcia_irqs[0].bits;	/* disable it */

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicCscPoll - Get the card status by polling the register.
*
* This routine gets the card status by polling the register.
* This routine can be called in interrupt level.
*
* RETURNS: The card status of the socket.
*/

LOCAL int pcicCscPoll
    (
    int sock			/* socket no. */
    )
    {
    BOOL intMode = intContext ();
    int  value;
    int  value0;
    int  status=0;

    if (!intMode)
        semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

	
/*  value = at91_pcmcia_poll_event(0);
    if(value&PC_DETECT) status = PC_DETECT;
    if(value&PC_STSCHG) status = PC_STSCHG;
    if(value&PC_READY) status = PC_READY;
*/
	if (!(AT91_SYS->PIOB_PDSR & (AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2))) {
		status |= PC_DETECT;
	}

	if (status&PC_DETECT) {
		if((AT91_SYS->PIOB_PDSR & AT91C_CF_PB4_RDY))
			status |= PC_READY;
	}
#if 0
    value = pcicGet (sock, PCIC_CSC);
    while ((value0 = pcicGet (sock, PCIC_CSC)) != 0)
        value |= value0;

    if (pcicGet (sock, PCIC_INTCTL) & PCIC_PC_IOCARD)
	status  = (value & PCIC_CSC_STSCHG) ? PC_STSCHG : 0;
    else
	{
	status  = (value & PCIC_CSC_BVD1) ? PC_BATDEAD : 0;
	status |= (value & PCIC_CSC_BVD2) ? PC_BATWARN : 0;
        }
    status |= (value & PCIC_CSC_READY) ? PC_READY : 0;
    status |= (value & PCIC_CSC_DETECT) ? PC_DETECT : 0;
#endif

    if (!intMode)
        semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (status);
    }

/*******************************************************************************
*
* pcicIrqGet - Get IRQ level of the socket.
*
* This routine gets IRQ level of the socket.
*
* RETURNS: The IRQ level of the socket.
*/

LOCAL int pcicIrqGet
    (
    int sock			/* socket no. */
    )
    {
    char value;

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

 /*   value = pcicGet (sock, PCIC_INTCTL);*/
    value = AT91C_ID_PIOB ; 

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (value & PCIC_IRQ_MASK);
    }

/*******************************************************************************
*
* pcicIrqSet - Set IRQ level of the socket.
*
* This routine sets IRQ level of the socket.
*
* RETURNS: OK, or ERROR if the IRQ level is greater than 15.
*/

LOCAL STATUS pcicIrqSet
    (
    int sock,			/* socket no. */
    int irq			/* IRQ level for the PC card */
    )
    {
#if 0
    char value;

    if (irq > 15)
	return (ERROR);

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

    value = pcicGet (sock, PCIC_INTCTL);
    value = (value & ~PCIC_IRQ_MASK) | irq;
    pcicSet (sock, PCIC_INTCTL, value);

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */
#endif
    return (OK);
    }

/*******************************************************************************
*
* pcicReset - Reset a card in the socket.
*
* This routine reset a card in the socket.
*
* RETURNS: OK (always).
*/

LOCAL STATUS pcicReset
    (
    int sock			/* socket no. */
    )
    {
 	int count=1000;
    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
#if 0
    /* Turn off interrupts, select memory-only interface */

    pcicBclr (sock, PCIC_INTCTL, PCIC_PC_IOCARD | PCIC_IRQ_MASK);

    /* Turn off all IO and Memory windows */

    pcicBclr (sock, PCIC_ADDRWIN, PCIC_ENA_ALL);
#endif
    
    AT91_SYS->PIOB_SODR = AT91C_CF_PB5_RESET;	/* set it */

    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */
    if( AT91F_CF_Card_OK()!=1) return (ERROR);
	else return OK;
    }

/*******************************************************************************
*
* pcicIowinGet - Get the IO window of the socket.
*
* This routine gets the IO window of the socket.
*
* RETURNS: OK, or ERROR if the window number is greater than max windows.
*/

LOCAL STATUS pcicIowinGet
    (
    int		 sock,		/* socket no. */
    PCMCIA_IOWIN *io		/* io window structure to get */
    )
    {
    char window	= io->window;
    char ioctl;
    char addr;

    if (window >= PCIC_IO_WINDOWS)
	return (ERROR);

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */

#if 0
    ioctl	= pcicGet (sock, PCIC_IOCTL);
    addr	= pcicGet (sock, PCIC_ADDRWIN);

    io->start	= pcicGet2 (sock, PCIC_IO(window)+PCIC_W_START);
    io->stop	= pcicGet2 (sock, PCIC_IO(window)+PCIC_W_STOP);
    io->extraws	= (ioctl & PCIC_IOCTL_WAIT(window)) ? 1 : 0;
    io->flags	= (addr & PCIC_ENA_IO(window)) ? MAP_ACTIVE : 0;
    io->flags  |= (ioctl & PCIC_IOCTL_0WS(window)) ? MAP_0WS : 0;
    io->flags  |= (ioctl & PCIC_IOCTL_CS16(window)) ? MAP_CS16 : 0;
    io->flags  |= (ioctl & PCIC_IOCTL_16BIT(window)) ? MAP_16BIT : 0;
#endif

/*
    io->start	= (int) at91_pcmcia_socket[sock].virt_io ;
    io->stop	=  io->start +PAGE_SIZE - 1;
    io->flags   =   at91_pcmcia_socket[sock].cs_state.flags;
 */   
/*    io->extraws	= (io->flags&MAP_USE_WAIT) ? 1 : 0;*/
    
    
    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicIowinSet - Set the IO window of the socket.
*
* This routine sets the IO window of the socket.
*
* RETURNS: OK, or ERROR if there is an error.
*/

LOCAL STATUS pcicIowinSet
    (
    int		 sock,		/* socket no. */
    PCMCIA_IOWIN *io		/* io window structure to set */
    )
    {
    char window	= io->window;
    char ioctl;

    if ((window >= PCIC_IO_WINDOWS) || (io->start > 0xffff) ||
	(io->stop > 0xffff) || (io->stop < io->start))
	return (ERROR);

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */


#if 0
    ioctl = pcicGet (sock, PCIC_IOCTL) & ~PCIC_IOCTL_MASK(window);

    /* Turn off the window before changing anything */
    if (pcicGet (sock, PCIC_ADDRWIN) & PCIC_ENA_IO(window))
	pcicBclr (sock, PCIC_ADDRWIN, PCIC_ENA_IO(window));

    pcicSet2 (sock, PCIC_IO(window)+PCIC_W_START, io->start);
    pcicSet2 (sock, PCIC_IO(window)+PCIC_W_STOP, io->stop);
    if (io->extraws) 
	ioctl |= PCIC_IOCTL_WAIT(window);
    if (io->flags & MAP_0WS) 
	ioctl |= PCIC_IOCTL_0WS(window);
    if (io->flags & MAP_CS16) 
	ioctl |= PCIC_IOCTL_CS16(window);
    if (io->flags & MAP_16BIT) 
	ioctl |= PCIC_IOCTL_16BIT(window);
    pcicSet (sock, PCIC_IOCTL, ioctl);

    /* Turn on the window if necessary */
    if (io->flags & MAP_ACTIVE)
	pcicBset (sock, PCIC_ADDRWIN, PCIC_ENA_IO(window));
#endif
    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicMemwinGet - Get the Memory window of the socket.
*
* This routine gets the Memory window of the socket.
*
* RETURNS: OK, or ERROR if the window number is greater than max windows.
*/

LOCAL STATUS pcicMemwinGet
    (
    int		  sock,		/* socket no. */
    PCMCIA_MEMWIN *mem		/* memory window structure to get */
    )
    {
    char window	= mem->window;
    char addr;
    short base;
    short value;
    
    if (window >= PCIC_MEM_WINDOWS)
	return (ERROR);

    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
#if 0
    addr	    = pcicGet (sock, PCIC_ADDRWIN);
    base	    = PCIC_MEM(window);

    mem->flags	    = (addr & PCIC_ENA_MEM(window)) ? MAP_ACTIVE : 0;
    
    value = pcicGet2 (sock, base+PCIC_W_START);
    mem->flags     |= (value & PCIC_MEM_16BIT) ? MAP_16BIT : 0;
    mem->flags     |= (value & PCIC_MEM_0WS) ? MAP_0WS : 0;
    mem->start      = ((long)(value & 0x0fff) << 12);
    
    value = pcicGet2 (sock, base+PCIC_W_STOP);
    mem->extraws    = (value & PCIC_MEM_WS0) ? 1 : 0;
    mem->extraws   += (value & PCIC_MEM_WS1) ? 2 : 0;
    mem->stop	    = ((long)(value & 0x0fff) << 12) + 0x0fff;
    
    value = pcicGet2 (sock, base+PCIC_W_OFF);
    mem->flags	   |= (value & PCIC_MEM_WRPROT) ? MAP_WRPROT : 0;
    mem->flags	   |= (value & PCIC_MEM_REG) ? MAP_ATTRIB : 0;
    mem->cardstart  = ((long)(value & 0x3fff) << 12) + mem->start;
    mem->cardstart &= 0x3ffffff;
#endif
    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

/*******************************************************************************
*
* pcicMemwinSet - Set the Memory window of the socket.
*
* This routine sets the Memory window of the socket.
*
* RETURNS: OK, or ERROR if there is an error.
*/

LOCAL STATUS pcicMemwinSet
    (
    int		  sock,		/* socket no. */
    PCMCIA_MEMWIN *mem		/* memory window structure to set */
    )
    {
    char window	= mem->window;
    short base;
    short value;
    
/*    if ((window >= PCIC_MEM_WINDOWS) || (mem->cardstart > 0x3ffffff) ||
	(mem->start > 0xffffff) || (mem->stop > 0xffffff) ||
	(mem->start > mem->stop) || (mem->extraws > 3))
	return (ERROR);
*/
    semTake (&pcicMuteSem, WAIT_FOREVER);	/* mutual execlusion start */
#if 0
    base = PCIC_MEM(window);

    /* Turn off the window before changing anything */
    if (pcicGet (sock, PCIC_ADDRWIN) & PCIC_ENA_MEM(window))
	pcicBclr (sock, PCIC_ADDRWIN, PCIC_ENA_MEM(window));
    
    value = mem->start >> 12;
    if (mem->flags & MAP_16BIT)
	{
	value |= PCIC_MEM_16BIT;
	pcicBset (sock, PCIC_ADDRWIN, PCIC_ENA_MEMCS16);
	}
    if (mem->flags & MAP_0WS)
	value |= PCIC_MEM_0WS;
    pcicSet2 (sock, base+PCIC_W_START, value);
    
    value = mem->stop >> 12;
    if (mem->extraws & 1)
	value |= PCIC_MEM_WS0;
    if (mem->extraws & 2)
	value |= PCIC_MEM_WS1;
    pcicSet2 (sock, base+PCIC_W_STOP, value);
    
    value = ((mem->cardstart - mem->start) >> 12) & 0x3fff;
    if (mem->flags & MAP_WRPROT)
	value |= PCIC_MEM_WRPROT;
    if (mem->flags & MAP_ATTRIB)
	value |= PCIC_MEM_REG;
    pcicSet2 (sock, base+PCIC_W_OFF, value);
    
    /* Turn on the window if necessary */
    if (mem->flags & MAP_ACTIVE)
	pcicBset (sock, PCIC_ADDRWIN, PCIC_ENA_MEM(window));
#endif
    semGive (&pcicMuteSem);		 	/* mutual execlusion stop */

    return (OK);
    }

#if 0
/*******************************************************************************
*
* pcicGet - Get a value from the register.
*
* This routine gets a value from the register.
*
* RETURNS: A value of the register.
*/

LOCAL int pcicGet
    (
    int sock,			/* socket no. */
    int reg			/* register no. */
    )
    {
    short port	= PCIC_PORT (sock);
    char offset	= PCIC_REG (sock, reg);

    sysOutByte (port, offset);
    return (sysInByte (port+1));
    }

/*******************************************************************************
*
* pcicSet - Set a value into the register.
*
* This routine sets a value into the register.
*
* RETURNS: N/A
*/

LOCAL void pcicSet
    (
    int  sock,			/* socket no. */
    int  reg,			/* register no. */
    char value			/* value to set */
    )
    {
    short port	= PCIC_PORT (sock);
    char offset	= PCIC_REG (sock, reg);

    sysOutByte (port, offset);
    sysOutByte (port+1, value);
    }

/*******************************************************************************
*
* pcicBset - Set specified bits in the register.
*
* This routine sets specified bits in the register.
*
* RETURNS: N/A
*/

LOCAL void pcicBset
    (
    int  sock,			/* socket no. */
    int  reg,			/* register no. */
    char mask			/* bits to set */
    )
    {
    char value	= pcicGet (sock, reg);

    value |= mask;
    pcicSet (sock, reg, value);
    }

/*******************************************************************************
*
* pcicBclr - Clear specified bits in the register.
*
* This routine clears specified bits in the register.
*
* RETURNS: N/A
*/

LOCAL void pcicBclr
    (
    int  sock,			/* socket no. */
    int  reg,			/* register no. */
    char mask			/* bits to clear */
    )
    {
    char value	= pcicGet (sock, reg);

    value &= ~mask;
    pcicSet (sock, reg, value);
    }

/*******************************************************************************
*
* pcicGet2 - Get a value from the consecutive registers.
*
* This routine gets a value from the consecutive registers.
*
* RETURNS: a value of the register
*/

LOCAL int pcicGet2
    (
    int sock,			/* socket no. */
    int reg			/* register no. */
    )
    {
    short a	= pcicGet (sock, reg);
    short b	= pcicGet (sock, reg+1);

    return (a + (b<<8));
    }

/*******************************************************************************
*
* pcicSet2 - Set a value into the consecutive registers.
*
* This routine sets a value into the consecutive registers.
*
* RETURNS: N/A
*/

LOCAL void pcicSet2
    (
    int   sock,			/* socket no. */
    int   reg,			/* register no. */
    short value			/* value to set */
    )
    {
    pcicSet (sock, reg, value & 0xff);
    pcicSet (sock, reg+1, value >> 8);
    }


#endif





