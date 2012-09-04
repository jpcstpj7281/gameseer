/* at91Timer.c - at91rm9200 timer driver */






#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"
#include "drv/timer/timerDev.h"
#include "drv/timer/timestampDev.h"
/*#include "h/AT91RM9200_TC.h"*/

#include "config.h"
#include "drv/intrCtl/at91Intr.h"
#include "drv/timer/at91Timer.h"
#include "drv/sio/at91Sio.h"
#include "lib_AT91RM9200.h"

#define CLOCK_TICK_RATE		(AT91C_SLOW_CLOCK)
#define LATCH  ((CLOCK_TICK_RATE + HZ/2) / HZ)	/* For divider */
#define HZ  100
/* Local forward declarations */

LOCAL BOOL sysClkConnectFirstTime       = TRUE;
LOCAL FUNCPTR sysClkRoutine             = NULL;
LOCAL int sysClkArg                     = 0;
LOCAL int sysClkRunning                 = FALSE;
LOCAL int sysClkTicksPerSecond          = DEF_SYS_CLK_TICKS;

LOCAL BOOL sysAuxClkConnectFirstTime    = TRUE;
LOCAL FUNCPTR sysAuxClkRoutine          = NULL;
LOCAL int sysAuxClkArg                  = 0;
LOCAL int sysAuxClkRunning              = FALSE;
LOCAL int sysAuxClkTicksPerSecond       = 100;
LOCAL UINT32 BspDaubleSecond;
#ifdef  INCLUDE_TIMESTAMP
LOCAL BOOL sysTimestampConnectFirstTime = TRUE;
LOCAL FUNCPTR sysTimestampRoutine       = NULL;
LOCAL int sysTimestampArg               = 0;
LOCAL BOOL sysTimestampRunning          = FALSE;
#endif  /* INCLUDE_TIMESTAMP */


/*******************************************************************************
*
* sysClkInt - clock interrupt handler
*
* This routine handles the clock interrupt on the at91rm9200 architecture. It is
* attached to the INT_VEC_SYS vector by the routine sysClkConnect().
*
* RETURNS : N/A
*/

LOCAL void sysClkInt(void)
{
    /* Clear interrupt. */
/*    *S3C2510_TIC |= S3C2510_TIC_T5;*/
    unsigned int st_sr = AT91_SYS->ST_SR;
    unsigned int dbgu_sr = AT91_SYS->DBGU_CSR;  
	if (st_sr & AT91C_ST_PITS) {	
	    /* Call system clock service routine. */
	    if (sysClkRoutine && sysClkRunning)
	    {
	        (*sysClkRoutine)(sysClkArg);
	    }
	}else
	if(dbgu_sr &  (AT91C_US_RXRDY| AT91C_US_TXEMPTY ))
	{
		at91SioInt(0);
	}
}

/*******************************************************************************
*
* sysClkConnect - connect a routine to the system clock interrupt
*
* This routine specifies the interrupt service routine to be called at each
* clock interrupt. Normally, it is called from usrRoot() in usrConfig.c to
* connect usrClock() to the system clock interrupt.
*
* RETURNS: OK, or ERROR if the routine cannot be connected to the interrupt.
*
* SEE ALSO: intConnect(), usrClock(), sysClkEnable()
*/

STATUS sysClkConnect(
    FUNCPTR routine,                                        /* routine called at each clock interrupt */
    int arg                                                 /* argument to clock interrupt routine */
    )
{
	
	AT91F_PMC_EnablePeriphClock ( (AT91PS_PMC)AT91C_BASE_PMC, 0xFFFFFFFF ) ;
    if (sysClkConnectFirstTime)
    {
        sysHwInit2();

	/* Disable all timer interrupts */
	AT91_SYS->ST_IDR = AT91C_ST_PITS | AT91C_ST_WDOVF | AT91C_ST_RTTINC | AT91C_ST_ALMS;
	(void) AT91_SYS->ST_SR;		/* Clear any pending interrupts */

	/*
	 * Make IRQs happen for the system timer.
	 */
/*	timer_irq.handler = at91rm9200_timer_interrupt;*/
/*	timer_irq.flags = SA_SHIRQ | SA_INTERRUPT;*/
/*	setup_arm_irq(AT91C_ID_SYS, &timer_irq);*/

/*	gettimeoffset = at91rm9200_gettimeoffset;*/

	/* Set initial alarm to 0 */
	AT91_SYS->ST_RTAR = 0;

	/* Real time counter incremented every 30.51758 microseconds */
	AT91_SYS->ST_RTMR = 1;

	/* Set Period Interval timer */
	AT91_SYS->ST_PIMR = LATCH;

	/* Change the kernel's 'tick' value to 10009 usec. (the default is 10000) */
/*	tick = (LATCH * 1000000) / CLOCK_TICK_RATE;*/

	/* Enable Period Interval Timer interrupt */
	AT91_SYS->ST_IER = AT91C_ST_PITS;


          /* Connect and enable interrupt. */
        intConnect(INT_VEC_SYS, (VOIDFUNCPTR)sysClkInt, 0);
        intEnable(INT_LVL_SYS);

        sysClkConnectFirstTime = FALSE;
   }

    sysClkRoutine   = routine;
    sysClkArg       = arg;

    return OK;
}

