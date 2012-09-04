/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBIN.c*/
/** Object              : DMA service for UDP peripheral*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#include "AT91_SVC_USBIN.h"


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBIN_Open*/
/** \brief Open USBIN service.*/
/**----------------------------------------------------------------------------*/
AT91PS_SVC_USBIN AT91F_SVC_USBIN_Open(
	AT91PS_SVC_USBIN pSvcUdp,  /* \arg Pointer to an USBIN service previously allocated*/
	AT91PS_UDP pUdp,            /* \arg Pointer to UDP registers*/
	unsigned char epNb,         /* \arg Endpoint Number*/
	unsigned char epSize,       /* \arg Endpoint Size*/
	unsigned char nbBanks)      /* \arg UDP DPR banks*/
{
	pSvcUdp->Handler = AT91F_SVC_USBIN_Handler;
	pSvcUdp->Write   = AT91F_SVC_USBIN_Write;

	pSvcUdp->TxComplete    = (AT91PF_SVC_SVCUSBIN_TxComplete) 0;

	pSvcUdp->pBuffer = (char *) 0;
	pSvcUdp->bufferSize = 0;

	pSvcUdp->pUdp = pUdp;
	pSvcUdp->epNb = epNb;
	pSvcUdp->epSize = epSize;
	pSvcUdp->nbBank = nbBanks;
	pSvcUdp->eot    = 0;


	return pSvcUdp;
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBIN_Handler*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBIN_Handler(
	AT91PS_SVC_USBIN pSvcUdp)     /* \arg Pointer to an USBIN service*/
{
	AT91PS_UDP    pUdp = pSvcUdp->pUdp; /* Pointer to UDP registers*/
	unsigned char epNb = pSvcUdp->epNb; /* Endpoint number*/
	unsigned int  epCsr =  AT91F_UDP_EpStatus(pUdp, epNb);
	unsigned int  bytesToSend;
	
	/* Test if the previous DATA IN is achieved*/
	if (epCsr & AT91C_UDP_TXCOMP) {
		AT91F_UDP_EpClear(pUdp, epNb, AT91C_UDP_TXCOMP);
		/* Test if this was the last packet to be sent*/
		if (pSvcUdp->eot) {
			AT91F_UDP_DisableIt(pUdp, (1 << epNb));
			if (pSvcUdp->TxComplete)
				pSvcUdp->TxComplete(pSvcUdp);
		}
		else {
			/* Start the transmition of the previous prepared packet (ping pong endpoints)*/
			if (pSvcUdp->nbBank > 1)
				AT91F_UDP_EpEndOfWr(pUdp, epNb);
	
			if (pSvcUdp->bufferSize == 0)
				pSvcUdp->eot = 1;
			else {
				/* Prepare the next packet*/
				bytesToSend = (pSvcUdp->bufferSize < pSvcUdp->epSize) ?
					pSvcUdp->bufferSize : pSvcUdp->epSize;
				pSvcUdp->bufferSize -= bytesToSend;
				while (bytesToSend--)
					AT91F_UDP_EpWrite(pUdp, epNb, *(pSvcUdp->pBuffer)++);
				/* Start the transmition of the next prepared packet (no ping pong endpoints)*/
				if (pSvcUdp->nbBank == 1)
					AT91F_UDP_EpEndOfWr(pUdp, epNb);
			}
		}
	}

	/* Test if a STALL has been acknowledged...*/
	else if (epCsr) { /* !!!!! Should be: AT91C_UDP_STALLSENT) {*/
		AT91F_UDP_EpClear(pUdp, epNb, (epCsr));
	}

}


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SVC_USBIN_Write*/
/** \brief*/
/**----------------------------------------------------------------------------*/
void AT91F_SVC_USBIN_Write(
	AT91PS_SVC_USBIN pSvcUdp,     /* \arg Pointer to an USBIN service*/
	const char *pBuffer,                 /* \arg Pointer to the client buffer to send*/
	unsigned int bufferSize,       /* \arg Client buffer size*/
	AT91PF_SVC_SVCUSBIN_TxComplete Callback) /* \arg Callback to invoke when buffer is Sent*/
{
	AT91PS_UDP   pUdp = pSvcUdp->pUdp; /* Pointer to UDP registers*/
	char epNb = pSvcUdp->epNb; /* Endpoint number*/
	unsigned int  bytesToSend;

	pSvcUdp->TxComplete  = Callback;

	/* Send a Zero Length Packet*/
	if (bufferSize == 0) {
		AT91F_UDP_EpEndOfWr(pUdp, epNb);
		pSvcUdp->eot = 1;
	}
	
	/* Send just one packet*/
	else if (bufferSize <= pSvcUdp->epSize) {
		while (bufferSize--)
			AT91F_UDP_EpWrite(pUdp, epNb, *(pBuffer)++);
		/* Allow this bank to be sent*/
		AT91F_UDP_EpEndOfWr(pUdp, epNb);
		pSvcUdp->eot = 1;
	}
	
	/* Send a full packet and prepare the next one if (ping pong endpoints)*/
	else {
		bytesToSend = pSvcUdp->epSize;
		bufferSize -= bytesToSend;
		while (bytesToSend--)
			AT91F_UDP_EpWrite(pUdp, epNb, *(pBuffer)++);
		AT91F_UDP_EpEndOfWr(pUdp, epNb);
		if (pSvcUdp->nbBank > 1) {
			bytesToSend = (bufferSize > pSvcUdp->epSize) ?
				pSvcUdp->epSize : bufferSize;
			bufferSize -= bytesToSend;
			while (bytesToSend--)
				AT91F_UDP_EpWrite(pUdp, epNb, *(pBuffer)++);
		}
		pSvcUdp->pBuffer     = (char *)pBuffer;
		pSvcUdp->bufferSize  = bufferSize;
		pSvcUdp->eot     = 0;
	}
		
	AT91F_UDP_EnableIt(pUdp, (1 << epNb));
}
