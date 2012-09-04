/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBOUT.h*/
/** Object              : DMA service for UDP peripheral*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#ifndef AT91_SVC_USBOUT
#define AT91_SVC_USBOUT


/* Following defines are used by TxComplete*/
#define AT91C_SVC_USBOUT_TXABORT 0
#define AT91C_SVC_USBOUT_TXCOMPLETE 0

typedef struct _AT91S_SVC_USBOUT {
	/* Public Method:*/
	/* ==============*/
	/* TxHandler is invoked by IT handler*/
	void (*Handler) (struct _AT91S_SVC_USBOUT *);
	/* Read return the number of bytes read in circular buffer*/
	void (*Read) (
		struct _AT91S_SVC_USBOUT *,
		char *,
		unsigned int,
		void (*)(struct _AT91S_SVC_USBOUT *,int,char));
	/* Private Datas:*/
	/* ==============*/
	/* Callbacks initialized by Read and Write functions*/
	void (*RxComplete) (struct _AT91S_SVC_USBOUT *,int ,char);

	/* There is 2 transfer descriptor to describe the 2 blocs being sent by PDC*/
	unsigned int clrFlag; /* used by AT91F_SVC_DMAUDP_OutEpHandler to know which DATA_BK flag to clear*/
	/* One transfer descriptor*/
	char *pBuffer;
	volatile unsigned int bufferSize;
	/* Following stands as UDP static variables*/
	AT91PS_UDP pUdp;        /* Pointer to UDP registers*/
	unsigned char epNb;     /* Endpoint number*/
	unsigned char epSize;   /* Size of the endpoint*/
	unsigned char nbBank;   /* Number of banks (CTL endpoints = 1, FIFO endpoints = 2)*/
} AT91S_SVC_USBOUT, *AT91PS_SVC_USBOUT;

typedef void (*AT91PF_SVC_SVCUSBOUT_RxComplete)  (AT91PS_SVC_USBOUT,int,char);

/** ====================================================================================*/
extern AT91PS_SVC_USBOUT AT91F_SVC_USBOUT_Open(
	AT91PS_SVC_USBOUT pSvcUdp,  /* \arg Pointer to an USBOUT service previously allocated*/
	AT91PS_UDP pUdp,            /* \arg Pointer to UDP registers*/
	unsigned char epNb,         /* \arg Endpoint Number*/
	unsigned char epSize,       /* \arg Endpoint Size*/
	unsigned char nbBanks);     /* \arg UDP DPR banks*/

extern void AT91F_SVC_USBOUT_Handler(
	AT91PS_SVC_USBOUT pSvcUdp);    /* Pointer to an USBOUT service*/

extern void AT91F_SVC_USBOUT_Read(
	AT91PS_SVC_USBOUT pSvcUdp,     /* Pointer to an USBOUT service*/
	char *pBuffer,          /* Pointer to the client buffer to fill*/
	unsigned int bufferSize,       /* Client buffer size*/
	AT91PF_SVC_SVCUSBOUT_RxComplete Callback); /* Callback to invoke when buffer is Full*/

#endif /* AT91_SVC_USBOUT*/

