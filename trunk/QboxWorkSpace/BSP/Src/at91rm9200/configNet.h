/* configNet.h - network configuration header */




#ifndef INCconfigNeth
#define INCconfigNeth

#include "vxWorks.h"
#include "end.h"
#include "miiLib.h"
#include "arpLib.h"

/*#include "at91Eth.h"*/



#ifdef  INCLUDE_SEC_END
#define SEC_END_LOAD_FUNC               secEndLoad
#define SEC_END_LOAD_STRING             "at91End:0"

IMPORT  END_OBJ* SEC_END_LOAD_FUNC(char*, void*);

/*
#define SEC_SAR_END_LOAD_FUNC          secSarEndLoad
#define SEC_SAR_END_LOAD_STRING        ""

IMPORT  END_OBJ* SEC_SAR_END_LOAD_FUNC(char*, void*);
*/
#endif /* INCLUDE_SEC_END */

/* Max number of SENS ipAttachments we can have */

#ifndef IP_MAX_UNITS
#define IP_MAX_UNITS                    (NELEMENTS(endDevTbl) - 1)
#endif  /* IP_MAX_UNITS */

END_TBL_ENTRY endDevTbl [] = {
#ifdef  INCLUDE_SEC_END
    { 0, SEC_END_LOAD_FUNC, SEC_END_LOAD_STRING, TRUE, NULL, FALSE},
#if     (ETH_MAX_UNITS == 2)
    { 1, SEC_END_LOAD_FUNC, SEC_END_LOAD_STRING, TRUE, NULL, FALSE},
#endif  /* (ETH_MAX_UNITS == 2) */

/*
    { 0, SEC_SAR_END_LOAD_FUNC, SEC_SAR_END_LOAD_STRING, TRUE, NULL, FALSE},
*/

#endif  /* INCLUDE_SEC_END */
    { 0, END_TBL_END, NULL, 0, NULL, FALSE} 
};


#endif  /* INCconfigNeth */


