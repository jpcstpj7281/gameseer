/* s3c2510Sio.c - at91rm9200 UART controller driver */




#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"


#include "config.h"
#include "drv/intrCtl/at91Intr.h"
#include "drv/sio/at91Sio.h"
#include "lib_AT91RM9200.h"

#define UART_PUT_CR(port,v)	port->US_CR = v
#define UART_GET_MR(port)	port->US_MR
#define UART_PUT_MR(port,v)	port->US_MR = v
#define UART_PUT_IER(port,v)	port->US_IER = v
#define UART_PUT_IDR(port,v)	port->US_IDR = v
#define UART_GET_IMR(port)	port->US_IMR
#define UART_GET_CSR(port)	port->US_CSR
#define UART_GET_CHAR(port)	port->US_RHR
#define UART_PUT_CHAR(port,v)	port->US_THR = v
#define UART_GET_BRGR(port)	port->US_BRGR
#define UART_PUT_BRGR(port,v)	port->US_BRGR = v
#define UART_PUT_RTOR(port,v)	port->US_RTOR = v

/* #define UART_GET_CR(port)  port->US_CR    // is write-only*/

 /* PDC registers */
#define UART_PUT_PTCR(port,v)	port->US_PTCR = v
#define UART_PUT_RPR(port,v)	port->US_RPR = v
#define UART_PUT_RCR(port,v)	port->US_RCR = v
#define UART_GET_RCR(port)	port->US_RCR
#define UART_PUT_RNPR(port,v)	port->US_RNPR = v
#define UART_PUT_RNCR(port,v)	port->US_RNCR = v

#define DEFAULT_BAUD                    115200

/* Local Forward Declarations */


LOCAL int       at91SioBaudSet(AT91_SIO_CHAN *pChan, int baudRate);
LOCAL int       at91SioOptsSet(AT91_SIO_CHAN *pChan, int options);
LOCAL int       at91SioModeSet(AT91_SIO_CHAN *pChan, int sioMode);
LOCAL int       at91SioOpen(AT91_SIO_CHAN *pChan);
LOCAL int       at91SioHup(AT91_SIO_CHAN *pChan);


LOCAL int       at91SioIoctl(SIO_CHAN *pSioChan, int cmd, void* arg);
LOCAL int       at91SioTxStartup(SIO_CHAN *pSioChan);
LOCAL int       at91SioCallbackInstall(SIO_CHAN *pSioChan, int callbackType, STATUS(*callback)(), void *callbackArg);
LOCAL int       at91SioPollInput(SIO_CHAN *pSioChan, char *inChar);
LOCAL int       at91SioPollOutput(SIO_CHAN *pSioChan, char outChar);

/* Driver Function Table */
LOCAL AT91_SIO_CHAN *pDbgUChan = 0;
LOCAL SIO_DRV_FUNCS at91SioDrvFuncs = {
    at91SioIoctl,
    at91SioTxStartup,
    at91SioCallbackInstall,
    at91SioPollInput,
    at91SioPollOutput
};

/*******************************************************************************
*
* at91SioDummyCallback - dummy callback routine.
*
* RETURNS: ERROR, always.
*/

LOCAL STATUS at91SioDummyCallback(void)
{
    return ERROR;
}

/******************************************************************************
*
* at91SioDevInit - initialize a UART
*
* This routine is called to initialize the chip to a quiescent state. Note that
* the `ch' field of at91_CHAN must be less than or equal to the maximum
* number of UART channels to configure as SIOs, as defined in at91.h
*
* RETURNS: N/A
*/

