/* usrAppInit.c - stub application initialization routine */

/* Copyright 1984-1998 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,02jun98,ms   written
*/

/*
DESCRIPTION
Initialize user application code.
*/ 

/******************************************************************************
*
* usrAppInit - initialize the users application
*/ 


void BSP_SoftStart(void);
void usrAppInit (void)
    {
#ifdef	INCLUDE_USER_APPL
	USER_APPL_INIT;		/* for backwards compatibility */
#endif
//BSP_SoftStart();
//	sp(BSP_SoftStart);



    sp(BSP_SoftStart);
    /* add application specific code here */

    }


