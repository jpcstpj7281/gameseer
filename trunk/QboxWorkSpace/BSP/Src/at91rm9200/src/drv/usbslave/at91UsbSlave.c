/* at91Usb.c - AT91RM9200 USB Slave driver  */




#include "vxWorks.h"
#include "intLib.h"
#include "netLib.h"
#include "end.h"
#include "endLib.h"
#include "cacheLib.h"
#include "miiLib.h"
#include "errno.h"
#include "stdio.h"
#include "logLib.h"
#include "taskLib.h"
#include "eventLib.h"
#include "sys/stat.h"
#include "config.h"
#include "drv/intrCtl/at91Intr.h"
#include "AT91_SVC_USBCTL.c"
#include "AT91_SVC_USBIN.c"
#include "AT91_SVC_USBOUT.c"

//#include "at91_usb_target.c"


typedef struct __trans_header {
	long magic;
	long head_size;
	long target_addr;
	long fsize;
	char filename[32];
} TRANS_HEADER;

int usbTaskID=-1;

#define EV_USB_SLAVE_RCV 1
#define EV_USB_SLAVE_SEND 2
ULONG usbSlaveEvent=EV_USB_SLAVE_RCV|EV_USB_SLAVE_SEND;
//SEM_ID rcvSem = 0,sendSem=0;
static int usbSlaveHelperTask (long );

#undef  DEBUG_TRACE
/*#define DEBUG_LOG(x, p1, p2, p3, p4, p5, p6) \
        logMsg(x, (int)(UINT32)(p1), (int)(UINT32)(p2), (int)(UINT32)(p3), (int)(UINT32)(p4), (int)(UINT32)(p5), (int)(UINT32)(p6))
*/
AT91S_SVC_USBIN    usbEp3;
AT91S_SVC_USBCTL   usbEp0;
AT91S_SVC_USBOUT   usbEp1;
AT91S_SVC_USBIN    usbEp2;
static void at91_usb_int(void);
/* ================================================================ */
/* ===================== Device configuration ===================== */
/* ================================================================ */
/* This is the current configuration.*/
unsigned char currentConfiguration = 0;
unsigned char currentConnection = 0;

const char deviceDescriptor[] = {
	/* Device descriptor */
	0x12,   /* bLength*/
	0x01,   /* bDescriptorType*/
	0x10,   /* bcdUSBL*/
	0x01,   
	0x02,   /* bDeviceClass:    CDC class code*/
	0x00,   /* bDeviceSubclass: CDC class sub code*/
	0x00,   /* bDeviceProtocol: CDC Device protocol*/
	0x08,   /* bMaxPacketSize0*/
	0xEB,   /* idVendorL*/
	0x03,   
	0x22,   /* idProductL*/
	0x61,   
	0x10,   /* bcdDeviceL*/
	0x01,   
	0x00,   /* iManufacturer    // 0x01*/
	0x00,   /* iProduct*/
	0x00,   /* SerialNumber*/
	0x01    /* bNumConfigs*/
};

const char configurationDescriptor[] = {
	/* ============== CONFIGURATION 1 =========== */
	/* Configuration 1 descriptor */
	0x09,   /* CbLength*/
	0x02,   /* CbDescriptorType*/
	0x20,   /* CwTotalLength 2 EP + Control*/
	0x00,
	0x01,   /* CbNumInterfaces*/
	0x01,   /* CbConfigurationValue*/
	0x00,   /* CiConfiguration*/
	0xC0,   /* CbmAttributes 0xA0*/
	0x00,   /* CMaxPower*/

	/* Data Class Interface Descriptor Requirement */
	0x09, /* bLength*/
	0x04, /* bDescriptorType*/
	0x00, /* bInterfaceNumber*/
	0x00, /* bAlternateSetting*/
	0x02, /* bNumEndpoints*/
	0x00, /* bInterfaceClass*/
	0x00, /* bInterfaceSubclass*/
	0x00, /* bInterfaceProtocol*/
	0x00, /* iInterface*/

	/* First alternate setting */
	/* Endpoint 1 descriptor */
	0x07,   /* bLength*/
	0x05,   /* bDescriptorType*/
	0x01,   /* bEndpointAddress, Endpoint 01 - OUT*/
	0x02,   /* bmAttributes      BULK*/
	0x40,   /* wMaxPacketSize*/
	0x00,
	0x00,   /* bInterval*/

	/* Endpoint 2 descriptor */
	0x07,   /* bLength*/
	0x05,   /* bDescriptorType*/
	0x82,   /* bEndpointAddress, Endpoint 02 - IN*/
	0x02,   /* bmAttributes      BULK*/
	0x40,   /* wMaxPacketSize*/
	0x00,
	0x00    /* bInterval*/
};


