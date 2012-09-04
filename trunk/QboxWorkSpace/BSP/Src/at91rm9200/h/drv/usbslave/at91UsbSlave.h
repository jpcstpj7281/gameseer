/* s3c2510Usb.h - AT91RM9200 USB header */




#ifndef __INCs3c2510Usbh
#define __INCs3c2510Usbh

typedef struct usb_tcd_at91_params
    {
    UINT32 ioBase;		    /* Base I/O address range */
    UINT16 irq; 		    /* IRQ channel (e.g., 5 = IRQ5) */
    UINT16 dma; 		    /* DMA channel (e.g., 3 = DMA3) */
    } USB_TCD_AT91_PARAMS, *pUSB_TCD_AT91_PARAMS;

#ifdef  __cplusplus
extern "C" {
#endif


/* Function Prototypes */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT STATUS   at91UsbSlaveInit(void);


#else  /* defined(__STDC__) || defined(__cplusplus) */

IMPORT STATUS   at91UsbSlaveInit();

#endif  /* defined(__STDC__) || defined(__cplusplus) */


#ifdef __cplusplus
}
#endif

#endif  /* __INCs3c2510Usbh */
