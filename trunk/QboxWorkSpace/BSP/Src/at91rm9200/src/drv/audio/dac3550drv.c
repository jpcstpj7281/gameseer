/* sb16drv.c - Sound Blaster 16 driver implemented for Cyrix MediaGXi CPU */
/* $Revision: 1.5 $ */
/* Copyright 1999-2001 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,21sep01,dat  Fix ANSI violations for diab compiler
01c,27jan00,dmh  Corrected loop bug for audio on small buffers
01b,27oct99,spm  Sounds clean now, but record is still not implemented.
01a,03oct99,spm  created.  8 bit sound is still not working right.
*/

#include "vxWorks.h"
#include "errno.h"
#include "fcntl.h"
#include "intLib.h"
#include "ioLib.h"
#include "iosLib.h"
#include "iv.h"
#include "logLib.h"
#include "lstLib.h"
#include "msgQLib.h"
#include "semLib.h"
#include "stdlib.h"
#include "string.h"
#include "taskLib.h"
#include "AT91RM9200.h"
#include "lib_AT91RM9200.h"
#include "drv/audio/dac3550drv.h"
#ifdef __EK__
/* System function not in any include file.
 */
/* extern char *sysDmaMalloc (int); */
LOCAL DMA_MSG snd_buffer[MAX_DMA_MSGS];

char snd_dmaBuffer[MAX_DMA_MSGS * MAX_DMA_SIZE];


LOCAL int DrvNum;
/*int logBuf[1024];*/
int logIndex = -1;
int stopCount = 0;
#include "wavfile.c"
/* Useful macros.
 */
#define IS_16BITS(x) ((x)->info.sampleSize == 16)

/* Device Methods...
 */
static int sndCreate (SND_DEV *pDev, char *fileName, int mode);
static int sndOpen (SND_DEV *pDev, char *fileName, int flags, int mode);
static int sndClose (int devId);
static int sndRead (int devId, char *buffer, int maxbytes);
static int sndWrite (int devId, char *buffer, int nbytes);
static int sndIoctl (int devId, int function, int arg);

static int dspClose (int devId);
static int dspRead (int devId, char *buffer, int maxbytes);
static int dspWrite (int devId, char *buffer, int nbytes);
static int dspIoctl (int devId, int function, int arg);


/* Interrupt handler and Helper task
 */
static void dspInterrupt (SND_DEV *pDev);
static int dspHelperTask (SND_DEV *pDev);

/* DMA buffer management routines
 */
static int createDmaBuffer (void);
static DMA_MSG *getDmaBuffer (SND_DEV *pDev);
static void freeDmaBuffer (SND_DEV *pDev);

/* Low level register access routines.
 */
static int dsp_init (SND_DEV *pDev);
static int dsp_version (SND_DEV *pDev);
static int dsp_reset (SND_DEV *pDev);
void dsp_output(SND_DEV*pDev ,DMA_MSG* buf );




/* Device creation routines...
 */
STATUS dac3550Drv (void)
{

  if (DrvNum > 0) return OK;

  DrvNum = iosDrvInstall (sndCreate, NULL, sndOpen, sndClose,
			  sndRead, sndWrite, sndIoctl);

  return (DrvNum == ERROR) ? ERROR : OK;
}
LOCAL SND_DEV * dac3550Dev=0;
//STATUS dac3550DevCreate (char *devName, int port, int irq)
DEV_HDR* dac3550DevCreate (char *devName, int port, int irq)
{
  SND_DEV *pDev;

  if (DrvNum < 1)
  {
    errno = S_ioLib_NO_DRIVER;
    return ERROR;
  }
  if(dac3550Dev) 
  	return &(dac3550Dev->devHdr);
  pDev = (SND_DEV *)malloc (sizeof(SND_DEV));
  if (!pDev) return 0;

  bzero ((char *)pDev, sizeof(SND_DEV));
  if(port==0) port = (int)AT91C_BASE_SSC1;
  if(irq==0) irq = AT91C_ID_SSC1;
  pDev->port   = port;
  pDev->irq    = irq;
/*  pDev->dma8   = dma8;
  pDev->dma16  = dma16;
*/
  pDev->devSem = semBCreate (SEM_Q_FIFO, SEM_FULL);
  pDev->intSem = semCCreate (SEM_Q_FIFO, 0);
  pDev->bufSem = semCCreate (SEM_Q_FIFO, MAX_DMA_MSGS);
  pDev->dmaQ   = msgQCreate (MAX_DMA_MSGS, sizeof (DMA_MSG), MSG_Q_FIFO);

  pDev->dmaIndex = 0;

  if (createDmaBuffer () < 0)
  {
    free (pDev);
    return 0;
  }

  if (dsp_init (pDev) < 0)
  {
    free (pDev);
    return 0;
  }



  if (iosDevAdd (&pDev->devHdr, devName, DrvNum) == ERROR)
  {
    free ((char *)pDev);
    return 0;
  }
/*
  pDev->tid = taskSpawn ("tSndTask", TASK_PRIORITY, TASK_OPTIONS,
			 TASK_STACK_SIZE, dspHelperTask, (int)pDev,
			 0, 0, 0, 0, 0, 0, 0, 0, 0);

  if (pDev->tid == ERROR)
  {
    free (pDev);
    return ERROR;
  }
*/
  intConnect (INUM_TO_IVEC (	(irq)), dspInterrupt, (int)pDev);
  dac3550Dev = pDev;
  return &(pDev->devHdr);
}

