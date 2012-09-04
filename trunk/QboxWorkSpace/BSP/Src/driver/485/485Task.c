#include "copyright_wrs.h"


#include <errnoLib.h>
#include <taskLib.h>

#include <stdio.h>

#include <netLib.h>
#include <sys/socket.h>
#include <net/mbuf.h>
   
#include <memPartLib.h>

#include "UrgencyChannelDrv.h" 

 

#define BSP_VIRTUAL_STACK_DELETE
#ifndef BZERO
#define BZERO(buf, nbytes)		bzero((char *)(buf), (int)(nbytes))
#endif
 
IMPORT void mcastHashInit (void); 	/* initialize mcast hsh tbl */
void UrgencyTask (void);


typedef struct _TODO_NODE
    {
    struct _TODO_NODE * pNext;
    FUNCPTR routine;    /* routine to be called */
    void * param1;              /* arg to routine */
    void * param2;
    void * param3;
    void * param4;
    void * param5;
    void * reserved; /* an even 8 words */
    } TODO_NODE;

typedef struct _Urgency_JOB_INFO
    {
    TODO_NODE * pHead; /* Active node queue head */
    TODO_NODE * pTail; /* Active node queue tail */
    TODO_NODE * pFree; /* Free node queue head */
    SEMAPHORE sem;      /* UrgencyTask work-to-do sync semaphore */
    } Urgency_JOB_INFO;

typedef struct _GTF_Urgency_TICK_INFO
    {
    UINT unhandledTicks;
    BOOL eventPosted;
    } GTF_Urgency_TICK_INFO;

#define NUMBER_OF_JOBS    128       /* XXX probably needs to be configurable */
#define JOB_RING_SIZE     (NUMBER_OF_JOBS * sizeof (TODO_NODE))



/* local variables */
LOCAL Urgency_JOB_INFO UrgencyJobInfo;
LOCAL GTF_Urgency_TICK_INFO UrgencyGtfTickInfo;

LOCAL SEMAPHORE UrgencyTaskSem;		/* UrgencyTask work-to-do sync-semaphore */

#ifdef BSP_VIRTUAL_STACK_DELETE
LOCAL SEMAPHORE UrgencyTaskDelSem;		/* UrgencyTask sync with vs delete process */
#endif
LOCAL int UrgencyGtfTicks = 0;              /* ticks until next second */

/* global variables */

LOCAL SEM_ID UrgencyTaskSemId = &UrgencyTaskSem;
LOCAL ULONG  UrgencyGtfSeconds = 0; /* Second counter for use in Urgencyworking code,
                             use of this counter will avoid issues with
                             counter wrap */
LOCAL int    UrgencyGtfHz = 10;     /* Number of GTF ticks per second, set in
                             usrUrgencyGtf.c */

#ifdef BSP_VIRTUAL_STACK_DELETE
LOCAL SEM_ID UrgencyTaskDelSemId = &UrgencyTaskDelSem;
#endif

LOCAL int UrgencyTaskId;
LOCAL int UrgencyTaskPriority  = 20 ;
LOCAL int UrgencyTaskOptions   = VX_SUPERVISOR_MODE | VX_UNBREAKABLE;
LOCAL int UrgencyTaskStackSize = 10000;

LOCAL unsigned int 	UrgencyJobNum = NUMBER_OF_JOBS;
LOCAL void * UrgencyGtfTickInformation = &UrgencyGtfTickInfo;




/*******************************************************************************
*
* UrgencyLibInit - initialize the Urgencywork package
*
* This creates the Urgencywork task job queue, and spawns the Urgencywork task
* UrgencyTask(). It should be called once to initialize the Urgencywork. This is
* done automatically when INCLUDE_Urgency_DAEMON is defined.
*
* RETURNS: OK, or ERROR if Urgencywork support cannot be initialized.
*
* SEE ALSO: usrConfig, UrgencyTask()
*/

