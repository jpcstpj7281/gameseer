/**----------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : AT91_SVC_USBCTL.h*/
/** Object              : DMA service for USB control endpoint*/
/***/
/** 1.0 Jul 30 2002 	: ODi Creation*/
/**----------------------------------------------------------------------------*/
#ifndef AT91_SVC_USBCTL
#define AT91_SVC_USBCTL



typedef struct _AT91S_SVC_USBCTL {
	/* Public Method:*/
	/* ==============*/
	/* TxHandler is invoked by IT handler*/
	void (*Handler) (struct _AT91S_SVC_USBCTL *);
	/* Read return the number of bytes read in circular buffer*/
	void (*Read) (
		struct _AT91S_SVC_USBCTL *,
		char *, unsigned int,
		void (*)(struct _AT91S_SVC_USBCTL *));
	void (*Write) (
		struct _AT91S_SVC_USBCTL *,
		const char *, unsigned int,
		void (*)(struct _AT91S_SVC_USBCTL *));

	/* Private Datas:*/
	/* ==============*/
	/* Callbacks initialized by Read and Write functions*/
	void (*DisptachSetup) (struct _AT91S_SVC_USBCTL *);
	void (*RWComplete) (struct _AT91S_SVC_USBCTL *);

	char pSetup[8];
	/* One transfer descriptor*/
	char *pBuffer;
	unsigned int bufferSize;
	/* Following stands as UDP static variables*/
	AT91PS_UDP pUdp;        /* Pointer to UDP registers*/
	char eot;
} AT91S_SVC_USBCTL, *AT91PS_SVC_USBCTL;

typedef void (*AT91PF_SVC_USBCTL_DispatchSetup)  (AT91PS_SVC_USBCTL);
typedef void (*AT91PF_SVC_USBCTL_RWComplete)  (AT91PS_SVC_USBCTL);

/** ====================================================================================*/
extern AT91PS_SVC_USBCTL AT91F_SVC_USBCTL_Open(
	AT91PS_SVC_USBCTL pSvcUdp,  /* \arg Pointer to an USBCTL service previously allocated*/
	AT91PS_UDP pUdp);           /* \arg Pointer to UDP registers*/

extern void AT91F_SVC_USBCTL_Handler(
	AT91PS_SVC_USBCTL pSvcUdp);    /* Pointer to an USBCTL service*/

extern void AT91F_SVC_USBCTL_Write(
	AT91PS_SVC_USBCTL pSvcUdp,     /* Pointer to an USBCTL service*/
	const char *pBuffer,                 /* Pointer to the client buffer to send*/
	unsigned int bufferSize,       /* Client buffer size*/
	AT91PF_SVC_USBCTL_RWComplete Callback); /* Callback to invoke when buffer is Sent*/

extern void AT91F_SVC_USBCTL_Read(
	AT91PS_SVC_USBCTL pSvcUdp,     /* Pointer to an USBCTL service*/
	char *pBuffer,          /* Pointer to the client buffer to fill*/
	unsigned int bufferSize,       /* Client buffer size*/
	AT91PF_SVC_USBCTL_RWComplete Callback); /* Callback to invoke when buffer is Full*/

#endif /* AT91_SVC_USBCTL*/