/* Device methods...
 */
static int sndCreate (SND_DEV *pDev, char *fileName, int mode)
{
  return ERROR;
}

static int sndOpen (SND_DEV *pDev, char *fileName, int flags, int mode)
{
  SND_FD *pSnd = NULL;

  if (semTake (pDev->devSem, 30 * sysClkRateGet()))
  {
    errno = S_ioLib_DEVICE_ERROR;
    return ERROR;
  }
logIndex = -1;
  if (strcmp (fileName, "/dsp") == 0)
  {
    DSP_FD *pDsp;

    if (pDev->pDsp)
    {
      errno = EBUSY;
      goto error;
    }

    if (! (pDsp = malloc (sizeof(DSP_FD))))
    {
      errno = ENOMEM;
      goto error;
    }

    pDsp->dev.pDev    = pDev;
    pDsp->dev.fdClose = dspClose;
    pDsp->dev.fdRead  = dspRead;
    pDsp->dev.fdWrite = dspWrite;
    pDsp->dev.fdIoctl = dspIoctl;

    pDsp->info.rate       = RATE_MAX;
    pDsp->info.stereo     = 1;
    pDsp->info.sampleSize = 16;
    pDsp->info.uLaw       = 0; /* PCM format is default */
	pDsp->dmaDirection = O_WRONLY;
    pDev->pDsp = pDsp;

    pSnd = (SND_FD *)pDsp;
    pDev->dmaAuto = TWO_BUFF_EMPTY;
  }
  
  else
  {
    errno = ENODEV;
    goto error;
  }

error:
  semGive (pDev->devSem);
  return pSnd ? (int)pSnd : ERROR;
}

static int sndClose (int devId)
{
  SND_FD *pSnd = (SND_FD *)devId;

  return pSnd->fdClose (devId);
}

static int sndRead (int devId, char *buffer, int maxbytes)
{
  SND_FD *pSnd = (SND_FD *)devId;

  return pSnd->fdRead (devId, buffer, maxbytes);
}

static int sndWrite (int devId, char *buffer, int nbytes)
{
  SND_FD *pSnd = (SND_FD *)devId;

  return pSnd->fdWrite (devId, buffer, nbytes);
}

static int sndIoctl (int devId, int function, int arg)
{
  SND_FD *pSnd = (SND_FD *)devId;

  return pSnd->fdIoctl (devId, function, arg);
}

/* DSP device methods.
 */
static int dspClose (int devId)
{
  DSP_FD *pDsp = (DSP_FD *)devId;
  SND_DEV *pDev = pDsp->dev.pDev;

  if (semTake (pDev->devSem, 30 * sysClkRateGet()))
  {
    errno = S_ioLib_DEVICE_ERROR;
    return ERROR;
  }

  while (pDev->taskBusy) taskDelay (1);

  pDev->pDsp = NULL;
  free (pDsp);

  semGive (pDev->devSem);

  return OK;
}

static int dspRead (int devId, char *buffer, int maxbytes)
{
  errno = S_ioLib_UNKNOWN_REQUEST;
  return ERROR;
}

