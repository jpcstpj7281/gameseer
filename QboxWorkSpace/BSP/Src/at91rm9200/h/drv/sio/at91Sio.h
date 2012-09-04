/* at91Sio.h - at91rm9200 SIO header file */




#ifndef __INCat91Sioh
#define __INCat91Sioh

#include "sioLib.h"

#ifdef  __cplusplus
extern  "C" {
#endif


/* Device Initialization Structure */

typedef struct {
    int             intLvl;                               /* Rx interrupt level */
    VOIDFUNCPTR     *intVec;                               /* Rx interrupt vector */
/*    int             ch;    */                                 /* channel number, 0:CUART, 1:HUART0, 2:HUART2 */
    void*		    base;
} AT91_SIO_CHAN_PARAM;

/* Device and Channel Structures */

typedef struct {
    /* Must be first */
    SIO_DRV_FUNCS  *pDrvFuncs;                              /* driver functions */

    /* Callbacks */
    STATUS          (*getTxChar)();                         /* pointer to transmit function */
    STATUS          (*putRcvChar)();                        /* pointer to receive function */
    void           *getTxArg;                               /* argument of transmit function */
    void           *putRcvArg;                              /* argument of receive function */

    /* Interrupt */
    int             intLvl;                               /* Rx interrupt vevel */
    VOIDFUNCPTR    *intVec;                               /* Rx interrupt vector */
	void*			base;
    /* Channel Information */
/*    int             ch;    */                                 /* channel number, 0:CUART, 1:HUART0, 2:HUART2 */
    int             baudRate;                               /* baud rate */
    int             sioMode;                                /* SIO mode  */
    int             options;                                /* SIO options */
    unsigned long 	read_status_mask;
} AT91_SIO_CHAN;


/* Function Prototypes */

#if defined(__STDC__) || defined(__cplusplus)

extern void at91SioDevInit(AT91_SIO_CHAN *pChan);
extern void at91SioDevInit2(AT91_SIO_CHAN *pChan);
extern void at91SioInt(AT91_SIO_CHAN *pChan );
#else  /* defined(__STDC__) || defined(__cplusplus) */

extern void at91SioDevInit();
extern void at91SioDevInit2();

extern void at91SioInt();
#endif  /* defined(__STDC__) || defined(__cplusplus) */


#ifdef  __cplusplus
}
#endif

#endif  /* __INCat91Sioh */



