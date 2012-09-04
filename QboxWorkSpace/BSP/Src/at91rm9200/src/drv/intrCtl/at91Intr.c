/* at91Intr.c - at91rm9200 interrupt controller driver */



/*
modification history
--------------------
01b,17July02,jwchoi
01a,08feb02,jmLee   created.
*/


#include "vxWorks.h"
#include "intLib.h"
#include "iv.h"


#include "config.h"
#include "drv/intrCtl/at91Intr.h"


/*
 * Because FIQ is not handled within VxWorks, all interrupts should be processed
 * in IRQ mode.
*/

#define INTERNAL_INT_MODE               0x00000000          /* Internal Interrupt (Level 6 ~ 35) */
#define EXTERNAL_INT_MODE               0x00000000          /* External Interrupt (Level 0 ~ 5) */





/* Interrupt configuration */
static AT91_REG at91rm9200_irq_smr[]  = {
  (AT91_SMR_FIQ),   /* FIQ */
  (AT91_SMR_SYS),   /* System Peripherals */
  (AT91_SMR_PIOA),  /* PIO A */
  (AT91_SMR_PIOB),  /* PIO B */
  (AT91_SMR_PIOC),  /* PIO C */
  (AT91_SMR_PIOD),  /* PIO D */
  (AT91_SMR_US0),   /* USART 0 */
  (AT91_SMR_US1),   /* USART 1 */
  (AT91_SMR_US2),   /* USART 2 */
  (AT91_SMR_US3),   /* USART 3 */
  (AT91_SMR_MCI),   /* Multimedia Card */
  (AT91_SMR_UDP),   /* USB Device */
  (AT91_SMR_TWI),   /* Two-wire interface */
  (AT91_SMR_SPI),   /* SPI */
  (AT91_SMR_SSC0),  /* Sync Serial 0 */
  (AT91_SMR_SSC1),  /* Sync Serial 1 */
  (AT91_SMR_SSC2),  /* Sync Serial 2 */
  (AT91_SMR_TC0),   /* TC 0 */
  (AT91_SMR_TC1),   /* TC 1 */
  (AT91_SMR_TC2),   /* TC 2 */
  (AT91_SMR_TC3),   /* TC 3 */
  (AT91_SMR_TC4),   /* TC 4 */
  (AT91_SMR_TC5),   /* TC 5 */
  (AT91_SMR_UHP),   /* USB Host */
  (AT91_SMR_EMAC),  /* Ethernet */
  (AT91_SMR_IRQ0),  /* IRQ 0 */
  (AT91_SMR_IRQ1),  /* IRQ 1 */
  (AT91_SMR_IRQ2),  /* IRQ 2 */
  (AT91_SMR_IRQ3),  /* IRQ 3 */
  (AT91_SMR_IRQ4),  /* IRQ 4 */
  (AT91_SMR_IRQ5),  /* IRQ 5 */
  (AT91_SMR_IRQ6)   /* IRQ 6 */
};
#if 0
/* Interrupt priority table : Default value*/

LOCAL UINT32 intPriority[] = {
    0x03020100, /*                      Low  */
    0x07060504, /*                       .   */
    0x0B0A0908, /*                       .   */
    0x0F0E0D0C, /*                       .   */
    0x13121110, /*                       .   */
    0x17161514, /*                       .   */
    0x1B1A1918, /*                       .   */
    0x1F1E1D1C, /*                      High */
    0x23222120, /* High ........... Low      */    
};
#endif

/* Local forward declarations */

LOCAL STATUS at91IntLvlVecChk(int *pLevel, int *pVector);
LOCAL STATUS at91IntLvlVecAck(int level, int vector);
LOCAL STATUS at91IntLvlEnable(int level);
LOCAL STATUS at91IntLvlDisable(int level);


/*******************************************************************************
*
* at91IntDevInit - initialize the interrupt controller
*
* This routine will initialize the interrupt controller device, disabling all
* interrupt sources. It will also connect the device driver specific routines
* into the architecture level hooks. If the BSP needs to create a wrapper
* routine around any of the arhitecture level routines, it should install the
* pointer to the wrapper routine after calling this routine.
*
* RETURNS: N/A
*/