static int dspWrite (int devId, char *buffer, int nbytes)
{
  DSP_FD *pDsp = (DSP_FD *)devId;
  SND_DEV *pDev = pDsp->dev.pDev;
  int bytesLeft = nbytes;
  int x;
  DMA_MSG* mDma;



 
  /* Check if we were recording.  If so, wait till all is clear.
   */
  if (pDev->pDsp->dmaDirection != O_WRONLY)
    while (pDev->taskBusy) taskDelay (1);

  while (bytesLeft > 0)
  {
    /*mDma.buffer    = getDmaBuffer (pDev);*/
    mDma = getDmaBuffer (pDev);
    mDma->length    = bytesLeft > MAX_DMA_SIZE ? MAX_DMA_SIZE : bytesLeft;
    mDma->direction = O_WRONLY;

    memcpy (mDma->buffer, buffer, mDma->length);
    if (mDma->length<MAX_DMA_SIZE) {
        bzero(mDma->buffer+mDma->length,MAX_DMA_SIZE-mDma->length);
    } /* endif */


	dsp_output(pDev,mDma);
	
/*	
    msgQSend (pDev->dmaQ, (char *)&mDma, sizeof (mDma),
	      WAIT_FOREVER, MSG_PRI_NORMAL);
*/
    buffer    += mDma->length;
    bytesLeft -= mDma->length;
  }

  return nbytes - bytesLeft;
}

static int dspIoctl (int devId, int function, int arg)
{
  DSP_FD *pDsp = (DSP_FD *)devId;
  SND_DEV *pDev = pDsp->dev.pDev;
    AT91PS_SSC	pSSC = (AT91PS_SSC ) pDev->port;
  union arg_union
  {
    int i;
    long l;
    int *pInt;
    long *pLong;
    snd_info_t *pInfo;
  } u_arg;
  
  u_arg.i = arg;

  switch (function)
  {
    case SNDCTL_DSP_SYNC:
      while (pDev->taskBusy) taskDelay (1);
      return OK;

    case SNDCTL_DSP_GETBLKSIZE:
      *u_arg.pInt = MAX_DMA_SIZE;
      return OK;

    case SNDCTL_DSP_SPEED:
      {
	int i = *u_arg.pLong;

	if (i < RATE_MIN) i = RATE_MIN;
	if (i > RATE_MAX) i = RATE_MAX;
	while (pDev->taskBusy) taskDelay (1);
	pDsp->info.rate = i;
	AT91F_SSC_SetBaudrate(pSSC, MCK, pDsp->info.rate*(BITS_BY_SLOT*SLOT_BY_FRAME));
	return OK;
      }

    case SNDCTL_DSP_STEREO:
      while (pDev->taskBusy) taskDelay (1);
      pDsp->info.stereo = *u_arg.pInt;
      return OK;

    case SNDCTL_DSP_SAMPLESIZE:
      if (*u_arg.pInt == 8 || *u_arg.pInt == 16)
      {
	while (pDev->taskBusy) taskDelay (1);
	pDsp->info.sampleSize = *u_arg.pInt;
	return OK;
      }
      break;
    case SNDCTL_DSP_SETFORMAT:
      pDsp->info.uLaw = *u_arg.pInt;
      return OK;
      break;
    case SNDCTL_GET_INFO:
      *u_arg.pInfo = pDsp->info;
      return OK;

    case SNDCTL_SET_INFO:
      while (pDev->taskBusy) taskDelay (1);
      pDsp->info = *u_arg.pInfo;
      return OK;
  }
  errno = S_ioLib_UNKNOWN_REQUEST;
  return ERROR;
}


#if 0

