/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBCTL.c*/
/** Object              : DMA service USB device control enpoint*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#include "AT91_SVC_USBCTL.h"


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_Open*/
/** \brief Open USBCTL service.*/
/**----------------------------------------------------------------------------*/
AT91PS_SVC_USBCTL AT91F_SVC_USBCTL_Open(
	AT91PS_SVC_USBCTL pSvcUdp,  /* \arg Pointer to an USBCTL service previously allocated*/
	AT91PS_UDP pUdp)            /* \arg Pointer to UDP registers*/
{
	pSvcUdp->Handler = AT91F_SVC_USBCTL_Handler;
	pSvcUdp->Read    = AT91F_SVC_USBCTL_Read;
	pSvcUdp->Write   = AT91F_SVC_USBCTL_Write;

	pSvcUdp->DisptachSetup = (AT91PF_SVC_USBCTL_DispatchSetup) 0;
	pSvcUdp->RWComplete    = (AT91PF_SVC_USBCTL_RWComplete) 0;

	pSvcUdp->pBuffer = (char *) 0;
	pSvcUdp->bufferSize = 0;
	pSvcUdp->eot = 0;

	pSvcUdp->pUdp = pUdp;


	return pSvcUdp;
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_DataIn*/
/** \brief*/
/**----------------------------------------------------------------------------*/
static void AT91F_SVC_USBCTL_DataIn(
	AT91PS_SVC_USBCTL pSvcUdp,     /* \arg Pointer to an USBCTL service*/
	AT91PS_UDP pUdp)               /* \arg Pointer to UDP registers*/
{
	char *pBuffer;

	/* If bufferSize == 0 Send a Zero length packet*/
	if (pSvcUdp->bufferSize == 0)
		AT91F_UDP_EpEndOfWr(pUdp, 0);

	/* else initialize DPR*/
	else {
		pBuffer = pSvcUdp->pBuffer;
		if (pSvcUdp->bufferSize >= 8) {
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
			pSvcUdp->bufferSize -= 8;
		}
		else while (pSvcUdp->bufferSize--)
			AT91F_UDP_EpWrite(pUdp, 0, *pBuffer++);
		pSvcUdp->pBuffer = pBuffer;
		AT91F_UDP_EpEndOfWr(pUdp, 0);
	}
	pSvcUdp->eot = !(pSvcUdp->bufferSize);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_DataOut*/
/** \brief*/
/**----------------------------------------------------------------------------*/
__inline char AT91F_SVC_USBCTL_DataOut(
	AT91PS_SVC_USBCTL pSvcUdp,     /* \arg Pointer to an USBCTL service*/
	AT91PS_UDP pUdp,               /* \arg Pointer to UDP registers*/
	unsigned int epCsr)            /* \arg Value of the UDP_CSR[0] register*/
{
	unsigned int bytesReceived;
	char eor; /* Detect end of Receive*/

	/* Copy bytes received to the client buffer*/
	bytesReceived = (epCsr & AT91C_UDP_RXBYTECNT) >> 16;
	if (bytesReceived > pSvcUdp->bufferSize)
		bytesReceived = pSvcUdp->bufferSize;
	pSvcUdp->bufferSize -= bytesReceived;
	/* Check the end of a Control OUT sequence: An incomplete packet stops the Data OUT sequence*/
	eor = (bytesReceived < 8);

	while (bytesReceived--)
		*(pSvcUdp->pBuffer)++ = AT91F_UDP_EpRead(pUdp, 0);
	AT91F_UDP_EpClear(pUdp, 0, (AT91C_UDP_RX_DATA_BK0));

	return eor;
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_Handler*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBCTL_Handler(
	AT91PS_SVC_USBCTL pSvcUdp)     /* \arg Pointer to an USBCTL service*/
{
	AT91PS_UDP   pUdp = pSvcUdp->pUdp; /* Pointer to UDP registers*/
	unsigned int epCsr =  AT91F_UDP_EpStatus(pUdp, 0);

	/* Test if a SETUP packet has been received*/
	if (epCsr & AT91C_UDP_RXSETUP) {
		/* Copy the setup packet*/
		pSvcUdp->pSetup[0] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[1] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[2] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[3] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[4] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[5] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[6] = AT91F_UDP_EpRead(pUdp, 0);
		pSvcUdp->pSetup[7] = AT91F_UDP_EpRead(pUdp, 0);
		/* Set the DIR bit before clearing RXSETUP in Control IN sequence*/
		if (pSvcUdp->pSetup[0] & 0x80)
			AT91F_UDP_EpSet(pUdp, 0, AT91C_UDP_DIR);
		/* Clear RXSETUP*/
		AT91F_UDP_EpClear(pUdp, 0, AT91C_UDP_RXSETUP);
		/* Notify the dispatcher*/
		if (pSvcUdp->DisptachSetup)
			pSvcUdp->DisptachSetup(pSvcUdp);
	}

	/* Test if the previous DATA IN packet is achieved*/
	else if (epCsr & AT91C_UDP_TXCOMP) {
		AT91F_UDP_EpClear(pUdp, 0, AT91C_UDP_TXCOMP);
		/* test end of transmission*/
		if (pSvcUdp->eot && pSvcUdp->RWComplete)
			pSvcUdp->RWComplete(pSvcUdp);
		/* else start new packet transfer*/
		else
			AT91F_SVC_USBCTL_DataIn(pSvcUdp, pUdp);
	}

	/* test if any DATA OUT packet occured*/
	else if (epCsr & AT91C_UDP_RX_DATA_BK0) {
		/* Test if this DATA OUT aborts a CONTROL IN sequence*/
		if (!(pSvcUdp->eot) && pSvcUdp->RWComplete)
			pSvcUdp->RWComplete(pSvcUdp);
		if (AT91F_SVC_USBCTL_DataOut(pSvcUdp, pUdp, epCsr) && pSvcUdp->RWComplete)
			pSvcUdp->RWComplete(pSvcUdp);
	}

	/* Test if a STALL has been acknowledged...*/
	else if (epCsr & AT91C_UDP_ISOERROR) { /* !!!!! Should be: AT91C_UDP_STALLSENT) {*/
		AT91F_UDP_EpClear(pUdp, 0, (AT91C_UDP_ISOERROR | AT91C_UDP_FORCESTALL));
	}

}


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_Write*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBCTL_Write(
	AT91PS_SVC_USBCTL pSvcUdp,     /* \arg Pointer to an USBCTL service*/
	const char *pBuffer,                 /* \arg Pointer to the client buffer to send*/
	unsigned int bufferSize,       /* \arg Client buffer size*/
	AT91PF_SVC_USBCTL_RWComplete Callback) /* \arg Callback to invoke when buffer is Sent*/
{
	pSvcUdp->bufferSize  = bufferSize;
	pSvcUdp->pBuffer     = (char *)pBuffer;
	pSvcUdp->RWComplete  = Callback;

	AT91F_SVC_USBCTL_DataIn(pSvcUdp, pSvcUdp->pUdp);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBCTL_Read*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBCTL_Read(
	AT91PS_SVC_USBCTL pSvcUdp,     /* \arg Pointer to an USBCTL service*/
	char *pBuffer,                 /* \arg Pointer to the client buffer to fill*/
	unsigned int bufferSize,       /* \arg Client buffer size*/
	AT91PF_SVC_USBCTL_RWComplete Callback) /* \arg Callback to invoke when buffer is Full*/
{
	if ((bufferSize == 0) && (Callback)) {
		Callback(pSvcUdp);
		return;
	}
	pSvcUdp->bufferSize = bufferSize;
	pSvcUdp->pBuffer    = pBuffer;
	pSvcUdp->RWComplete = Callback;
}