int  at91IntDevInit(void)
{
  unsigned int i;

  /*
   * The IVR is used by macro get_irqnr_and_base to read and verify.
   * The irq number is NR_IRQS when a spurious interrupt has occured.
   */
  for (i = 0; i < NR_IRQS; i++) {
    /* Put irq number in Source Vector Register: */
    AT91_SYS->AIC_SVR[i] = i;
    /* Store the Source Mode Register as defined in table above */
    AT91_SYS->AIC_SMR[i] = at91rm9200_irq_smr[i];

 

    /* Perform 8 End Of Interrupt Command to make sure AIC will not Lock out nIRQ */
    if (i < 8)
      AT91_SYS->AIC_EOICR = AT91_SYS->AIC_EOICR;
  }

  /* Spurious Interrupt ID in Spurious Vector Register is NR_IRQS
   * When there is no current interrupt, the IRQ Vector Register reads the value stored in AIC_SPU
   */
  AT91_SYS->AIC_SPU = NR_IRQS;

  /* No debugging in AIC: Debug (Protect) Control Register */
  AT91_SYS->AIC_DCR = 0;

  /* Disable and clear all interrupts initially */
  AT91_SYS->AIC_IDCR = 0xFFFFFFFF;
  AT91_SYS->AIC_ICCR = 0xFFFFFFFF;
    

    /* Install the driver routines in the architecture hooks. */
    sysIntLvlVecChkRtn  = at91IntLvlVecChk;
    sysIntLvlVecAckRtn	= at91IntLvlVecAck;
    sysIntLvlEnableRtn  = at91IntLvlEnable;
    sysIntLvlDisableRtn = at91IntLvlDisable;
	return OK;
}

/*******************************************************************************
*
* at91IntLvlVecChk - check for and return any pending interrupts
*
* This routine interrogates the hardware to determine the highest priority
* interrupt pending. It returns the vector associated with that interrupt, and
* also the interrupt priority level. The current interrupt should be masked.
*
* The return value ERROR indicates that no pending interrupt was found and that
* the level and vector values were not returned.
*
* RETURNS: OK or ERROR if no interrupt is pending.
*/

LOCAL STATUS at91IntLvlVecChk(
    int *pLevel,                                            /* pointer to receive current interrupt level */
    int *pVector                                            /* pointer to receive current interrupt vector */
    )
{
    int level;

    /* Read Interrupt Offset Register. */
    
    level = AT91_SYS->AIC_IVR ;/*level = (int)*AT91_INTOFFSET_IRQ;*/
    	
    if (level >= AT91_INT_NUM_LEVELS)
    {
    	/* DEBUG_LOG("\n\n: jwchoi check it 0x%x >\n\n", level,0,0,0,0,0); */
        return ERROR;
    }

    *pLevel  = level;
    *pVector = level;

    /* Disable current interrupt. */
    at91IntLvlDisable(level);

    return OK;
}

/*******************************************************************************
*
* at91IntLvlVecAck - acknowledge the current interrupt
*
* Acknowledge the current interrupt cycle. The level and vector values are those
* generated during the at91IntLvlVecChk() routine for this interrupt cycle.
* The basic action is to unmask the current interrupt.
*
* RETURNS: OK or ERROR if a hardware fault is detected.
*/

LOCAL STATUS at91IntLvlVecAck(
    int level,                                              /* current interrupt level to be restored */
    int vector                                              /* current interrupt vector, if needed */
    )
{
    AT91_SYS->AIC_EOICR = (1<<level) ; 

    /* Enable current interrupt. */
    at91IntLvlEnable(level);

    return OK;
}

/*******************************************************************************
*
* at91IntLvlEnable - enable a single interrupt level
*
* Enable a specific interrupt level. The enabled level will be allowed to 
* generate an interrupt, when the overall interrupt level is set below the
* specified level. Without being enabled, the interrupt is blocked regardless of
* the overall interrupt level setting.
*
* RETURNS: OK or ERROR if the specified level cannot be enabled.
*/

LOCAL STATUS at91IntLvlEnable(
    int level                                               /* level to be enabled */
    )
{
    int lockKey;

    if ((level < 0) || (level >= AT91_INT_NUM_LEVELS))
    {
        return ERROR;
    }

    lockKey = intLock();

/* Enable interrupt on AIC */
    AT91_SYS->AIC_IECR =  1 << level;

    intUnlock(lockKey);

    return OK;
}

/*******************************************************************************
*
* at91IntLvlDisable - disable a single interrupt level
*
* Disable a specific interrupt level. The disabled level is prevented from
* generating an interrupt even if the overall interrupt level is set below the
* specified level.
*
* RETURNS: OK or ERROR, if the specified interrupt level cannot be disabled.
*/

LOCAL STATUS at91IntLvlDisable(
    int level                                               /* level to be disabled */
    )
{
    int lockKey;

    if ((level < 0) || (level >= AT91_INT_NUM_LEVELS))
    {
        return ERROR;
    }

    lockKey = intLock();

   /* Disable interrupt on AIC */
    AT91_SYS->AIC_IDCR =  1 << level;

    intUnlock(lockKey);

    return OK;
}

