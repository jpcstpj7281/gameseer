
#ifndef __INDRVDEBUG
#define __INDRVDEBUG


#ifdef __cplusplus
extern "C" {
#endif

/*µ÷ÊÔ²¿·Ö*/
#define DRV_SSC
#ifdef DRV_SSC
#define DRV_DEBUG_OFF		(0x0)
#define DRV_DEBUG_RX		(0x1)
#define DRV_DEBUG_TX		(0x1 << 1)
#define DRV_DEBUG_POLL_RX (0x1 << 2)
#define DRV_DEBUG_POLL_TX (0x1 << 3)
#define DRV_DEBUG_LOAD		(0x1 << 4)
#define DRV_DEBUG_IOCTL	(0x1 << 5)
#define DRV_DEBUG_INT		(0x1 << 6)
#define DRV_DEBUG_START   	(0x1 << 7)
#define DRV_DEBUG_DUMP    	(0x1 << 8)
#define DRV_DEBUG_PHY		(0x1 << 9)
#define DRV_DEBUG_INIT		(0x1 << 10)
#define DRV_DEBUG_TEST		(0x1 << 11)

#define DRV_DEBUG_ALL    	(0xffffffff)

LOCAL UINT32 mdl__DriverDebug = DRV_DEBUG_ALL;
LOCAL int (*func_logMsg)(char *,int,int,int,int,int,int)=logMsg;
	
#define DRV_LOG(FLG, X0, X1, X2, X3, X4, X5, X6)  				\
    do {														\
    if (mdl__DriverDebug & FLG)								\
	if (func_logMsg != NULL)									\
	    func_logMsg (X0, (int)X1, (int)X2, (int)X3, (int)X4,	\
			    (int)X5, (int)X6);								\
    } while (FALSE)

#else /* DRV_SSC */

#define DRV_LOG(FLG, X0, X1, X2, X3, X4, X5, X6)


#endif /* DRV_SSC */

#ifdef __cplusplus
}
#endif

#endif /*__INSCCDRIVER*/

