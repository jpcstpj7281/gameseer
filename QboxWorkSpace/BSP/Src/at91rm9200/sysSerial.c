/* sysSerial.c - AT91RM9200 serial device initialization */



/*
modification history
--------------------
01a,08feb02,jmLee   created.
*/


#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"
#include "sysLib.h"


#include "config.h"
#include "drv/intrCtl/at91Intr.h"
#include "drv/sio/at91Sio.h"


/* Driver Initialization Parameters */
LOCAL AT91_SIO_CHAN_PARAM at91SioParams[] = {

    {INT_LVL_SYS,    INT_VEC_SYS,  AT91C_BASE_DBGU},	
    {INT_LVL_US0,    INT_VEC_US0,  AT91C_BASE_US0},

/*   {INT_LVL_US1,    INT_VEC_US1,  1},
    {INT_LVL_US2,    INT_VEC_US2,  2},
    {INT_LVL_US3,    INT_VEC_US3,  3},*/
};

/* Array of all serial channels configured in system. */
LOCAL AT91_SIO_CHAN at91SioChan[N_SIO_CHANNELS];


/******************************************************************************
*
* sysSerialHwInit - initialize the BSP serial devices to a quiescent state
*
* This routine initializes the BSP serial device descriptors and puts the
* devices in a quiesent state. It is called from sysHwInit() with interrupts
* locked.
*
* RETURNS: N/A
*
* SEE ALSO: sysHwInit()
*/

void sysSerialHwInit(void)
{
    int i;

    for (i=0; i<N_SIO_CHANNELS; i++)
    {
        at91SioChan[i].intLvl  = at91SioParams[i].intLvl;
        at91SioChan[i].intVec  = at91SioParams[i].intVec;
		
       /* at91SioChan[i].ch        = at91SioParams[i].ch;*/
	at91SioChan[i].base  = at91SioParams[i].base;
        at91SioDevInit(&at91SioChan[i]);
/*        LED_ON(LED_ALL_MASK); */
    }
}

/******************************************************************************
*
* sysSerialHwInit2 - connect BSP serial device interrupts
*
* This routine connects the BSP serial device interrupts. It is called from
* sysHwInit2(). Serial device interrupts could not be connected in
* sysSerialHwInit() because the kernel memory allocator was not initialized at
* that point, and intConnect() may call malloc().
*
* RETURNS: N/A
*
* SEE ALSO: sysHwInit2()
*/

void sysSerialHwInit2(void)
{
    int i;

    for (i=0; i<N_SIO_CHANNELS; i++)
    {
        /* Connect interrupt. */
        if(at91SioChan[i].intLvl !=INT_LVL_SYS)
        {
	        intConnect(at91SioChan[i].intVec, (VOIDFUNCPTR)at91SioInt, (int)&at91SioChan[i]);
	        
	        /* Enable interrupt. */
	        intEnable(at91SioChan[i].intLvl);
	}
        at91SioDevInit2(&at91SioChan[i]);
    }
}

/******************************************************************************
*
* sysSerialChanGet - get the SIO_CHAN device associated with a serial channel
*
* This routine returns a pointer to the SIO_CHAN device associated with a
* specified serial channel. It is called by usrRoot() to obtain pointers when
* creating the system serial devices '/tyCo/x'. It is also used by the WDB agent
* to locate its serial channel.
*
* RETURNS: A pointer to the SIO_CHAN structure for the channel, or ERROR if the
* channel is invalid.
*/

SIO_CHAN* sysSerialChanGet(
    int channel                                             /* serial channel */
    )
{
    if ((channel < 0) || (channel >= N_SIO_CHANNELS))
    {
        return (SIO_CHAN*)ERROR;
    }

    return ((SIO_CHAN*)&at91SioChan[channel]);
}

/******************************************************************************
*
* sysSerialReset - reset the sio devices to a quiet state
*
* Reset all devices to prevent them from generating interrupts.
*
* This is called from sysToMonitor to shutdown the system gracefully before
* transferring to the boot ROMs.
*
* RETURNS: N/A.
*/

void sysSerialReset(void)
{
    int i;

    for (i=0; i<N_SIO_CHANNELS; i++)
    {
        /* Disable interrupt. */
        intDisable(at91SioChan[i].intLvl);

    }
}