/*******************************************************************************
*
* sysClkDisable - turn off system clock interrupts
*
* This routine disables system clock interrupts.
*
* RETURNS: N/A
*
* SEE ALSO: sysClkEnable()
*/

void sysClkDisable(void)
{
    if (sysClkRunning)
    {
        /* Disable timer. */
      /*  *S3C2510_TMOD &= ~S3C2510_TMOD_TE5;*/
	AT91_SYS->ST_IDR = AT91C_ST_PITS | AT91C_ST_WDOVF | AT91C_ST_RTTINC | AT91C_ST_ALMS;

        sysClkRunning = FALSE;
    }
}

/*******************************************************************************
*
* sysClkEnable - turn on system clock interrupts
*
* This routine enables system clock interrupts.
*
* RETURNS: N/A
*
* SEE ALSO: sysClkConnect(), sysClkDisable(), sysClkRateSet()
*/

void sysClkEnable(void)
{
    if (!sysClkRunning)
    {
        /* Calculate the timer interval. */
        /* *S3C2510_TDATA5 = SPLL_FREQ * 1000 * 1000 / sysClkTicksPerSecond - 1;*/
        /*	AT91_SYS->ST_CRTR = SPLL_FREQ * 1000 * 1000 / sysClkTicksPerSecond - 1;*/

        /* Enable timer. */
        /* *S3C2510_TMOD |= S3C2510_TMOD_TE5; */
        
        AT91_SYS->ST_PIMR =  ((CLOCK_TICK_RATE + sysClkTicksPerSecond/2) / sysClkTicksPerSecond)	;/* For divider */
        AT91_SYS->ST_IER = AT91C_ST_PITS ;/*| AT91C_ST_WDOVF | AT91C_ST_RTTINC | AT91C_ST_ALMS;*/
        sysClkRunning = TRUE;
    }
}

/*******************************************************************************
*
* sysClkRateGet - get the system clock rate
*
* This routine returns the system clock rate.
*
* RETURNS: The number of ticks per second of the system clock.
*
* SEE ALSO: sysClkEnable(), sysClkRateSet()
*/

int sysClkRateGet(void)
{
    return (sysClkTicksPerSecond);
}


/*******************************************************************************
*
* sysClkRateSet - set the system clock rate
*
* This routine sets the interrupt rate of the system clock. It is called by
* usrRoot() in usrConfig.c.
*
* RETURNS: OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* SEE ALSO: sysClkEnable(), sysClkRateGet()
*/

STATUS sysClkRateSet(
    int ticksPerSecond                                      /* number of clock interrupts per second */
    )
{
    if ((ticksPerSecond < SYS_CLK_RATE_MIN) || (ticksPerSecond > SYS_CLK_RATE_MAX))
    {
        return ERROR;
    }

    sysClkTicksPerSecond = ticksPerSecond;

    if (sysClkRunning)
    {
        sysClkDisable();
        sysClkEnable();
    }
    
/*    LED_ON(LED8_MASK);*/
    
    return OK;
}

/*******************************************************************************
*
* sysAuxClkInt - auxiliary clock interrupt handler
*
* This routine handles the auxiliary clock interrupton the S3C9500 architecture.
* It is attached to the TIMER5 vector by the routine sysAuxClkConnect().
*
* RETURNS : N/A
*/