static void processOutput (SND_DEV *pDev, DMA_MSG mDma)
{
  int dmaChannel = 0;
  AT91PS_SSC	pSSC = (AT91PS_SSC)pDev->port;
  if (pDev->pDsp->dmaDirection != O_WRONLY )
  {
    pDev->dmaAuto = 0;

    pDev->pDsp->dmaDirection = mDma.direction;
  }

  if (pDev->dmaAuto)
  {
    if (mDma.length != MAX_DMA_SIZE)
    {
      /* If this was the interrupt from the middle of the block,
       * then wait around for the next one.
       */
      if (pDev->dmaAuto)
      {
	pDev->dmaAuto = 0;

	if (semTake (pDev->intSem, 5 * sysClkRateGet()))
	  logMsg ("SB16: Interrupt timeout\n", 0, 0, 0, 0, 0, 0);

	freeDmaBuffer (pDev);
      }

    
      /* Setup a one-shot.
       */
	cacheFlush(DATA_CACHE,mDma.buffer, mDma.length);
/*      dmaSetup (DMA_MODE_SINGLE | DMA_MODE_WRITE,
		mDma.buffer, mDma.length, dmaChannel);
*/
      /* Send out this block.
       */
       AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR), (char *)mDma.buffer, mDma.length/2);	       
      /*dsp_output (pDev->pDsp, mDma.length);*/
    }
  }
  else
  {
    
    if (mDma.buffer == snd_dmaBuffer && mDma.length == MAX_DMA_SIZE)
    {
      pDev->dmaAuto = 2;

      cacheFlush(DATA_CACHE,snd_dmaBuffer,  MAX_DMA_MSGS * MAX_DMA_SIZE);
	
/*      dmaSetup (DMA_MODE_SINGLE | DMA_MODE_WRITE | DMA_MODE_AUTO_ENABLE,
		snd_dmaBuffer, MAX_DMA_MSGS * MAX_DMA_SIZE, dmaChannel);
*/
      /* Check for the next buffer available when half the buffer
       * has been transferred.
       */
      /*mDma.length >>= 1;*/

    }
    else
    {
	cacheFlush(DATA_CACHE,mDma.buffer, mDma.length);
     /* dmaSetup (DMA_MODE_SINGLE | DMA_MODE_WRITE,
		mDma.buffer, mDma.length, dmaChannel);*/
      /*AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR), (char *)mDma.buffer, mDma.length/2);	 */
    }

    /* Send out this block.
     */
    AT91F_PDC_SetTx ((AT91PS_PDC) &(pSSC->SSC_RPR),		
					 (char *)mDma.buffer,
					 mDma.length/2);
/*    AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR), (char *)(mDma.buffer+mDma.length), mDma.length/2);	  					      */
  }
}
#endif
/* Interrupt handler and Helper task
 */



static void dspInterrupt (SND_DEV *pDev)
{
	volatile unsigned int status;
	  AT91PS_SSC	pSSC = (AT91PS_SSC)pDev->port;
    /* Get status and acknowledge IT*/
     status = pSSC->SSC_SR;	
    /* Reload the PDC*/
   /* logBuf[++logIndex]=status;*/
    		

    		
    if(pDev->dmaAuto) 
    {
    	pDev->dmaAuto--;
/*    	if(!pDev->dmaAuto)
    	{
	    	AT91F_SSC_DisableIt (pSSC, AT91C_SSC_ENDTX);
			AT91F_PDC_DisableTx ((AT91PS_PDC) &(pSSC->SSC_RPR));	
	    	AT91F_SSC_DisableTx (pSSC);
    	}*/
    	freeDmaBuffer (pDev);
    }else
    {
    	/*AT91F_SSC_DisableIt (pSSC, AT91C_SSC_ENDTX);
		AT91F_PDC_DisableTx ((AT91PS_PDC) &(pSSC->SSC_RPR));	
    	AT91F_SSC_DisableTx (pSSC);*/
    	stopCount++;
    	if( status & AT91C_SSC_TXBUFE)
	    {
	    	AT91F_SSC_DisableIt (pSSC, AT91C_SSC_ENDTX);
	    	return;
	    }   
    }
 
  /*  
    if(status& AT91C_SSC_TXBUFE)
    {
	    AT91F_SSC_DisableIt (pSSC, AT91C_SSC_ENDTX);
		AT91F_PDC_DisableTx ((AT91PS_PDC) &(pSSC->SSC_RPR));	
    	AT91F_SSC_DisableTx (pSSC);
    	pDev->dmaAuto=TWO_BUFF_EMPTY ;
    }else
    {
    	if(pDev->dmaAuto) 
    		pDev->dmaAuto--;
    	else 
    	{
	 	    AT91F_SSC_DisableIt (pSSC, AT91C_SSC_ENDTX);
			AT91F_PDC_DisableTx ((AT91PS_PDC) &(pSSC->SSC_RPR));	
	    	AT91F_SSC_DisableTx (pSSC);
	    	pDev->dmaAuto=TWO_BUFF_EMPTY ;   		
    	}
    		
    }
    if(status& AT91C_SSC_ENDTX)*/
  
 /*   semGive (pDev->intSem);*/
    /*AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR), (char *)wav_file, AT91C_WAV_FILE_SIZE/2);*/
}