void at91SioDevInit(
    AT91_SIO_CHAN *pChan                                 /* device to initialize */
    )
{
AT91PS_USART port=(AT91PS_USART) pChan->base;
if(pChan->base==(void*)AT91C_BASE_DBGU)
{

	AT91F_DBGU_CfgPIO();


	AT91F_US_Configure (
		(AT91PS_USART) AT91C_BASE_DBGU, /* DBGU base address*/
		AT91C_MASTER_CLOCK,             				/* MCK*/
		AT91C_US_ASYNC_MODE,  			/* mode Register to be programmed*/
		DEFAULT_BAUD ,              		/* baudrate to be programmed*/
		0);                   			/* timeguard to be programmed*/

		
	/* Enable peripheral clock if required 
	AT91_SYS->PMC_PCER = 1 << AT91C_ID_US0;
	
	 * Finally, clear and enable interrupts
	 */
	pDbgUChan = pChan;
   	pChan->read_status_mask = AT91C_US_RXRDY | AT91C_US_TXRDY | AT91C_US_OVRE
			| AT91C_US_FRAME | AT91C_US_PARE | AT91C_US_RXBRK|AT91C_US_TXEMPTY;
	UART_PUT_IDR(port, -1);
	UART_PUT_CR(port, AT91C_US_TXEN | AT91C_US_RXEN);  /* enable xmit & rcvr */
	UART_PUT_IER(port, AT91C_US_RXRDY);  



}else
{
        AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA,AT91C_PIO_PA17 | AT91C_PIO_PA18,0);
    	/* First, enable the clock of the PIOB*/
    	AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1<<AT91C_ID_US0 ) ;
	/* Usart Configure*/
	AT91F_US_Configure (port, AT91C_MASTER_CLOCK,AT91C_US_ASYNC_MODE, DEFAULT_BAUD, 0);
	/* Enable usart */
	UART_PUT_CR(port, AT91C_US_TXEN | AT91C_US_RXEN);  /* enable xmit & rcvr */
	
   	pChan->read_status_mask = AT91C_US_RXRDY | AT91C_US_TXRDY | AT91C_US_OVRE
			| AT91C_US_FRAME | AT91C_US_PARE | AT91C_US_RXBRK|AT91C_US_TXEMPTY;
				
     /* Enable USART IT error and AT91C_US_ENDRX*/
   	AT91F_US_EnableIt(port,AT91C_US_TIMEOUT | AT91C_US_FRAME | AT91C_US_OVRE |AT91C_US_ENDRX|AT91C_US_TXEMPTY);
     /* open Usart 1 interrupt*/
	/*AT91F_AIC_ConfigureIt ( AT91C_BASE_AIC, AT91C_ID_US1, USART_INTERRUPT_LEVEL,AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, usart_asm_irq_handler); 
	
	AT91F_AIC_EnableIt (AT91C_BASE_AIC, AT91C_ID_US1); */
      /* set time out US_RTOR
      * Arm time out after 255 * 4  bits time 
      * for 115200 bit time = 1/115200 = 8.6 micro sec time out unuti= 4* 8.6 = 34 micro
      */
	port->US_RTOR = 0xFFFF;
     /*Enable usart SSTO*/
	port->US_CR = AT91C_US_STTTO;

}
	
    /* Initialize each channel's structure. */

    pChan->pDrvFuncs    = &at91SioDrvFuncs;

    pChan->getTxChar    = at91SioDummyCallback;
    pChan->putRcvChar   = at91SioDummyCallback;

    at91SioBaudSet(pChan, DEFAULT_BAUD);
    at91SioOptsSet(pChan, CREAD | CS8);
    at91SioModeSet(pChan, SIO_MODE_POLL);
    
/*    	while(*buffer != '\0') {
		while (!AT91F_US_TxReady((AT91PS_USART)AT91C_BASE_DBGU));
		AT91F_US_PutChar((AT91PS_USART)AT91C_BASE_DBGU, *buffer++);
	}*/
}

/******************************************************************************
*
* at91SioDevInit2 - initialize a UART, part 2
*
* This routine is called by the BSP after interrupts have been connected. The
* driver can now operate in interrupt mode. Before this routine is called only
* polled mode operations should be allowed.
*
* RETURNS: N/A
*/

void at91SioDevInit2(
    AT91_SIO_CHAN *pChan                                 /* device to initialize */
    )
{
}

