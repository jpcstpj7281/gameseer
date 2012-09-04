/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBIN.h*/
/** Object              : DMA service for UDP peripheral*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#ifndef AT91_SVC_USBIN
#define AT91_SVC_USBIN


typedef struct _AT91S_SVC_USBIN {
	/* Public Method:*/
	/* ==============*/
	/* TxHandler is invoked by IT handler*/
	void (*Handler) (struct _AT91S_SVC_USBIN *);
	void (*Write) (
		struct _AT91S_SVC_USBIN *,
		const char *,
		unsigned int,
		void (*)(struct _AT91S_SVC_USBIN *));

	/* Private Datas:*/
	/* ==============*/
	/* Callbacks initialized by Read and Write functions*/
	void (*TxComplete) (struct _AT91S_SVC_USBIN *);

	/* One transfer descriptor*/
	char *pBuffer;
	volatile unsigned int bufferSize;
	/* Following stands as UDP static variables*/
	AT91PS_UDP pUdp;        /* Pointer to UDP registers*/
	unsigned char epNb;     /* Endpoint number*/
	unsigned char epSize;   /* Size of the endpoint*/
	unsigned char nbBank;   /* Number of banks (CTL endpoints = 1, FIFO endpoints = 2)*/
	unsigned char eot;      /* used to mark the end of DATA IN stage*/
} AT91S_SVC_USBIN, *AT91PS_SVC_USBIN;

typedef void (*AT91PF_SVC_SVCUSBIN_TxComplete)  (AT91PS_SVC_USBIN);

/** ====================================================================================*/
extern AT91PS_SVC_USBIN AT91F_SVC_USBIN_Open(
	AT91PS_SVC_USBIN pSvcUdp,  /* \arg Pointer to an USBIN service previously allocated*/
	AT91PS_UDP pUdp,            /* \arg Pointer to UDP registers*/
	unsigned char epNb,         /* \arg Endpoint Number*/
	unsigned char epSize,       /* \arg Endpoint Size*/
	unsigned char nbBanks);     /* \arg UDP DPR banks*/

extern void AT91F_SVC_USBIN_Handler(
	AT91PS_SVC_USBIN pSvcUdp);  /* Pointer to an USBIN service*/

extern void AT91F_SVC_USBIN_Write(
	AT91PS_SVC_USBIN pSvcUdp,     /* Pointer to an USBIN service*/
	const char *pBuffer,                 /* Pointer to the client buffer to send*/
	unsigned int bufferSize,       /* Client buffer size*/
	AT91PF_SVC_SVCUSBIN_TxComplete Callback); /* Callback to invoke when buffer is Sent*/

#endif /* AT91_SVC_USBIN*/