static int dspHelperTask (SND_DEV *pDev)
{
	if (semTake (pDev->intSem, WAIT_FOREVER))
		logMsg ("SB16: Interrupt timeout\n", 0, 0, 0, 0, 0, 0);
	if(pDev->dmaAuto>TWO_BUFF_EMPTY)
	{	
		pDev->dmaAuto--;	
		if(pDev->dmaAuto==TWO_BUFF_EMPTY)
		{
			AT91PS_SSC	pSSC = (AT91PS_SSC ) pDev->port;
			AT91F_SSC_DisableTx (pSSC);
		}
		freeDmaBuffer (pDev);
	}else logMsg ("DAC3550: buffer error\n", 0, 0, 0, 0, 0, 0);	
	
}

#if 0
static int dspHelperTask (SND_DEV *pDev)
{

  DMA_MSG mDma;

  while (1)
  {
    pDev->taskBusy = pDev->dmaAuto = 0;


    if (msgQReceive (pDev->dmaQ, (char *)&mDma,
		     sizeof (mDma), WAIT_FOREVER) != sizeof (mDma))
      return 0;

    pDev->taskBusy = 1;


    do
    {
      switch (mDma.direction)
      {
	case O_WRONLY:
	  processOutput (pDev, mDma);
	  break;
	case O_RDONLY:
	  break;
      }

      /* wait for a DMA interrupt
       */
	if (semTake (pDev->intSem, 5 * sysClkRateGet()))
		logMsg ("SB16: Interrupt timeout\n", 0, 0, 0, 0, 0, 0);

	if (pDev->dmaAuto)
	{
		/* We can do this, because we know the stream will be
		 * non-contiguous if any properties change (rate, direction, etc).
		 */
		while (pDev->dmaAuto)
		{
			pDev->dmaAuto--;
			if (pDev->dmaAuto)
			{
				if (msgQReceive (pDev->dmaQ, (char *)&mDma,
					     sizeof (mDma), NO_WAIT) != sizeof (mDma))
				{
					pDev->dmaAuto = 0;
				}
			}
			else
			{
			    /* Great, we can keep going with 2 more interrupts to follow.
			     */
				pDev->dmaAuto = 2;
				
				freeDmaBuffer (pDev);
			}
			
			/* wait for the next DMA interrupt
			*/
			if (semTake (pDev->intSem, 5 * sysClkRateGet()))
				logMsg ("SB16: Interrupt timeout\n", 0, 0, 0, 0, 0, 0);
		}

	/* We can't do any more DMA continuously.
	 */
	
	}

	freeDmaBuffer (pDev);

    } while (msgQReceive (pDev->dmaQ, (char *)&mDma,
			  sizeof (mDma), NO_WAIT) == sizeof (mDma));
  }
}
#endif

/* DMA buffer management routines
 */

/* DMA buffers are never grabbed by the interrupt routine
 */
static int createDmaBuffer (void)
{
/*   snd_dmaBuffer = sysDmaMalloc (MAX_DMA_MSGS * MAX_DMA_SIZE); */
  int i=0;
/*  bzero (snd_buffer, sizeof(snd_buffer));*/
  for(	i=0;i<MAX_DMA_MSGS;i++)
  {
  	snd_buffer[i].buffer=snd_dmaBuffer + MAX_DMA_SIZE*i;
  }
  return snd_buffer ? OK : ERROR;
}

static DMA_MSG *getDmaBuffer (SND_DEV *pDev)
{
  DMA_MSG *dmaBuffer;

  semTake (pDev->bufSem, WAIT_FOREVER);

  semTake (pDev->devSem, WAIT_FOREVER);
/*  dmaBuffer = snd_dmaBuffer + pDev->dmaIndex * MAX_DMA_SIZE;*/
  dmaBuffer = &snd_buffer[pDev->dmaIndex];
  pDev->dmaIndex = (pDev->dmaIndex + 1) % MAX_DMA_MSGS;
  semGive (pDev->devSem);

  return dmaBuffer;
}

/* DMA buffers are always freed by the interrupt routine
 */