LOCAL void sysAuxClkInt(void)
{
    /* Clear interrupt. */
   /* *S3C2510_TIC |= S3C2510_TIC_T4;*/
    
	AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC0 ; 
    unsigned int temp=tc->TC_SR;
	if(temp&AT91C_TC_CPCS)
	{
        /* Call auxiliary clock service routine. */
        if (sysAuxClkRoutine && sysAuxClkRunning)
        {
            (*sysAuxClkRoutine)(sysAuxClkArg);
        }
	}
}

/*******************************************************************************
*
* sysAuxClkConnect - connect a routine to the auxiliary clock interrupt
*
* This routine specifies the interrupt service routine to be called at each
* auxiliary clock interrupt. It does not enable auxiliary clock interrupts.
*
* RETURNS: OK, or ERROR if the routine cannot be connected to the interrupt.
*
* SEE ALSO: intConnect(), sysAuxClkEnable()
*/

STATUS sysAuxClkConnect(
    FUNCPTR routine,                                        /* routine called at each auxiliary clock interrupt */
    int arg                                                 /* argument to auxiliary clock interrupt routine */
    )
{
    if (sysAuxClkConnectFirstTime)
    {
        unsigned int temp;
        AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC0 ; 

        
        /*AT91F_PMC_EnablePeriphClock ( (AT91PS_PMC)AT91C_BASE_PMC, (unsigned int)(1<<17) ) ;*/
        AT91F_PMC_EnablePeriphClock ( (AT91PS_PMC)AT91C_BASE_PMC, 0xFFFFFFFF ) ;

        /* Enable peripheral clock. */
        /* *S3C2510_PCLKDIS &= ~S3C2510_PCLKDIS_TIMER4;*/

        /* Interval mode. */
        /* *S3C2510_TMOD &= ~S3C2510_TMOD_TMD4;*/


        tc->TC_CMR=4|AT91C_TC_WAVE|AT91C_TC_WAVESEL_UP_AUTO;
        tc->TC_RC=((CLOCK_TICK_RATE + sysAuxClkTicksPerSecond/2) / sysAuxClkTicksPerSecond);
        temp=tc->TC_SR;    
        temp=tc->TC_SR; 
        AT91F_AIC_Trig (AT91C_BASE_AIC,AT91C_ID_TC0) ;
        tc->TC_CCR = AT91C_TC_CLKEN;
        tc->TC_CCR = AT91C_TC_SWTRG ;

        /* Connect and enable interrupt. */
        sysAuxClkConnectFirstTime = FALSE;
        intConnect(INT_VEC_TC0, (VOIDFUNCPTR)sysAuxClkInt, 0);
        intEnable(INT_LVL_TC0);
        tc->TC_IER=AT91C_TC_CPCS;

    }

    sysAuxClkRoutine    = routine;
    sysAuxClkArg        = arg;

    return OK;
}

/*******************************************************************************
*
* sysAuxClkDisable - turn off auxiliary clock interrupts
*
* This routine disables auxiliary clock interrupts.
*
* RETURNS: N/A
*
* SEE ALSO: sysAuxClkEnable()
*/

void sysAuxClkDisable(void)
{
    if (sysAuxClkRunning)
    {
        /* Disable timer. */
     /*   *S3C2510_TMOD &= ~S3C2510_TMOD_TE4;*/
	AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC0 ; 
	tc->TC_CCR = AT91C_TC_CLKDIS ;


        sysAuxClkRunning = FALSE;
    }
}

/*******************************************************************************
*
* sysAuxClkEnable - turn on auxiliary clock interrupts
*
* This routine enables auxiliary clock interrupts. The timer is used in
* "reference mode" i.e. a value is programmed into the reference register and an
* interrupt occurs when the timer reaches that value. 
*
* RETURNS: N/A
*
* SEE ALSO: sysAuxClkConnect(), sysAuxClkDisable(), sysAuxClkRateSet()
*/

void sysAuxClkEnable(void)
{
    if (!sysAuxClkRunning)
    {
        /* Calculate the timer interval. */
      /*  *S3C2510_TDATA4 = SPLL_FREQ * 1000 * 1000 / sysAuxClkTicksPerSecond - 1;*/

        /* Enable timer. */
      /*  *S3C2510_TMOD |= S3C2510_TMOD_TE4;*/
	AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC0 ; 
    tc->TC_RC=((CLOCK_TICK_RATE + sysAuxClkTicksPerSecond/2) / sysAuxClkTicksPerSecond);
	tc->TC_CCR = AT91C_TC_CLKEN ;
    tc->TC_CCR = AT91C_TC_SWTRG ;

        sysAuxClkRunning = TRUE;
    }
}