/*******************************************************************************
*
* at91SioIoctl - special device control
*
* This routine handles the IOCTL messages from the user. It supports commands
* to get/set baud rate, mode(INT,POLL), hardware options(parity, number of data
* bits) and modem control(RTS/CTS and DTR/DSR handshakes). The ioctl commands
* SIO_HUP and SIO_OPEN are used to implement the HUPCL(hang up on last close)
* function.
*
* As on a UNIX system, requesting a baud rate of zero is translated into a
* hangup request. The DTR and RTS lines are dropped. This should cause a
* connected modem to drop the connection. The SIO_HUP command will only hangup
* if the HUPCL option is active. The SIO_OPEN function will raise DTR and RTS
* lines whenever it is called. Use the BAUD_RATE=0 function to hangup when HUPCL
* is not active.
*
* The CLOCAL option will disable hardware flow control. When selected, hardware
* flow control is not used. When not selected hardware flow control is based on
* the RTS/CTS signals. CTS is the clear to send input from the other end. It
* must be true for this end to begin sending new characters. In most drivers,
* the RTS signal will be assumed to be connected to the opposite end's CTS
* signal and can be used to control output from the other end. Raising RTS
* asserts CTS at the other end and the other end can send data. Lowering RTS
* de-asserts CTS and the other end will stop sending data. (This is non-EIA
* defined use of RTS).
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioIoctl(
    SIO_CHAN *pSioChan,                                     /* device to control */
    int cmd,                                                /* request code */
    void *arg                                               /* some argument */
    )
{
    AT91_SIO_CHAN *pChan = (AT91_SIO_CHAN *)pSioChan;
    int status = OK;
    int lockKey;

    switch (cmd)
    {
	/* Set the baud rate. */
    case SIO_BAUD_SET:
        /* Disable interrupts during chip access. */
        lockKey = intLock();

        status = at91SioBaudSet(pChan, (int)arg);

        /* Enable interrupts after chip access. */
        intUnlock(lockKey);
        break;

    /* Get the baud rate. */
    case SIO_BAUD_GET:
        *(int *)arg = pChan->baudRate;
        break;

    /* Set the hardware options (as defined in sioLib.h). */
    case SIO_HW_OPTS_SET:
        /* Disable interrupts during chip access. */
        lockKey = intLock();

        status = at91SioOptsSet(pChan, (int)arg);

        /* Enable interrupts after chip access. */
        intUnlock(lockKey);
        break;

    /* Get the hardware options (as defined in sioLib.h). */
    case SIO_HW_OPTS_GET:
        *(int *)arg = pChan->options;
        break;

	/* Set the mode (e.g., to interrupt or polled). */
    case SIO_MODE_SET:
        /* Disable interrupts during chip access. */
        lockKey = intLock();

        status = at91SioModeSet(pChan, (int)arg);

        /* Enable interrupts after chip access. */
        intUnlock(lockKey);
        break;

    /* Get the current mode. */
    case SIO_MODE_GET:
        *(int *)arg = pChan->sioMode;
        break;

    /* Get the available modes. */
    case SIO_AVAIL_MODES_GET:
        *(int *)arg = SIO_MODE_INT | SIO_MODE_POLL;
        break;

    case SIO_OPEN:
        status = at91SioOpen(pChan);
        break;

    case SIO_HUP:
        status = at91SioHup(pChan);
        break;

    default:
        status = ENOSYS;
    }

    return (status);
}

/******************************************************************************
*
* at91SioTxStartup - start the interrupt transmitter
*
* RETURNS: OK on success, ENOSYS if the device is polled-only, or EIO on
* hardware error.
*/

LOCAL int at91SioTxStartup(
    SIO_CHAN *pSioChan                                      /* device to start */
    )
{
    AT91_SIO_CHAN *pChan = (AT91_SIO_CHAN *)pSioChan;
	AT91PS_USART port =(AT91PS_USART) (pChan->base);
    if (pChan->sioMode != SIO_MODE_INT)                     /* polling mode */
    {
        return ENOSYS;
    }

    /* Enable Transmit Holding Register Empty Interrupt. */
    /**at91_UINT(pChan->ch) |= at91_UINT_THEIE;*/
    UART_PUT_IER(port, AT91C_US_TXEMPTY);

    return OK;
}

/******************************************************************************
*
* at91SioCallbackInstall - install ISR callbacks to get/put chars
*
* This driver allows interrupt callbacks for transmitting characters and
* receiving characters. In general, drivers may support other types of callbacks
* too.
*
* RETURNS: OK on success, or ENOSYS for an unsupported callback type.
*/

LOCAL int at91SioCallbackInstall(
    SIO_CHAN *pSioChan,                                     /* device */
    int callbackType,                                       /* type of callback */
    STATUS (*callback)(),                                   /* callback */
    void* callbackArg                                       /* parameter to callback */
    )
{
    AT91_SIO_CHAN *pChan = (AT91_SIO_CHAN *)pSioChan;

    switch (callbackType)
    {
    case SIO_CALLBACK_GET_TX_CHAR:
        pChan->getTxChar    = callback;
        pChan->getTxArg     = callbackArg;
        break;

    case SIO_CALLBACK_PUT_RCV_CHAR:
        pChan->putRcvChar   = callback;
        pChan->putRcvArg    = callbackArg;
        break;

    default:
        return ENOSYS;
    }

    return OK;
}

/******************************************************************************
*
* at91SioPollInput - poll the device for input
*
* RETURNS: OK if a character arrived, EIO on device error, EAGAIN if the input
* buffer if empty, ENOSYS if the device is interrupt-only.
*/

LOCAL int at91SioPollInput(
    SIO_CHAN *pSioChan,                                     /* device to poll */
    char *inChar                                            /* buffer to receive char */
    )
{
    AT91_SIO_CHAN *pChan = (AT91_SIO_CHAN *)pSioChan;
    UINT32 stat;
    AT91PS_USART port =(AT91PS_USART) (pChan->base);
    /*stat =  *at91_USTAT(pChan->ch);*/
    stat = UART_GET_CSR(port);
    /*stat = *at91_USTAT(pChan->ch);*/

    /* If no valid data present, retry later. */
    if (!(stat & AT91C_US_RXRDY))                        /* Receive Data Valid */
    {
        return EAGAIN;
    }

    /* Read character from Receive Data Register. */
    *inChar = UART_GET_CHAR(port); /**inChar = (char)*at91_URXBUF(pChan->ch);*/

    return OK;
}

/*******************************************************************************
*
* at91SioPollOutput - output a character in polled mode
*
* RETURNS: OK if a character arrived, EIO on device error, EAGAIN if the output
* buffer if full. ENOSYS if the device is interrupt-only.
*/

LOCAL int at91SioPollOutput(
    SIO_CHAN *pSioChan,                                     /* device to poll */
    char outChar                                            /* char to transmit */
    )
{
    AT91_SIO_CHAN *pChan = (AT91_SIO_CHAN *)pSioChan;
    UINT32 stat;
    AT91PS_USART port =(AT91PS_USART) (pChan->base);
    /*stat =  *at91_USTAT(pChan->ch);*/
    stat = UART_GET_CSR(port);
    if (!(stat & AT91C_US_TXEMPTY))                        /* Transmit Holding Register Empty */
    {
        return EAGAIN;
    }

    /* Write char to Transmit Data Register. */
    UART_PUT_CHAR(port, outChar);/**at91_UTXBUF(pChan->ch) = (VUINT8)outChar;*/

    return OK;
}



/*
 * Interrupt handler
 */
void at91SioInt(AT91_SIO_CHAN *pChan )
{
	/*struct uart_port *port = dev_id;*/
	char ch = 0; 
	unsigned int status, pending;
  	AT91PS_USART port = 0;
  	if(pChan==0)
  	{
  		pChan = pDbgUChan;
  		if(pChan==0) return;
  	}
  	port =(AT91PS_USART) (pChan->base);
	status = UART_GET_CSR(port);
	pending = status& pChan->read_status_mask;/*& port->read_status_mask;*/
	if (pending) 
	{
		do {
			if (pending & AT91C_US_RXRDY)
			{	
				ch = UART_GET_CHAR(port);
				/* Call callback routine. */
 		               (*pChan->putRcvChar)(pChan->putRcvArg, ch);
			}
			/* Clear the relevent break bits */
			if (pending & AT91C_US_RXBRK) {
				UART_PUT_CR(port, AT91C_US_RSTSTA);
				/*port->icount.brk++;*/

     			 }


			if (pending & (AT91C_US_TXRDY|AT91C_US_TXEMPTY) )
			{
				if ((*pChan->getTxChar)(pChan->getTxArg, &ch) != ERROR)
				{
				/* Write char to Transmit Data Register. */
					UART_PUT_CHAR (port , ch);
				}
				else
				{
				/* Disable Transmit Holding Register Empty Interrupt. */
					UART_PUT_IDR(port, AT91C_US_TXRDY|AT91C_US_TXEMPTY );
					/*pChan->read_status_mask &= ~(AT91C_US_TXRDY|AT91C_US_TXEMPTY);*/
					AT91_SYS->AIC_ICCR = (1<<pChan->intLvl);
					/*UART_PUT_CR(port, AT91C_US_TXDIS );*/
					
					break;
				}
					
			}
			

			status = UART_GET_CSR(port);
			pending = status&(pChan->read_status_mask);/* & port->read_status_mask;*/
		} while (pending);
	}
}


/******************************************************************************
*
* at91SioBaudSet - set the baud rates
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioBaudSet(
    AT91_SIO_CHAN *pChan,                                /* device to control */
    int baudRate                                            /* baud rate */
    )
{
#if 0	
    int cnt;

    if (pChan->ch != 0)                                     /* high-speed UART */
    {
        if (baudRate == 0)                                  /* hangup request */
        {
            return (at91SioHup(pChan));
        }
    }

    /* Calculate the baud rate. */
    cnt = (UART_BRGCLK_FREQ / (baudRate * 16 * (1 << (UART_BRGCLK_DIV_FACTOR * 4)))) - 1;

    /* Baudrate divisor must fit in a 12-bit register. */
    if ((cnt < 0) || (cnt > 0xFFF))
    {
        return EIO;
    }

    /* Write to the Baud Rate Divisor Register. */
    *AT91_UBRD(pChan->ch) = (UINT16)((cnt << AT91_UBRD_CNT_SHIFT) | UART_BRGCLK_DIV_FACTOR);
#endif

  unsigned int mode, imr;
  
  AT91PS_USART port =(AT91PS_USART) (pChan->base);
  /* Get current mode register */
  mode = port->US_MR & ~(AT91C_US_CHRL | AT91C_US_NBSTOP | AT91C_US_PAR);

	/* first, disable interrupts and drain transmitter */
/*	local_irq_save(flags);*/
	imr = UART_GET_IMR(port);	/* get interrupt mask */
	UART_PUT_IDR(port, -1);		/* disable all interrupts */
/*	local_irq_restore(flags);*/
	/*while (!(UART_GET_CSR(port) & AT91C_US_TXEMPTY)) { barrier(); }*/

	/* disable receiver and transmitter */
	UART_PUT_CR(port, AT91C_US_TXDIS | AT91C_US_RXDIS);



	/* set the baud rate */
	UART_PUT_BRGR(port,AT91F_US_Baudrate(AT91C_MASTER_CLOCK ,baudRate) );
	UART_PUT_CR(port, AT91C_US_TXEN | AT91C_US_RXEN);

	/* restore interrupts */
	UART_PUT_IER(port, imr);

	
    pChan->baudRate = baudRate;

    return OK;
}

/******************************************************************************
*
* at91SioOptsSet - set the serial options
*
* Set the channel operating mode to that specified. All sioLib options are
* supported: CLOCAL, HUPCL, CREAD, CSIZE, PARENB, and PARODD.
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioOptsSet(
    AT91_SIO_CHAN *pChan,                                /* device to control */
    int options                                             /* options */
    )
{
#if 0	
    UINT32 ucon;

    /* Set default bits for UART Control Register. */
    ucon = AT91_UCON_RMODE_CPU |                         /* CPU Request */
           AT91_UCON_TMODE_CPU |                         /* CPU Request */
#ifdef  UARTCLK_EXTERNAL
           AT91_UCON_SCSEL_UCLK;                         /* External */
#else   /* UARTCLK_EXTERNAL */
           AT91_UCON_SCSEL_PCLK2;                        /* Internal (PCLK2 = PCLK / 2) */
#endif  /* UARTCLK_EXTERNAL */

    /* Set character size. */
    switch (options & CSIZE)
    {
    case CS5:
        ucon |= AT91_UCON_WL_5;                          /* 5 Bits */
        break;

    case CS6:
        ucon |= AT91_UCON_WL_6;                          /* 6 Bits */
        break;

    case CS7:
        ucon |= AT91_UCON_WL_7;                          /* 7 Bits */
        break;

    case CS8:
        ucon |= AT91_UCON_WL_8;                          /* 8 Bits */
        break;
    }

    /* Set stop bits. */
    if (!(options & STOPB))                                 /* send two stop bits (else one) */
    {
        ucon |= AT91_UCON_STB_1;                         /* One Stop Bit per Frame */
    }
    else
    {
        ucon |= AT91_UCON_STB_2;                         /* Two Stop Bit per Frame */
    }

    /* Set parity. */
    if (!(options & PARENB))                                /* parity detection enabled (else disabled) */
    {
        ucon |= AT91_UCON_PMD_NO;                        /* No Parity */
    }
    else
    {
        if (options & PARODD)                               /* odd parity  (else even) */
        {
            ucon |= AT91_UCON_PMD_ODD;                   /* Odd Parity */
        }
        else
        {
            ucon |= AT91_UCON_PMD_EVEN;                  /* Even Parity */
        }
    }

    if (pChan->ch != 0)                                     /* high-speed UART. */
    {
        ucon |= AT91_HUCON_RFTL_28 |                     /* Receive FIFO Trigger Level */
                AT91_HUCON_TFTL_16 |                     /* Transmit FIFO Trigger Level */
                AT91_HUCON_RFEN |                        /* Receive FIFO Enable */
                AT91_HUCON_TFEN;                         /* Transmit FIFO Enable */

        if (!(options & CLOCAL))                            /* ignore modem status lines */
        {
            ucon |= AT91_HUCON_HFEN |                    /* Hardware Flow Control Enable */
                    AT91_HUCON_RTSRTR_RTS |              /* RTS/RTR Selection */
                    AT91_HUCON_DTR;                      /* Data Terminal Ready to Pin */
        }
    }

    /* Write UART Control Register. */
    *AT91_UCON(pChan->ch) = ucon;
#endif
  unsigned int mode, imr;
  AT91PS_USART port =(AT91PS_USART) (pChan->base);
  
  /* Get current mode register */
  mode = port->US_MR & ~(AT91C_US_CHRL | AT91C_US_NBSTOP | AT91C_US_PAR);

	/* byte size */
	switch (options & CSIZE) {
	case CS5:
		mode |= AT91C_US_CHRL_5_BITS;
		break;
	case CS6:
		mode |= AT91C_US_CHRL_6_BITS;
		break;
	case CS7:
		mode |= AT91C_US_CHRL_7_BITS;
		break;
	default:
		mode |= AT91C_US_CHRL_8_BITS;
		break;
	}

	/* stop bits */
	if (options & STOPB)
		mode |= AT91C_US_NBSTOP_2_BIT;

	/* parity */
	if (options & PARENB) {
		if (options & PARENB) {			/* Mark or Space parity */
			if (options & PARODD)
				mode |= AT91C_US_PAR_MARK;
			else
				mode |= AT91C_US_PAR_SPACE;
		}
		else if (options & PARODD)
			mode |= AT91C_US_PAR_ODD;
		else
			mode |= AT91C_US_PAR_EVEN;
	}
	else
		mode |= AT91C_US_PAR_NONE;




	/* TODO: Ignore all characters if CREAD is set.*/

	/* first, disable interrupts and drain transmitter */
	/*local_irq_save(flags);*/
	imr = UART_GET_IMR(port);	/* get interrupt mask */
	UART_PUT_IDR(port, -1);		/* disable all interrupts */
	/*local_irq_restore(flags);*/
	/*while (!(UART_GET_CSR(port) & AT91C_US_TXEMPTY)) { barrier(); }*/

	/* disable receiver and transmitter */
	UART_PUT_CR(port, AT91C_US_TXDIS | AT91C_US_RXDIS);

	/* set the parity, stop bits and data size */
	UART_PUT_MR(port, mode);

	/* set the baud rate */
/*	UART_PUT_BRGR(port, quot);*/
	UART_PUT_CR(port, AT91C_US_TXEN | AT91C_US_RXEN);

	/* restore interrupts */
	UART_PUT_IER(port, imr);

	/* CTS flow-control and modem-status interrupts */
	/*if (UART_ENABLE_MS(port, cflag))*/
	/*	at91_pops.enable_ms(port);*/
    pChan->options = options;

    return OK;
}