/* USB standard request code */
#define STD_GET_STATUS_ZERO           0x0080 
#define STD_GET_STATUS_INTERFACE      0x0081
#define STD_GET_STATUS_ENDPOINT       0x0082

#define STD_CLEAR_FEATURE_ZERO        0x0100
#define STD_CLEAR_FEATURE_INTERFACE   0x0101
#define STD_CLEAR_FEATURE_ENDPOINT    0x0102

#define STD_SET_FEATURE_ZERO          0x0300
#define STD_SET_FEATURE_INTERFACE     0x0301
#define STD_SET_FEATURE_ENDPOINT      0x0302

#define STD_SET_ADDRESS               0x0500
#define STD_GET_DESCRIPTOR            0x0680
#define STD_SET_DESCRIPTOR            0x0700
#define STD_GET_CONFIGURATION         0x0880
#define STD_SET_CONFIGURATION         0x0900
#define STD_GET_INTERFACE             0x0A81
#define STD_SET_INTERFACE             0x0B01
#define STD_SYNCH_FRAME               0x0C82

/* CDC Class Specific Request Code */
#define GET_LINE_CODING               0x21A1
#define SET_LINE_CODING               0x2021
#define SET_CONTROL_LINE_STATE        0x2221

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetDescriptorDevice*/
/** \brief Answer to a standard GET DESCRIPTOR request*/
/**----------------------------------------------------------------------------*/
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
__inline void AT91F_USB_GetDescriptorDevice(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned short wLength = *((unsigned short *) &(pUSBCTL->pSetup[6]));
	pUSBCTL->Write(pUSBCTL,
		deviceDescriptor,
		MIN(sizeof(deviceDescriptor), wLength),
		(AT91PF_SVC_USBCTL_RWComplete) 0);    /* No callback*/
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetDescriptorConfiguration*/
/** \brief Answer to a standard GET DESCRIPTOR request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_GetDescriptorConfiguration(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned short wLength = *((unsigned short *) &(pUSBCTL->pSetup[6]));
	pUSBCTL->Write(pUSBCTL,
		configurationDescriptor,
		MIN(sizeof(configurationDescriptor), wLength),
		(AT91PF_SVC_USBCTL_RWComplete) 0);    /* No callback*/
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetAddress*/
/** \brief Answer to a standard SET ADDRESS request*/
/**----------------------------------------------------------------------------*/
void AT91F_USB_SetAddressComplete(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned char address = pUSBCTL->pSetup[2];

	/* Set Address*/
	AT91F_UDP_SetAddress(pUSBCTL->pUdp, address);
	if (address)
		/* Move the UDP function to the addressed state*/
		AT91F_UDP_SetState(pUSBCTL->pUdp, AT91C_UDP_FADDEN);
	else
		/* Move the UDP function to the default state*/
		AT91F_UDP_SetState(pUSBCTL->pUdp, 0);
}

__inline void AT91F_USB_SetAddress(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	/* UDP address change must be done once STATUS IN is achieved*/
	pUSBCTL->Write(pUSBCTL,	(char *) 0,	0, AT91F_USB_SetAddressComplete);
}


/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetConfiguration*/
/** \brief Answer to a standard SET CONFIGURATION request*/
/**----------------------------------------------------------------------------*/
void AT91F_USB_SetConfigurationComplete(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/

	/* Move the UDP function to the configured state*/
	AT91F_UDP_SetState(pUdp, AT91C_UDP_CONFG);

	/* Enable endpoints*/
	AT91F_UDP_EpSet(pUdp, 1, AT91C_UDP_EPEDS);
	AT91F_UDP_EpSet(pUdp, 2, AT91C_UDP_EPEDS);
	AT91F_UDP_EpSet(pUdp, 3, AT91C_UDP_EPEDS);

	/* Enable endpoint 1 & 2 interrupts*/
	AT91F_SVC_USBIN_Open(&usbEp3, AT91C_BASE_UDP, 3, 8, 1);
/*	AT91F_UDP_EnableIt(pUdp, (AT91C_UDP_EPINT1 | AT91C_UDP_EPINT2 | AT91C_UDP_EPINT3));*/
	usbStartRead();
}

__inline void AT91F_USB_SetConfiguration(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/
	AT91PF_SVC_USBCTL_RWComplete RWComplete = (AT91PF_SVC_USBCTL_RWComplete) 0; /* Callback*/

	/* Store the current configuration*/
	currentConfiguration = pUSBCTL->pSetup[2];

	/* Move to the Configured State*/
	if (currentConfiguration) {
		/* Reset  endpoints*/
		AT91F_UDP_ResetEp(pUdp, (AT91C_UDP_EPINT1 | AT91C_UDP_EPINT2 | AT91C_UDP_EPINT3));
		AT91F_UDP_ResetEp(pUdp, 0);
		/*AT91F_UDP_EnableEp(pUdp, (AT91C_UDP_EPINT1 | AT91C_UDP_EPINT2));*/

		/* Configure endpoints and enable them*/
		AT91F_UDP_EpSet(pUdp, 1, (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_OUT)); /* Endpoint 1 is a bulk out*/
		AT91F_UDP_EpSet(pUdp, 2, (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_IN));  /* Endpoint 2 is a bulk in*/
		AT91F_UDP_EpSet(pUdp, 3, (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_ISO_IN));   /* Endpoint 3 is a INT in*/

		/* Init the Callback after STATUS IN*/
		RWComplete = AT91F_USB_SetConfigurationComplete;
	}

	/* Move back to the Address State*/
	else {
		/* Move the UDP function to the addressed state*/
		AT91F_UDP_SetState(pUdp, AT91C_UDP_FADDEN);

		/* Enable endpoints*/
		AT91F_UDP_EpClear(pUdp, 1, AT91C_UDP_EPEDS);
		AT91F_UDP_EpClear(pUdp, 2, AT91C_UDP_EPEDS);

	}
	/* Send a STATUS IN*/
	pUSBCTL->Write(pUSBCTL,	(char *) 0,	0, RWComplete);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetConfiguration*/
/** \brief Answer to a standard GET CONFIGURATION request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_GetConfiguration(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/

	/* Send the current configuration*/
	AT91F_UDP_EpWrite(pUdp, 0, currentConfiguration);
	AT91F_UDP_EpEndOfWr(pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetStatusZero*/
/** \brief Answer to a standard GET STATUS ZERO request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_GetStatusZero(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/

	/* Return no Remote wakeup, not self powered (Cf. Fig 9.4 in USB Spec Rev 1.1)*/
	AT91F_UDP_EpWrite(pUdp, 0, 0);
	AT91F_UDP_EpWrite(pUdp, 0, 0);
	AT91F_UDP_EpEndOfWr(pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetStatusInterface*/
/** \brief Answer to a standard GET STATUS INTERFACE request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_GetStatusInterface(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/

	/* Return 0 (Cf. Fig 9.5 in USB Spec Rev 1.1)*/
	AT91F_UDP_EpWrite(pUdp, 0, 0);
	AT91F_UDP_EpWrite(pUdp, 0, 0);
	AT91F_UDP_EpEndOfWr(pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_GetStatusEndpoint*/
/** \brief Answer to a standard GET STATUS ENDPOINT request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_GetStatusEndpoint(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/
	unsigned char endpoint = (pUSBCTL->pSetup[4] & 0x7F);

	/* Return halt or not (Cf. Fig 9.6 in USB Spec Rev 1.1)*/
	if ((AT91F_UDP_GetState(pUdp) != AT91C_UDP_CONFG) ||  (endpoint > 3))
		AT91F_UDP_EpStall(pUdp, 0);
	else {
		if (AT91F_UDP_EpStatus(pUdp, endpoint) & AT91C_UDP_EPEDS)
			AT91F_UDP_EpWrite(pUdp, 0, 1);
		else
			AT91F_UDP_EpWrite(pUdp, 0, 0);
		AT91F_UDP_EpWrite(pUdp, 0, 0);
		AT91F_UDP_EpEndOfWr(pUdp, 0);
	}
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetFeatureZero*/
/** \brief Answer to a standard SET FEATURE ZERO request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_SetFeatureZero(
	AT91PS_SVC_USBCTL pUSBCTL)
{
    /* Device feature RWUp is not supported STALL it*/
	AT91F_UDP_EpStall(pUSBCTL->pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetFeatureInterface*/
/** \brief Answer to a standard SET FEATURE INTERFACE request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_SetFeatureInterface(
	AT91PS_SVC_USBCTL pUSBCTL)
{
    /* Assumed RFU...*/
    /* Send a zero length packet*/
	AT91F_UDP_EpEndOfWr(pUSBCTL->pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetFeatureEndpoint*/
/** \brief Answer to a standard SET FEATURE ENDPOINT request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_SetFeatureEndpoint(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/
	unsigned char endpoint = (pUSBCTL->pSetup[4] & 0x7F);

    /* If Feature different from ENDPOINT_HALT, Stall the request !!! (Cf table 9.6 in USB Spec. )*/
	if (pUSBCTL->pSetup[2])
		AT91F_UDP_EpStall(pUdp, 0);

	if ((AT91F_UDP_GetState(pUdp) != AT91C_UDP_CONFG) ||  (endpoint < 1) || (endpoint > 3))
		AT91F_UDP_EpStall(pUdp, 0);
	else {
		/* Disable the endpoint*/
		AT91F_UDP_DisableEp(pUdp, endpoint);
    	/* Send a zero length packet*/
		AT91F_UDP_EpEndOfWr(pUdp, 0);
	}
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_ClrFeatureZero*/
/** \brief Answer to a standard CLEAR FEATURE ZERO request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_ClrFeatureZero(
	AT91PS_SVC_USBCTL pUSBCTL)
{
    /* Device feature RWUp is not supported STALL it*/
	AT91F_UDP_EpStall(pUSBCTL->pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_ClrFeatureInterface*/
/** \brief Answer to a standard CLEAR FEATURE INTERFACE request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_ClrFeatureInterface(
	AT91PS_SVC_USBCTL pUSBCTL)
{
    /* Assumed RFU...*/
    /* Send a zero length packet*/
	AT91F_UDP_EpEndOfWr(pUSBCTL->pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_ClrFeatureEndpoint*/
/** \brief Answer to a standard CLEAR FEATURE ENDPOINT request*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_USB_ClrFeatureEndpoint(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/
	unsigned char endpoint = (pUSBCTL->pSetup[4] & 0x7F);

    /* If Feature different from ENDPOINT_HALT, Stall the request !!! (Cf table 9.6 in USB Spec. )*/
	if (pUSBCTL->pSetup[2])
		AT91F_UDP_EpStall(pUdp, 0);

	if ((AT91F_UDP_GetState(pUdp) != AT91C_UDP_CONFG) ||  (endpoint < 1) || (endpoint > 3))
		AT91F_UDP_EpStall(pUdp, 0);
	else {
		/* Disable the endpoint*/
		AT91F_UDP_EnableEp(pUdp, endpoint);
    	/* Send a zero length packet*/
		AT91F_UDP_EpEndOfWr(pUdp, 0);
	}
}

char serialState[] = {
	0xA1, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

char networkConnection[] = {
	0xA1, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00
	};

typedef struct {
	unsigned int dwDTERRate;
	char bCharFormat;
	char bParityType;
	char bDataBits;
} AT91S_CDC_LINE_CODING, *AT91PS_CDC_LINE_CODING;

	
AT91S_CDC_LINE_CODING lineCoding = {
	921600, /* baudrate*/
	0,      /* 1 Stop Bit*/
	2,      /* None Parity*/
	8};     /* 8 Data bits*/

	
/**----------------------------------------------------------------------------*/
/** \fn    AT91F_CDC_GetLineCoding*/
/** \brief This request allows the host to find out the currently configured line coding*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_CDC_GetLineCoding(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned short wLength = *((unsigned short *) &(pUSBCTL->pSetup[6]));
	pUSBCTL->Write(pUSBCTL,
		(const char *) &lineCoding,
		MIN(sizeof(lineCoding), wLength),
		(AT91PF_SVC_USBCTL_RWComplete) 0);    /* No callback*/
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_CDC_SetLineCodingComplete*/
/** \brief AT91F_CDC_SetLineCodingComplete once AT91F_CDC_SetLineCoding is achieved*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_CDC_SetLineCodingComplete(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	AT91PS_UDP   pUdp = pUSBCTL->pUdp; /* Pointer to UDP registers*/
	/* Send a STATUS IN*/
	AT91F_UDP_EpEndOfWr(pUdp, 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_CDC_SetLineCoding*/
/** \brief This request allows the host to specify typical asynchronous line-characterformatting properties*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_CDC_SetLineCoding(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned short wLength = *((unsigned short *) &(pUSBCTL->pSetup[6]));
	pUSBCTL->Read(pUSBCTL,
		(char *) &lineCoding,
		MIN(sizeof(lineCoding), wLength),
		(AT91PF_SVC_USBCTL_RWComplete) AT91F_CDC_SetLineCodingComplete);    /* No callback*/
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_SetAddress*/
/** \brief Answer to a standard SET ADDRESS request*/
/**----------------------------------------------------------------------------*/
void AT91F_CDC_NotificationComplete(
	AT91PS_SVC_USBIN pUSBIN)
{
	usbEp3.Write(&usbEp3, networkConnection, sizeof(networkConnection), (AT91PF_SVC_SVCUSBIN_TxComplete) 0);

}

void AT91F_CDC_SetControlLineStateComplete(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	currentConnection = pUSBCTL->pSetup[2];
	if (currentConnection == 3)
		usbEp3.Write(&usbEp3, serialState, sizeof(serialState), (AT91PF_SVC_SVCUSBIN_TxComplete) 0);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_CDC_SetControlLineState*/
/** \brief This request allows the host to specify typical asynchronous line-characterformatting properties*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_CDC_SetControlLineState(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	/*AT91PS_UDP   pUdp = pUSBCTL->pUdp; // Pointer to UDP registers*/
	/* Send a STATUS IN*/
	pUSBCTL->Write(pUSBCTL,	(char *) 0,	0, AT91F_CDC_SetControlLineStateComplete);
	/*AT91F_UDP_EpEndOfWr(pUdp, 0);*/
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_USB_DispatchRequest*/
/** \brief This function is a callback invoked when a SETUP packet is received*/
/**----------------------------------------------------------------------------*/
void AT91F_USB_DispatchRequest(
	AT91PS_SVC_USBCTL pUSBCTL)
{
	unsigned short request = *((unsigned short *) pUSBCTL->pSetup);

	/* Handle supported standard device request Cf Table 9-3 in USB specification Rev 1.1*/
	if ((request == STD_GET_DESCRIPTOR) && (pUSBCTL->pSetup[3] == 1))
		AT91F_USB_GetDescriptorDevice(pUSBCTL);
	else if ((request == STD_GET_DESCRIPTOR) && (pUSBCTL->pSetup[3] == 2))
		AT91F_USB_GetDescriptorConfiguration(pUSBCTL);
	else if (request == STD_SET_ADDRESS)             AT91F_USB_SetAddress(pUSBCTL);
	else if (request == STD_SET_CONFIGURATION)       AT91F_USB_SetConfiguration(pUSBCTL);
	else if (request == STD_GET_CONFIGURATION)       AT91F_USB_GetConfiguration(pUSBCTL);
	else if (request == STD_GET_STATUS_ZERO)         AT91F_USB_GetStatusZero(pUSBCTL);
	else if (request == STD_GET_STATUS_INTERFACE)    AT91F_USB_GetStatusInterface(pUSBCTL);
	else if (request == STD_GET_STATUS_ENDPOINT)     AT91F_USB_GetStatusEndpoint(pUSBCTL);
	else if (request == STD_SET_FEATURE_ZERO)        AT91F_USB_SetFeatureZero(pUSBCTL);
	else if (request == STD_SET_FEATURE_INTERFACE)   AT91F_USB_SetFeatureInterface(pUSBCTL);
	else if (request == STD_SET_FEATURE_ENDPOINT)    AT91F_USB_SetFeatureEndpoint(pUSBCTL);
	else if (request == STD_CLEAR_FEATURE_ZERO)      AT91F_USB_ClrFeatureZero(pUSBCTL);
	else if (request == STD_CLEAR_FEATURE_INTERFACE) AT91F_USB_ClrFeatureInterface(pUSBCTL);
	else if (request == STD_CLEAR_FEATURE_ENDPOINT)  AT91F_USB_ClrFeatureEndpoint(pUSBCTL);

	/* handle CDC class requests*/
	else if (request == SET_LINE_CODING) AT91F_CDC_SetLineCoding(pUSBCTL);
	else if (request == GET_LINE_CODING) AT91F_CDC_GetLineCoding(pUSBCTL);
	else if (request == SET_CONTROL_LINE_STATE) AT91F_CDC_SetControlLineState(pUSBCTL);
	/* Unsupported requests*/
	else
		AT91F_UDP_EpStall(pUSBCTL->pUdp, 0);
}

#define BUFFER_SIZE 64
char pBuffer[BUFFER_SIZE];


TRANS_HEADER gTransHeader,gReplyHeader;


char* downloadAddress=(char*)-1;
long downloadFileSize=0;
long receivedSize = 0;
char* malloced_ptr = 0;


//long uploadAddress=-1,uploadSize=0;
//long gMagic=0;

LOCAL char * transmitBuf=0;
void usbSentCallBack(AT91PS_SVC_USBIN pUsbIn)
{
	if(	gReplyHeader.magic==0x87654321)
	{
		if(transmitBuf !=0 )
		{
			gReplyHeader.magic=0;
			usbEp2.Write(&usbEp2,transmitBuf,gReplyHeader.fsize,usbSentCallBack);
		}else
		{
			memset(&gReplyHeader,0,sizeof(gReplyHeader));
		}
	}else 
	{
		if(transmitBuf)
		{
			free(transmitBuf);transmitBuf=0;
			memset(&gReplyHeader,0,sizeof(gReplyHeader));
		}
	}
}


void usbReceiveCallBack(AT91PS_SVC_USBOUT pSvcUdp,int bytesReceived,char epNb)
{
	int count=0;
	if(downloadFileSize==0)
	{
		char *pHeader = (char*) &gTransHeader;
		if( bytesReceived<sizeof(gTransHeader) )
		{
			while (bytesReceived--)
				(void)AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
			return;	
		}
	

		while (bytesReceived-- && count<sizeof(gTransHeader))
		{
			*(pHeader)++ = AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
			count++;
		}
		bytesReceived++ ;
	 	if(gTransHeader.magic==0x12345678)/* download request */
	 	{
		 	downloadAddress=(char*)  gTransHeader.target_addr;
			downloadFileSize= gTransHeader.fsize-sizeof(gTransHeader);
			receivedSize = 0;
		 	/*downloadAddress=  *(long*)(downPt+4);
			downloadFileSize= *(long*)(downPt+8);*/
			if(downloadAddress==(char*)-1||downloadAddress==0)
			{
				malloced_ptr = (char*) malloc( downloadFileSize);
				if(malloced_ptr==0)
				{
					
				}else
					downloadAddress =  malloced_ptr;
				gTransHeader.target_addr =(long)downloadAddress;
			}				
			while (bytesReceived-- )
			{
				*(downloadAddress)++ = AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
				receivedSize++;
			}
			bytesReceived++;
			
   		}else if(gTransHeader.magic==0x87654321) /*upload request */
   		{
// 			uploadAddress = gTransHeader.target_addr;
//			uploadSize = gTransHeader.fsize;
   			//usbEp2.Write(&usbEp2,(char*)uploadAddress,uploadSize,usbSentCallBack);
   			if(gReplyHeader.magic!=0x87654321){
	   			memcpy(&gReplyHeader,&gTransHeader,sizeof(gReplyHeader));
				eventSend(usbTaskID,EV_USB_SLAVE_SEND);
			}

   		}else
   		{
			while (bytesReceived--)
				(void)AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
			bytesReceived++;	
			downloadAddress = (char*)-1;
			memset(&gTransHeader,0,sizeof(gTransHeader));
   		}
   		
	}else
	{
		if(gTransHeader.magic==0x12345678)
		{
			if(receivedSize>=downloadFileSize)
			{
				while (bytesReceived-- )
				{
					(void) AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
				}
				bytesReceived++;
			}else
			{
				while (bytesReceived-- )
				{
					*(downloadAddress)++ = AT91F_UDP_EpRead(pSvcUdp->pUdp, epNb);
					receivedSize++;
				}
				bytesReceived++;
			}
			if(receivedSize==downloadFileSize)
			{   //AT91F_UDP_DisableIt(pSvcUdp->pUdp, (1 << epNb));
				//semGive(rcvSem);downloadFileSize=0;
				eventSend(usbTaskID,EV_USB_SLAVE_RCV);
			}
	  	}
	}
	//AT91F_UDP_EnableIt(pSvcUdp->pUdp, (1 << pSvcUdp->epNb));
}


/*******************************************************************************
*
* at91UsbInit - initialize S3C2510 USB
*
* RETURNS: OK, or ERROR.
*/
#define TASK_PRIORITY    0
#define TASK_OPTIONS     0
#define TASK_STACK_SIZE  2048


STATUS at91UsbSlaveInit(void)
{
	int i;

    /* Disable interrupt. */
    intDisable(INT_LVL_UDP);
	AT91F_UDP_CfgPMC();                        /* Enable UDP peripheral*/
	AT91C_BASE_PMC->PMC_SCER |= AT91C_PMC_UDP; /* Enable 48 MHz*/
	/* Open DMA service for each endpoint*/
	AT91F_SVC_USBCTL_Open(&usbEp0, AT91C_BASE_UDP);
	usbEp0.DisptachSetup = AT91F_USB_DispatchRequest;
	AT91F_SVC_USBOUT_Open(&usbEp1, AT91C_BASE_UDP, 1, 64, 2);
	AT91F_SVC_USBIN_Open(&usbEp2, AT91C_BASE_UDP, 2, 64, 2);
#if 0
	/* eConfigure AIC controller to handle USB interrupts*/
	AT91F_AIC_ConfigureIt (
		AT91C_BASE_AIC,                        /* AIC base address*/
		AT91C_ID_UDP,                          /* System peripheral ID*/
		AT91C_AIC_PRIOR_HIGHEST,               /* Max priority*/
		AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, /* Level sensitive*/
		AT91F_ASM_UDP_Handler );

	/* Enable Udp interrupt in AIC*/
	AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_UDP);
#endif	
	/* Enable UDP pullUp (PIOA10 on AT91RM3400DK)*/
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PIO_PA10);
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, AT91C_PIO_PA10);

	AT91F_PIO_CfgOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);	
	
    AT91F_PIO_CfgOutput(AT91C_BASE_PIOC, (1 << 15) | (1 << 14));
    /* reset endpoints */
 /*   	
	AT91F_UDP_ResetEp(AT91C_BASE_UDP, (AT91C_UDP_EPINT1 | AT91C_UDP_EPINT2));
	AT91F_UDP_ResetEp(AT91C_BASE_UDP, 0);    
*/
    /* Connect interrupt. */
    intConnect(INT_VEC_UDP, (VOIDFUNCPTR)at91_usb_int, 0);

    /* Disable interrupt. */
    intEnable(AT91C_ID_UDP);
    
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);
	for(i=0;i<500000;i++);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);    
 
   //  sendSem = semCCreate (SEM_Q_FIFO, 0);
  //  rcvSem = semCCreate (SEM_Q_FIFO, 0);
    usbTaskID = taskSpawn ("tUsbSlaveTask", TASK_PRIORITY, TASK_OPTIONS,
			 TASK_STACK_SIZE, usbSlaveHelperTask, 0,
			 0, 0, 0, 0, 0, 0, 0, 0, 0);
			 
	memset(&gTransHeader,0,sizeof(gTransHeader));
	memset(&gReplyHeader,0,sizeof(gReplyHeader));		 
    usbEp1.Read(&usbEp1, pBuffer, BUFFER_SIZE, usbReceiveCallBack);

    return OK;
} 

int usbStartRead()
{
//	AT91F_PIO_ClearOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5);
//	AT91F_PIO_SetOutput(AT91C_BASE_PIOD, AT91C_PIO_PD5); 
    usbEp1.Read(&usbEp1, pBuffer, BUFFER_SIZE, usbReceiveCallBack);
    return 0;
}
/*---------------------------------------------------------------------------*/
/* \fn    AT91F_UDP_Handler*/
/* \brief This function is invoked by AT91F_ASM_UDP_Handler*/
/* This function is for demonstration purpose only*/
/*----------------------------------------------------------------------------*/
static void at91_usb_int(void)
{
	unsigned int interrupt = (AT91C_BASE_UDP->UDP_ISR  & AT91C_BASE_UDP->UDP_IMR);
	
	AT91F_PIO_SetOutput(AT91C_BASE_PIOC, (1 << 14));
	while (interrupt ) {
		if (interrupt & AT91C_UDP_ENDBUSRES) {
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_ENDBUSRES;		
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_ENDBUSRES;	
			/* reset all endpoints	*/
			AT91F_UDP_ResetEp(AT91C_BASE_UDP, (AT91C_UDP_EPINT1 | AT91C_UDP_EPINT2));
			AT91F_UDP_ResetEp(AT91C_BASE_UDP, 0);
			/*AT91F_UDP_EnableEp(AT91C_BASE_UDP, (AT91C_UDP_EPINT0));*/
			AT91F_UDP_EpSet(AT91C_BASE_UDP, 0, (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_CTRL)); /* Endpoint 1 is a ctl endpoint		*/
			AT91F_UDP_EnableIt(AT91C_BASE_UDP, AT91C_UDP_EPINT0);
		}
		else if (interrupt & AT91C_UDP_EPINT0) {
			usbEp0.Handler(&usbEp0);
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_EPINT0;		
		}
		
		else if (interrupt & AT91C_UDP_EPINT1) {
			usbEp1.Handler(&usbEp1);
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_EPINT1;
		}
		
		else if (interrupt & AT91C_UDP_EPINT2) {
			usbEp2.Handler(&usbEp2);
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_EPINT2;
		}

		else if (interrupt & AT91C_UDP_EPINT3) {
			usbEp3.Handler(&usbEp3);
			AT91C_BASE_UDP->UDP_ICR = AT91C_UDP_EPINT3;
		}
		
		else {
			AT91C_BASE_UDP->UDP_ICR = interrupt;
		}
		interrupt = (AT91C_BASE_UDP->UDP_ISR  & AT91C_BASE_UDP->UDP_IMR);
	}
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOC, (1 << 14));
}


static int usbSlaveHelperTask (long l)
{
  FILE *f;
  char szfile[32];
  UINT32 ev;
  while (1)
  {
    
    //if (semTake (rcvSem, WAIT_FOREVER)==0)
    if(OK==eventReceive(usbSlaveEvent,EVENTS_WAIT_ANY,WAIT_FOREVER,&ev))
    {
    	if(ev&EV_USB_SLAVE_RCV)
    	{
	    	if(malloced_ptr)
	    	{
		    	sprintf(szfile,"/ram0/%s",gTransHeader.filename);
		    	f = fopen(szfile,"w");
				if(f)
				{
			 	   	fwrite((char*)gTransHeader.target_addr ,1, gTransHeader.fsize-sizeof(gTransHeader),f);
					if(malloced_ptr)
					{
						free(malloced_ptr);malloced_ptr=0;
					}	 	   	
					fclose(f);downloadFileSize=0;
				}
			}
		}
		if(ev&EV_USB_SLAVE_SEND)
    	{
    		struct stat sa;
	    	sprintf(szfile,"%s",gReplyHeader.filename);
			if(stat(szfile,&sa)==OK)
			{
	    		f = fopen(szfile,"r");
				if(f)
				{
			 	   	transmitBuf = (char*)malloc(sa.st_size);
			 	   	if(transmitBuf)
			 	   	{
			 	   	fread( transmitBuf ,1, sa.st_size,f);
			 	   	gReplyHeader.fsize=sa.st_size;
			 	   	usbEp2.Write(&usbEp2,(char*)&gReplyHeader,sizeof(gReplyHeader),usbSentCallBack);
			 	   	
	    			//usbEp2.Write(&usbEp2,buf,sa.st_size,usbSentCallBack);
					//free(buf);buf=0;
					}
					//fclose(f);
				}
    		}else
    		{
				gReplyHeader.fsize=0;
		 	   	usbEp2.Write(&usbEp2,(char*)&gReplyHeader,sizeof(gReplyHeader),usbSentCallBack);    			
    		}
    	}
    }
  }  
    
}
