static void freeDmaBuffer (SND_DEV *pDev)
{
  semGive (pDev->bufSem);
}


/* Low level register access routines.
 */
static int dsp_init (SND_DEV *pDev)
{
  int version;
  AT91PS_SSC	pSSC = (AT91PS_SSC ) pDev->port;
	  /* Initialization the DSP
	   */
   /* ============================= Init SSC1 in Output mode =============================*/
	/* Configure SSC1 PIOs  TF/TK/TD  */
	*AT91C_PIOB_PDR=    ((unsigned int) AT91C_PB7_TK1 ) |
	                    ((unsigned int) AT91C_PB8_TD1 ) |
	                    ((unsigned int) AT91C_PB6_TF1 );
	
	/* Configure PMC by enabling SSC1 clock    */
	AT91F_SSC1_CfgPMC(); 
	/* Reset All the Peripheral */
	pSSC->SSC_CR = AT91C_SSC_SWRST ;
	
	/* Clear Transmit and Receive Counters*/
	AT91F_PDC_Close((AT91PS_PDC) &(pSSC->SSC_RPR));
	
	/* Define the Clock Mode Register at 2*16*44100 => 1.4112 MHz */

	AT91F_SSC_SetBaudrate(pSSC, MCK, FILE_SAMPLING_FREQ*(BITS_BY_SLOT*SLOT_BY_FRAME));
	
	/* Write the Transmit Frame Mode Register*/
	pSSC->SSC_TFMR =  I2S_ASY_TX_FRAME_SETTING(BITS_BY_SLOT, SLOT_BY_FRAME);
	
	/* Configure AIC controller to handle SSC interrupts*/
/*	AT91F_AIC_ConfigureIt (
		AT91C_BASE_AIC,                        
		AT91C_ID_SSC1,                         
		IRQ_LEVEL_I2S,                         
		AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, 
		AT91F_ASM_I2S_Handler );*/
	/* Enable SSC interrupt in AIC*/
	AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SSC1);

  return 0;
}


static	int __div = 2;
void dsp_output(SND_DEV*pDev ,DMA_MSG* buf )
{
	int lockKey;

  AT91PS_SSC	pSSC = (AT91PS_SSC ) pDev->port;
  //printErr ("dsp_output: dmaAuto = %d\n", pDev->dmaAuto);
lockKey	     = intLock();  
	if(pDev->dmaAuto==TWO_BUFF_EMPTY)
	{
	   
		AT91F_PDC_SetTx ((AT91PS_PDC) &(pSSC->SSC_RPR),	
						 (char *)buf->buffer,	
						 buf->length/__div);

/*		AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR),	
						 (char *)(buf->buffer+buf->length/2),	
						 buf->length/4);
*/						 		
		AT91F_SSC_EnableIt (pSSC, AT91C_SSC_ENDTX);
	   
		AT91F_PDC_EnableTx ((AT91PS_PDC) &(pSSC->SSC_RPR));	
	
		
	        /* Write the Transmit Clock Mode Register and Enable TK and TF*/
		pSSC->SSC_TCMR =  I2S_ASY_MASTER_TX_SETTING(BITS_BY_SLOT, SLOT_BY_FRAME);
		pDev->dmaAuto++;	
		AT91F_SSC_EnableTx (pSSC);
		
	}else /*if(pDev->dmaAuto==ONE_BUFF_READY)*/
	{

		AT91F_PDC_SetNextTx ((AT91PS_PDC) &(pSSC->SSC_RPR),
			         (char *)buf->buffer, 
			         buf->length/__div);
		pDev->dmaAuto++;	         

/*	}else
	{
		logMsg ("DAC3550 : Error\n", 0, 0, 0, 0, 0, 0);*/
	}
	    intUnlock(lockKey);
}


/**
$Log: sb16drv.c,v $
Revision 1.5  1999/12/18 00:01:38  steveh
Corrected loop bug for audio on small buffers.
Connected up fwd,back and stop buttons.
Attempted to connect up logic to display link that mouse is over,
but api seems to not work for this.

Revision 1.4  1999/12/03 06:52:09  steveh
Created new IOCTL to set 8-bit uLaw format in SB driver.
Moved uLaw code from java to driver.

*/

#else
STATUS dac3550Drv (void)
{
  return ERROR ;
}
#endif