/******************************************************************************
*
* at91SioModeSet - set the channel's SIO mode
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioModeSet(
    AT91_SIO_CHAN *pChan,                                /* device to control */
    int sioMode                                             /* SIO mode */
    )
{
  
    AT91PS_USART uart =(AT91PS_USART) (pChan->base);
    
    if ((sioMode != SIO_MODE_POLL) && (sioMode != SIO_MODE_INT))
    {
        return EIO;
    }
   
 
    if (sioMode == SIO_MODE_INT)                            /* interrupt mode */
    {
              uart->US_IDR = AT91C_US_RXRDY   	|
                   AT91C_US_TXRDY       |
                   AT91C_US_ENDRX       |
                   AT91C_US_ENDTX       |
                   AT91C_US_OVRE    	|
                   AT91C_US_FRAME       |
                   AT91C_US_PARE        |
                   AT91C_US_TXEMPTY     |
                   AT91C_US_TXBUFE  	|
                   AT91C_US_RXBUFF      |
                   AT91C_US_COMM_TX     |
                   AT91C_US_COMM_RX  	|
                   AT91C_US_TIMEOUT	;          
                   
              uart->US_IER = AT91C_US_RXRDY   	|
                   AT91C_US_TXRDY|AT91C_US_TXRDY    /*   |
                   AT91C_US_ENDRX       |
                   AT91C_US_ENDTX       |
                   AT91C_US_OVRE    	|
                   AT91C_US_FRAME       |
                   AT91C_US_PARE        |
                   AT91C_US_TXEMPTY     |
                   AT91C_US_TXBUFE  	|
                   AT91C_US_RXBUFF      |
                   AT91C_US_COMM_TX     |
                   AT91C_US_COMM_RX  */;   
  
    }
    else                                                    /* polling mode */
    {
       /* uart->US_IER = AT91C_US_OVRE    	|
                   AT91C_US_FRAME       |
                   AT91C_US_PARE              ;   */
              uart->US_IDR = AT91C_US_RXRDY   	|
                   AT91C_US_TXRDY       |
                   AT91C_US_ENDRX       |
                   AT91C_US_ENDTX       |
                   AT91C_US_OVRE    	|
                   AT91C_US_FRAME       |
                   AT91C_US_PARE        |
                   AT91C_US_TXEMPTY     |
                   AT91C_US_TXBUFE  	|
                   AT91C_US_RXBUFF      |
                   AT91C_US_COMM_TX     |
                   AT91C_US_COMM_RX  	|
                   AT91C_US_TIMEOUT	;                        
    }

    pChan->sioMode = sioMode;

    return OK;
}

/******************************************************************************
*
* at91SioOpen - set the modem control lines 
*
* Set the modem control lines(RTS, DTR) TRUE if not already set.
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioOpen(
    AT91_SIO_CHAN *pChan                                 /* device to control */
    )
{
    AT91PS_USART uart =(AT91PS_USART) (pChan->base);

    if (pChan->base == (void*) AT91C_BASE_DBGU )                                     /* console UART */
    {
        return ENOSYS;
    }

    if (!(pChan->options & HUPCL))                          /* hang up on last close */
    {
        return ENOSYS;
    }

    if (pChan->options & CLOCAL)                            /* ignore modem status lines */
    {
        return ENOSYS;
    }

    /* Asserts DTR. */
    uart->US_CR |=AT91C_US_DTREN;  			/* Data Terminal Ready to Pin */	


    return OK;
}

/******************************************************************************
*
* at91SioHup - hang up the modem control lines 
*
* Resets the RTS and DTR signals.
*
* RETURNS: OK on success, ENOSYS on unsupported request, EIO on failed request.
*/

LOCAL int at91SioHup(
    AT91_SIO_CHAN *pChan                                 /* device to control */
    )
{
    AT91PS_USART uart =(AT91PS_USART) (pChan->base);
    if (uart == (AT91PS_USART)AT91C_BASE_DBGU)                                     /* console UART */
    {
        return ENOSYS;
    }

    if (!(pChan->options & HUPCL))                          /* hang up on last close */
    {
        return ENOSYS;
    }

    if (pChan->options & CLOCAL)                            /* ignore modem status lines */
    {
        return ENOSYS;
    }

    /* Deasserts DTR. */
        uart->US_CR &=~AT91C_US_DTREN;  			/* Data Terminal Ready to Pin */	

    return OK;
}