/*******************************************************************************
*
* sysAuxClkRateGet - get the auxiliary clock rate
*
* This routine returns the interrupt rate of the auxiliary clock.
*
* RETURNS: The number of ticks per second of the auxiliary clock.
*
* SEE ALSO: sysAuxClkEnable(), sysAuxClkRateSet()
*/

int sysAuxClkRateGet(void)
{
    return (sysAuxClkTicksPerSecond);
}

/*******************************************************************************
*
* sysAuxClkRateSet - set the auxiliary clock rate
*
* This routine sets the interrupt rate of the auxiliary clock. It does not
* enable auxiliary clock interrupts.
*
* RETURNS: OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* SEE ALSO: sysAuxClkEnable(), sysAuxClkRateGet()
*/

STATUS sysAuxClkRateSet(
    int ticksPerSecond                                      /* number of clock interrupts per second */
    )
{
    if ((ticksPerSecond < SYS_CLK_RATE_MIN) || (ticksPerSecond > SYS_CLK_RATE_MAX))
    {
        return ERROR;
    }

    sysAuxClkTicksPerSecond = ticksPerSecond;

    if (sysAuxClkRunning)
    {
        sysAuxClkDisable();
        sysAuxClkEnable();
    }

    return OK;
}

#ifdef  INCLUDE_TIMESTAMP
/*******************************************************************************
*
* sysTimestampInt - timestamp timer interrupt handler
*
* This rountine handles the timestamp timer interrupt. A user routine is called,
* if one was connected by sysTimestampConnect().
*
* RETURNS: N/A
*
* SEE ALSO: sysTimestampConnect()
*/

void sysTimestampInt(void)
{
    /* Clear interrupt. */
    *S3C2510_TIC |= S3C2510_TIC_T3;

    /* Call timestamp timer service routine. */
    if (sysTimestampRoutine && sysTimestampRunning)
    {
        (*sysTimestampRoutine)(sysTimestampArg);
    }
}

/*******************************************************************************
*
* sysTimestampConnect - connect a user routine to the timestamp timer interrupt
*
* This routine specifies the user interrupt routine to be called at each
* timestamp timer interrupt. It does not enable the timestamp timer itself.
*
* RETURNS: OK, or ERROR if sysTimestampInt() interrupt handler is not used.
*/

STATUS sysTimestampConnect(
    FUNCPTR routine,                                        /* routine called at each timestamp timer interrupt */
    int arg                                                 /* argument to timestamp timer interrupt routine */
    )
{
    if (sysTimestampConnectFirstTime)
    {
        /* Enable peripheral clock. */
        *S3C2510_PCLKDIS &= ~S3C2510_PCLKDIS_TIMER3;

        /* Interval mode. */
        *S3C2510_TMOD &= ~S3C2510_TMOD_TMD3;

        /* Connect and enable interrupt. */
        intConnect(INT_VEC_TIMER3, (VOIDFUNCPTR)sysTimestampInt, 0);
        intEnable(INT_LVL_TIMER3);

        sysTimestampConnectFirstTime = FALSE;
    }

    sysTimestampRoutine = routine;
    sysTimestampArg     = arg;

    return OK;
}

/*******************************************************************************
*
* sysTimestampDisable - turn off auxiliary clock interrupts
*
* This routine disables auxiliary clock interrupts.
*
* RETURNS: OK, always
*
* SEE ALSO: sysTimestampEnable()
*/

STATUS sysTimestampDisable(void)
{
    if (sysTimestampRunning)
    {
        /* Disable timer. */
        *S3C2510_TMOD &= ~S3C2510_TMOD_TE3;

        sysTimestampRunning = FALSE;
    }

    return OK;
}

/*******************************************************************************
*
* sysTimestampEnable - initialize and enable the timestamp timer
*
* This routine connects interrupts, and enables the timer device
*
* RETURNS: TRUE always
*/

STATUS sysTimestampEnable(void)
{
    if (!sysTimestampRunning)
    {
        /* Calculate the timer interval. */
        *S3C2510_TDATA3 = SPLL_FREQ * 1000 * 1000 / DEF_SYS_TIMESTAMP_TICKS - 1;

        /* Enable timer. */
        *S3C2510_TMOD |= S3C2510_TMOD_TE3;

        sysTimestampRunning = TRUE;
    }

    return OK;
}

