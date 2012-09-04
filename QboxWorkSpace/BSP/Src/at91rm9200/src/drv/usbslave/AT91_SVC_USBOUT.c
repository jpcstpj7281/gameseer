/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBOUT.c*/
/** Object              : DMA service for UDP peripheral*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#include "AT91_SVC_USBOUT.h"

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBOUT_Open*/
/** \brief Open USBOUT service.*/
/**----------------------------------------------------------------------------*/
AT91PS_SVC_USBOUT AT91F_SVC_USBOUT_Open(
	AT91PS_SVC_USBOUT pSvcUdp,  /* \arg Pointer to an USBOUT service previously allocated*/
	AT91PS_UDP pUdp,            /* \arg Pointer to UDP registers*/
	unsigned char epNb,         /* \arg Endpoint Number*/
	unsigned char epSize,       /* \arg Endpoint Size*/
	unsigned char nbBanks)      /* \arg UDP DPR banks*/
{
	pSvcUdp->Handler = AT91F_SVC_USBOUT_Handler;
	pSvcUdp->Read    = AT91F_SVC_USBOUT_Read;

	pSvcUdp->RxComplete    = (AT91PF_SVC_SVCUSBOUT_RxComplete) 0;

	pSvcUdp->clrFlag = AT91C_UDP_RX_DATA_BK0;

	pSvcUdp->pBuffer = (char *) 0;
	pSvcUdp->bufferSize = 0;

	pSvcUdp->pUdp = pUdp;
	pSvcUdp->epNb = epNb;
	pSvcUdp->epSize = epSize;
	pSvcUdp->nbBank = nbBanks;


	return pSvcUdp;
}


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBOUT_DataOut*/
/** \brief*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_SVC_USBOUT_DataOut(
	AT91PS_SVC_USBOUT pSvcUdp,     /* \arg Pointer to an USBOUT service*/
	AT91PS_UDP pUdp,               /* \arg Pointer to UDP registers*/
	char epNb,                     /* \arg Pointer to an endpoint number*/
	unsigned int epCsr)            /* \arg Value of the endpoint CSR*/
{
	unsigned int bytesReceived, nbBytes;
    char pool[64],*pPool=pool;
	/* Copy bytes received to the client buffer, check overrun*/
	bytesReceived = (epCsr & AT91C_UDP_RXBYTECNT) >> 16;
	if (pSvcUdp->RxComplete)
			pSvcUdp->RxComplete(pSvcUdp,bytesReceived,epNb);
	else 		
	{
		while (bytesReceived--)
			*pPool++ = AT91F_UDP_EpRead(pUdp, epNb);
	}
#if 0			
	while (bytesReceived > pSvcUdp->epSize) {
		AT91F_UDP_EpRead(pUdp, epNb);
		--bytesReceived;
	}
	if (bytesReceived > pSvcUdp->bufferSize) {
		bytesReceived = pSvcUdp->bufferSize;
	}

	/*if (bytesReceived > pSvcUdp->epSize)
		bytesReceived = pSvcUdp->epSize;
	*/
		
	pSvcUdp->bufferSize -= bytesReceived;
	nbBytes = bytesReceived;
	while (nbBytes--)
		*(pSvcUdp->pBuffer)++ = AT91F_UDP_EpRead(pUdp, epNb);

#endif
	/* Clear AT91C_UDP_RX_DATA_BK0 or AT91C_UDP_RX_DATA_BK1 flag*/
	AT91F_UDP_EpClear(pUdp, epNb, pSvcUdp->clrFlag);
	pSvcUdp->clrFlag = ((pSvcUdp->nbBank > 1) && (pSvcUdp->clrFlag == AT91C_UDP_RX_DATA_BK0)) ?
		AT91C_UDP_RX_DATA_BK1 :
		AT91C_UDP_RX_DATA_BK0;
#if 0
	/* Notify the end of Reception if buffer is full or nb of bytes received < epSize*/
	if (  (!pSvcUdp->bufferSize) || (bytesReceived < pSvcUdp->epSize) ) {
		AT91F_UDP_DisableIt(pUdp, (1 << epNb));
		if (pSvcUdp->RxComplete)
			pSvcUdp->RxComplete(pSvcUdp);
	}
#endif	
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBOUT_Handler*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBOUT_Handler(
	AT91PS_SVC_USBOUT pSvcUdp)     /* \arg Pointer to an USBOUT service*/
{
	AT91PS_UDP    pUdp = pSvcUdp->pUdp; /* Pointer to UDP registers*/
	unsigned char epNb = pSvcUdp->epNb; /* Endpoint number*/
	unsigned int  epCsr =  AT91F_UDP_EpStatus(pUdp, epNb);

	/* test if any DATA OUT occured*/
	if (epCsr & (AT91C_UDP_RX_DATA_BK0 | AT91C_UDP_RX_DATA_BK1)) {
		AT91F_SVC_USBOUT_DataOut(pSvcUdp, pUdp, epNb, epCsr);
	}

	/* Test if a STALL has been acknowledged...*/
	else if (epCsr) { /* !!!!! Should be: AT91C_UDP_STALLSENT) {*/
		AT91F_UDP_EpClear(pUdp, epNb, (epCsr));
	}

}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBOUT_Read*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBOUT_Read(
	AT91PS_SVC_USBOUT pSvcUdp,     /* \arg Pointer to an USBOUT service*/
	char *pBuffer,                 /* \arg Pointer to the client buffer to fill*/
	unsigned int bufferSize,       /* \arg Client buffer size*/
	AT91PF_SVC_SVCUSBOUT_RxComplete Callback) /* \arg Callback to invoke when buffer is Full*/
{
	pSvcUdp->bufferSize = bufferSize;
	pSvcUdp->pBuffer    = pBuffer;
	pSvcUdp->RxComplete = Callback;
	/* Enable endpoint 1 & 2 interrupts*/
	AT91F_UDP_EnableIt(pSvcUdp->pUdp, (1 << pSvcUdp->epNb));
}