STATUS UrgencyLibInit (void)
    {
    static BOOL done = FALSE;

    if (done)
	return (UrgencyTaskId == ERROR ? ERROR : OK);

    if (semBInit (&UrgencyJobInfo.sem, SEM_Q_FIFO, SEM_EMPTY) == ERROR)
	return (ERROR);

#ifdef BSP_VIRTUAL_STACK_DELETE
    semBInit (UrgencyTaskDelSemId, SEM_Q_PRIORITY, SEM_FULL);

    if (UrgencyTaskDelSemId == NULL)
	return (ERROR);
#endif

    done = TRUE;

    if (UrgencyJobAlloc (UrgencyJobNum) != OK)
      {
      panic ("UrgencyLibInit: couldn't allocate job nodes\n");
      return ERROR;
      }

    UrgencyTaskId = taskSpawn ("tUrgencyTask", UrgencyTaskPriority,
		           UrgencyTaskOptions, UrgencyTaskStackSize,
			   (FUNCPTR)UrgencyTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    
    return (UrgencyTaskId == ERROR ? ERROR : OK);
    }

/***************************************************************************
*
* netJobAlloc - allocate a number of net job TODO_NODEs
*
* RETURNS: OK if allocation succeeds, ERROR otherwise.
* NOMANUAL
*/


STATUS UrgencyJobAlloc
    (
    u_int numJobs
    )
    {
    TODO_NODE * pToDo;
    TODO_NODE * pNode;
    int i;
    int key;

    if (numJobs == 0)
	return OK;

    pToDo = (TODO_NODE *)KHEAP_ALIGNED_ALLOC (numJobs * sizeof (*pToDo),
					      _CACHE_ALIGN_SIZE);
    if (pToDo == NULL)
	{
	return ERROR;
	}

    BZERO (pToDo, numJobs * sizeof (TODO_NODE));

    pNode = pToDo;

    for (i = 0; i < numJobs; i++)
	{
	pNode->pNext = pNode + 1;
	pNode = pNode + 1;
	}

    --pNode;  /* back up to last node */

    /* Add new nodes to free list */

    key = intLock();
    pNode->pNext = UrgencyJobInfo.pFree;
    UrgencyJobInfo.pFree = pToDo;
    intUnlock (key);

    return OK;
    }

/*******************************************************************************
*
* UrgencyTask - Urgencywork task entry point
*
* This routine is the VxWorks Urgencywork support task.  Most of the VxWorks
* Urgencywork runs in this task's context.
*
* NOTE
* To prevent an application task from monopolizing the CPU if it is
* in an infinite loop or is never blocked, the priority of UrgencyTask()
* relative to an application may need to be adjusted.  Urgencywork communication
* may be lost if UrgencyTask() is "starved" of CPU time.  The default task
* priority of UrgencyTask() is 50.  Use taskPrioritySet() to change the priority
* of a task.
*
* This task is spawned by UrgencyLibInit().
*
* RETURNS: N/A
*
* SEE ALSO: UrgencyLibInit()
*
* INTERNAL
* UrgencyTask() reads messages from a ring buffer which is filled by calling
* UrgencyJobAdd().
*/

void UrgencyTask (void)
    {
    FAST int	key;
    Urgency_JOB_INFO * pInfo = &UrgencyJobInfo;


    FOREVER
	{
	/* wait for somebody to wake us up */

        semTake (&pInfo->sem, WAIT_FOREVER);


        key = intLock ();

        while (TRUE)
            {
            TODO_NODE * pHead;
            TODO_NODE * pNode;

            /* Pull all the active nodes off of the queue */

            if ( (pHead = pInfo->pHead) == NULL)
                break;

            pInfo->pHead = NULL;
            pInfo->pTail = NULL;

            intUnlock (key);

            pNode = pHead;

            while (TRUE)
                {
                pNode->routine (pNode->param1, pNode->param2,
                                pNode->param3, pNode->param4,
                                pNode->param5);

                if (pNode->pNext == NULL)
                    break;

                pNode = pNode->pNext;
                }

            /* Place all processed nodes on the free queue */

            key = intLock ();
            pNode->pNext = pInfo->pFree;
            pInfo->pFree = pHead;
            }

	intUnlock (key);

	}
    }

/*******************************************************************************
*
* UrgencyJobAdd - add a routine to the Urgencywork task job queue
*
* This function allows a routine and up to 5 parameters,
* to be added to the Urgencywork job queue.
* Only Urgencywork interfaces should use this function, usually
* to have their interrupt level processing done at task level.
*
* RETURNS: OK or ERROR
*
* NOMANUAL
*/

STATUS UrgencyJobAdd
    (
    FUNCPTR routine,
    int param1,
    int param2,
    int param3,
    int param4,
    int param5
    )
    {
    FAST int oldlevel;
    TODO_NODE * pNode;
    Urgency_JOB_INFO * pInfo = &UrgencyJobInfo;

    oldlevel = intLock ();

    if ( (pNode = pInfo->pFree) != NULL)
	{
	pInfo->pFree = pNode->pNext;
	pNode->pNext = NULL;

	pNode->routine = routine;
	pNode->param1 = (void *)param1;
	pNode->param2 = (void *)param2;
	pNode->param3 = (void *)param3;
	pNode->param4 = (void *)param4;
	pNode->param5 = (void *)param5;

	if (pInfo->pTail != NULL)
	    pInfo->pTail->pNext = pNode;
	else
	    pInfo->pHead = pNode;
	pInfo->pTail = pNode;
	}

    intUnlock (oldlevel);

    if (pNode != NULL)
	{
	/* wake up the Urgencywork daemon to process the request */

	semGive (&pInfo->sem);

	return (OK);
	}

    panic ("UrgencyJobAdd: ring buffer overflow!\n");
    return (ERROR);
    }