/*******************************************************************************
*
* sysTimestampPeriod - get the period of a timestamp timer 
*
* This routine gets the period of the timestamp timer, in ticks. The period, or
* terminal count, is the number of ticks to which the timestamp timer counts
* before rolling over and restarting the counting process.
*
* RETURNS: The period of the timestamp timer in counter ticks.
*/

UINT32 sysTimestampPeriod(void)
{
    /* The period of the timestamp depends on the clock rate of the on-chip timer. */

    return (*S3C2510_TDATA3);
}

/*******************************************************************************
*
* sysTimestampFreq - get a timestamp timer clock frequency
*
* This routine gets the frequency of the timer clock, in ticks per second. The
* rate of the timestamp timer is set explicitly by the hardware and typically
* cannot be altered.
*
* RETURNS: The timestamp timer clock frequency, in ticks per second.
*/

UINT32 sysTimestampFreq(void)
{
    return (SPLL_FREQ * 1000 * 1000);
}

/*******************************************************************************
*
* sysTimestamp - get a timestamp timer tick count
*
* This routine returns the current value of the timestamp timer tick counter.
* The tick count can be converted to seconds by dividing it by the return of
* sysTimestampFreq().
*
* This routine should be called with interrupts locked. If interrupts are not
* locked, sysTimestampLock() should be used instead.
*
* RETURNS: The current timestamp timer tick count.
*
* SEE ALSO: sysTimestampFreq(), sysTimestampLock()
*/

UINT32 sysTimestamp(void)
{
    return (*S3C2510_TCNT3);
}

/*******************************************************************************
*
* sysTimestampLock - lock interrupts and get the timestamp timer tick count
*
* This routine locks interrupts when the tick counter must be stopped in order
* to read it or when two independent counters must be read. It then returns the
* current value of the timestamp timer tick counter.
* 
* The tick count can be converted to seconds by dividing it by the return of
* sysTimestampFreq().
*
* If interrupts are already locked, sysTimestamp() should be used instead.
*
* RETURNS: The current timestamp timer tick count.
*
* SEE ALSO: sysTimestampFreq(), sysTimestamp()
*/

UINT32 sysTimestampLock(void)
{
    return (*S3C2510_TCNT3);
}
#endif  /* INCLUDE_TIMESTAMP */





LOCAL void BspClkInt(void)
{
    /* Clear interrupt. */
   /* *S3C2510_TIC |= S3C2510_TIC_T4;*/
    
	AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC1 ; 
    unsigned int temp=tc->TC_SR;
	if(temp&AT91C_TC_CPCS)
	{
		BspDaubleSecond++;
	}
}


UINT32 BSP_TimeInit(void)
{
		
        unsigned int temp;
        AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC1 ; 
        tc->TC_CMR=4|AT91C_TC_WAVE|AT91C_TC_WAVESEL_UP_AUTO;
        tc->TC_RC=0xFFFF;
        temp=tc->TC_SR;    
        temp=tc->TC_SR; 
        AT91F_AIC_Trig (AT91C_BASE_AIC,AT91C_ID_TC1) ;
        tc->TC_CCR = AT91C_TC_CLKEN;
        tc->TC_CCR = AT91C_TC_SWTRG ;
	    BspDaubleSecond=0;
	    intConnect(INT_VEC_TC1, (VOIDFUNCPTR)BspClkInt, 0);
	    intEnable(INT_LVL_TC1);
	    tc->TC_IER=AT91C_TC_CPCS;

        return OK;


}


UINT32 BSP_TimeGet(UINT32 *DaubleSecond ,UINT32 *munit)
{
        AT91PS_TC tc = (AT91PS_TC) AT91C_BASE_TC1 ; 
		*DaubleSecond = BspDaubleSecond;
	    *munit = tc->TC_CV;
		if(*DaubleSecond != BspDaubleSecond)
			{
			*DaubleSecond = BspDaubleSecond;
			*munit = tc->TC_CV;
			}
		return OK;
}

static unsigned int valuetemp[400];

UINT32 TestBspTimer()
{

	int i;
	for(i=0;i<200;i +=2)
		{
		BSP_TimeGet(&valuetemp[i],&valuetemp[i+1]);
		ping("192.168.67.111",1,11);
		}
	return (UINT32)valuetemp;

}



