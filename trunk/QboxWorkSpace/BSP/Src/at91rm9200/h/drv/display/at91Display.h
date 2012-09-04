/* at91display.h - display  controller header */

/* Copyright 1984-2001 Wind River Systems, Inc. */
/*
modification history
--------------------

*/

#ifndef __INCdisplayDrvh
#define __INCdisplayDrvh

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _ASMLANGUAGE






/* Video Graphic Controller */

#define S1D13806_DISP_MEM_BASE	( ( (int) S1D13806_BASE)  + ((int) 0x200000) )

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

STATUS	at91_s1d1xInit ();


#else

STATUS	at91_s1d1xInit();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdisplayDrvh */


