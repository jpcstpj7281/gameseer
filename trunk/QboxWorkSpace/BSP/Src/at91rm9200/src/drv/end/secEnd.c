/* secEnd.c - END style ATMEL AAT91RM9200 Ethernet network interface driver  */





#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"
#include "net/mbuf.h"
#include "net/unixLib.h"
#include "net/protosw.h"
#include "sys/socket.h"
#include "sys/ioctl.h"
#include "net/route.h"
#include "inetLib.h"

#include "cacheLib.h"
#include "logLib.h"
#include "netLib.h"
#include "stdio.h"
#include "stdlib.h"
#include "sysLib.h"
#include "taskLib.h"

#include "net/systm.h"
#include "sys/times.h"
#include "net/if_subr.h"

#undef  ETHER_MAP_IP_MULTICAST
#include "etherMultiLib.h"
#include "end.h"
#include "semLib.h"

#define END_MACROS
#include "endLib.h"
#include "miiLib.h"
#include "lstLib.h"

#include "config.h"
#include "drv/end/secEnd.h"
#include "bootLib.h "

/* Defines */

#undef  DEBUG_TRACE
/*#define DEBUG_LOG(x, p1, p2, p3, p4, p5, p6) \
        logMsg(x, (int)(UINT32)(p1), (int)(UINT32)(p2), (int)(UINT32)(p3), (int)(UINT32)(p4), (int)(UINT32)(p5), (int)(UINT32)(p6))
*/

/* Forward Function Declarations */
 
LOCAL STATUS    secEndInitParse(DRV_CTRL *pDrvCtrl, char *initString);
LOCAL STATUS    secEndInitMem(DRV_CTRL *pDrvCtrl);

LOCAL STATUS    secEndUnload(DRV_CTRL *pDrvCtrl);
LOCAL STATUS    secEndStart(DRV_CTRL *pDrvCtrl);
LOCAL STATUS    secEndStop(DRV_CTRL *pDrvCtrl);

LOCAL int       secEndIoctl(DRV_CTRL *pDrvCtrl, int cmd, caddr_t data);
LOCAL STATUS    secEndSend(DRV_CTRL *pDrvCtrl, M_BLK_ID pMblk);
LOCAL STATUS    secEndMCastAddrAdd(DRV_CTRL *pDrvCtrl, UCHAR *pAddr);
LOCAL STATUS    secEndMCastAddrDel(DRV_CTRL *pDrvCtrl, UCHAR *pAddr);
LOCAL STATUS    secEndMCastAddrGet(DRV_CTRL *pDrvCtrl, MULTI_TABLE *pTable);
LOCAL STATUS    secEndPollSend(DRV_CTRL *pDrvCtrl, M_BLK_ID pMblk);
LOCAL STATUS    secEndPollReceive(DRV_CTRL *pDrvCtrl, M_BLK_ID pMblk);


/* Declare our function table. This is static across all driver instances. */

LOCAL NET_FUNCS endFuncTable = {
    (FUNCPTR)secEndStart,                                   /* start func. */
    (FUNCPTR)secEndStop,                                    /* stop func. */
    (FUNCPTR)secEndUnload,                                  /* unload func. */
    (FUNCPTR)secEndIoctl,                                   /* ioctl func. */
    (FUNCPTR)secEndSend,                                    /* send func. */
    (FUNCPTR)secEndMCastAddrAdd,                            /* multicast add func. */
    (FUNCPTR)secEndMCastAddrDel,                            /* multicast delete func. */
    (FUNCPTR)secEndMCastAddrGet,                            /* multicast get fun. */
    (FUNCPTR)secEndPollSend,                                /* polling send func. */
    (FUNCPTR)secEndPollReceive,                             /* polling receive func. */
    endEtherAddressForm,                                    /* put address info into a NET_BUFFER */
    (FUNCPTR)endEtherPacketDataGet,                         /* get pointer to data in NET_BUFFER */
    (FUNCPTR)endEtherPacketAddrGet                          /* Get packet addresses */
};


/*******************************************************************************
*
* secEndLoad - initialize the driver and device
*
* This routine initializes the driver and the device to the operational state.
* All of the device specific parameters are passed in the initString.
*
* The string contains the target specific parameters like this:
*
* "unit number:"
*
* RETURNS: An END object pointer or NULL on error.
*/

END_OBJ* secEndLoad(
    char *initString                                        /* parameter string */
    )
{
    DRV_CTRL *pDrvCtrl;                                     /* pointer to DRV_CTRL structure */
    UCHAR enetAddr[SEC_END_ADDR_LEN];                       /* ethernet address */

#ifdef  DEBUG_TRACE
    printf("secEnd Load, %s\n", initString);
#endif  /* DEBUG_TRACE */

    if (initString == NULL)
    {
        printf("secEnd Error: NULL parameter string\n");

        return NULL;
    }

    if (initString[0] == 0)
    {
        bcopy((char *)SEC_END_DEV_NAME, (char *)initString, SEC_END_DEV_NAME_LEN);

#ifdef  DEBUG_TRACE
        printf("secEnd Load, %s\n", initString);
#endif  /* DEBUG_TRACE */
        return NULL;
    }

    /* Allocate the device structure. */
    pDrvCtrl = (DRV_CTRL *)calloc(sizeof(DRV_CTRL), 1);
    if (pDrvCtrl == NULL)
    {
        printf("secEnd Error: Failed to allocate DRV_CTRL\n");

        return (NULL);
    }

    while (1)
    {
        /* Parse InitString. */
        if (secEndInitParse(pDrvCtrl, initString) != OK)
        {
            break;
        }

        /* Memory initialization. */
        if (secEndInitMem(pDrvCtrl) != OK)
        {
            break;
        }

        /* Initialize physical device. */
        if (DRV_INIT(pDrvCtrl) != OK)
        {
            break;
        }

        /* Initialize END object. */
        if (END_OBJ_INIT(
                &pDrvCtrl->endObj,
                (DEV_OBJ *)pDrvCtrl,
                SEC_END_DEV_NAME,
                pDrvCtrl->unit,
                &endFuncTable,
                SEC_END_DEV_DESCRIPTION
                ) == ERROR)
        {
            printf("secEnd%d Error: Failed to initialize END_OBJ\n", pDrvCtrl->unit);

            break;
        }

        /* Get ethernet hardware address. */
        sysSecEnetAddrGet(pDrvCtrl->unit, enetAddr);

        /* Initialize MIB. */
        if (END_MIB_INIT(
                &pDrvCtrl->endObj,
                M2_ifType_ethernet_csmacd, 
                enetAddr,
                SEC_END_ADDR_LEN,
                ETHERMTU,
                pDrvCtrl->phyInfo.phySpeed
                ) == ERROR)
        {
            printf("secEnd%d Error: Failed to initialize END_MIB\n", pDrvCtrl->unit);

            break;
        }

        /* Mark the device ready. */
        END_OBJ_READY(&pDrvCtrl->endObj, IFF_NOTRAILERS | IFF_MULTICAST | IFF_BROADCAST);

        return (&pDrvCtrl->endObj);
    }

    secEndUnload(pDrvCtrl);

    return NULL;
}

/******************************************************************************
*
* secEndUnload - unload a driver from the system
*
* This function first brings down the device, and then frees any stuff that was
* allocated by the driver in the load function.
*
* RETURNS: OK or ERROR.
*/

STATUS secEndUnload(
    DRV_CTRL *pDrvCtrl                                      /* pointer to DRV_CTRL structure */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d Unload\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    if (pDrvCtrl == NULL)
    {
        return ERROR;
    }

    /* Uninitialize END object. */
    END_OBJ_UNLOAD(&pDrvCtrl->endObj);

    /* Free buffer descriptor pool if necessary. */
  /*  if (pDrvCtrl->pBdArea != NULL)
    {
        cacheDmaFree(pDrvCtrl->pBdArea);
    }
*/
    /* Free cluster pool if necessary. */
    if (pDrvCtrl->pClArea != NULL)
    {
        cacheDmaFree(pDrvCtrl->pClArea);
        pDrvCtrl->pClArea = 0 ;
    }

    /* Free mBlk/clBlk pool if necessary. */
    if (pDrvCtrl->pMblkArea != NULL)
    {
        free(pDrvCtrl->pMblkArea);
        pDrvCtrl->pMblkArea = 0 ;
    }

    /* Free netPool if necessary. */
    if (pDrvCtrl->endObj.pNetPool != NULL)
    {
        free(pDrvCtrl->endObj.pNetPool);
    }

    /* Free the device structure. */
    cfree((char *)pDrvCtrl);

    return OK;
}

/*******************************************************************************
*
* secEndStart - start the device
*
* This function calls BSP functions to connect interrupts and start the device
* running in interrupt mode.
*
* RETURNS: OK or ERROR
*
*/

LOCAL STATUS secEndStart(
    DRV_CTRL *pDrvCtrl                                      /* pointer to DRV_CTRL structure */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d Start\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Mark the interface as up. */
    END_FLAGS_SET(&pDrvCtrl->endObj, (IFF_UP | IFF_RUNNING));

    return DRV_START(pDrvCtrl);
}

/*******************************************************************************
*
* secEndStop - stop the device
*
* This function calls BSP functions to disconnect interrupts and stop the device
* from operating in interrupt mode.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS secEndStop(
    DRV_CTRL *pDrvCtrl                                      /* pointer to DRV_CTRL structure */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d Stop\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Mark the interface as down. */
    END_FLAGS_CLR(&pDrvCtrl->endObj, (IFF_UP | IFF_RUNNING));

    return DRV_STOP(pDrvCtrl);
}

/*******************************************************************************
*
* secEndIoctl - the driver I/O control routine
*
* Process an ioctl request.
*
* RETURNS: A command specific response, usually OK or ERROR.
*/

LOCAL int secEndIoctl(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    int cmd,                                                /* command to process */
    caddr_t data                                            /* pointer to data */
    )
{
    int error = OK;
    END_OBJ *pEndObj = &pDrvCtrl->endObj;
    long value;

#ifdef  DEBUG_TRACE
    printf("secEnd%d Ioctl: ", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    switch (cmd)
    {
    case EIOCSADDR:
#ifdef  DEBUG_TRACE
        printf("EIOCSADDR\n");
#endif  /* DEBUG_TRACE */

        /* Stop the device. */
        DRV_STOP(pDrvCtrl);

        /* Save the enet address. */
        bcopy ((char *)data, END_HADDR(pEndObj), SEC_END_ADDR_LEN);

        /* Program the individual enet address. */
        error = DRV_ADDR_SET(pDrvCtrl);

        /* Restart the device. */
        DRV_START(pDrvCtrl);
        break;

    case EIOCGADDR:
#ifdef  DEBUG_TRACE
        printf("EIOCGADDR\n");
#endif  /* DEBUG_TRACE */

        /* Retrieve the enet address. */
        bcopy (END_HADDR(pEndObj), (char *)data, SEC_END_ADDR_LEN);
        break;

    case EIOCSFLAGS:
#ifdef  DEBUG_TRACE
        printf("EIOCSFLAGS\n");
#endif  /* DEBUG_TRACE */

        value = (long)data;
        if (value < 0)
        {
            value = -value;
            value--;
            END_FLAGS_CLR(pEndObj, value);
        }
        else
        {
            END_FLAGS_SET(pEndObj, value);
        }

        /* Set device flags. */
        error = DRV_FLAGS_SET(pDrvCtrl);
        break;

    case EIOCGFLAGS:
#ifdef  DEBUG_TRACE
        printf("EIOCGFLAGS\n");
#endif  /* DEBUG_TRACE */

        /* Get device flags. */
        *(long *)data = END_FLAGS_GET(pEndObj);
        break;

    case EIOCMULTIADD:
#ifdef  DEBUG_TRACE
        printf("EIOCMULTIADD\n");
#endif  /* DEBUG_TRACE */

        /* Add multicast address. */
        error = secEndMCastAddrAdd(pDrvCtrl, (UCHAR *)data);
        break;

    case EIOCMULTIDEL:
#ifdef  DEBUG_TRACE
        printf("EIOCMULTIDEL\n");
#endif  /* DEBUG_TRACE */

        /* Delete multicast address. */
        error = secEndMCastAddrDel(pDrvCtrl, (UCHAR *)data);
        break;

    case EIOCMULTIGET:
#ifdef  DEBUG_TRACE
        printf("EIOCMULTIGET\n");
#endif  /* DEBUG_TRACE */

        /* Retrieve a table of multicast addresses. */
        error = secEndMCastAddrGet(pDrvCtrl, (MULTI_TABLE *)data);
        break;

    case EIOCPOLLSTART:
#ifdef  DEBUG_TRACE
        printf("EIOCPOLLSTART\n");
#endif  /* DEBUG_TRACE */

        /* Start polling mode. */
        error = DRV_POLL_START(pDrvCtrl);
        break;

    case EIOCPOLLSTOP:
#ifdef  DEBUG_TRACE
        printf("EIOCPOLLSTOP\n");
#endif  /* DEBUG_TRACE */

        /* Stop polling mode. */
        error = DRV_POLL_STOP(pDrvCtrl);
        break;

    case EIOCGMIB2:  
#ifdef  DEBUG_TRACE
        printf("EIOCGMIB2\n");
#endif  /* DEBUG_TRACE */

        /* Get MIB2 table. */
        bcopy ((char *)&pEndObj->mib2Tbl, (char *)data, sizeof(pEndObj->mib2Tbl));
        break;

    case EIOCGNPT:
#ifdef  DEBUG_TRACE
        printf("EIOCGNPT\n");
#endif  /* DEBUG_TRACE */

        error = EINVAL;
        break;

    case EIOCGHDRLEN:
#ifdef  DEBUG_TRACE
        printf("EIOCGHDRLEN\n");
#endif  /* DEBUG_TRACE */

        *(long *)data = ENET_HDR_REAL_SIZ;
        break;

    default:
#ifdef  DEBUG_TRACE
        printf("\n");
#endif  /* DEBUG_TRACE */
        printf("secEnd%d Error: Unknown IOCTL command(0x%08X)\n", pDrvCtrl->unit, cmd);

        error = EINVAL;
        break;
    }

    return (error);
}

/*******************************************************************************
*
* secEndSend - the driver send routine
*
* This routine takes a M_BLK_ID sends off the data in the M_BLK_ID. The buffer
* must already have the addressing information properly installed in it. This is
* done by a higher layer. The last arguments are a free routine to be called
* when the device is done with the buffer and a pointer to the argument to pass
* to the free routine.
*
* RETURNS: OK, ERROR, or END_ERR_BLOCK.
*/

LOCAL STATUS secEndSend(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{
    STATUS status;

#ifdef  DEBUG_TRACE
    printf("secEnd%d Send\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    END_TX_SEM_TAKE(&pDrvCtrl->endObj, WAIT_FOREVER);

    /* Send data. */
    status = DRV_SEND(pDrvCtrl, pMblk);

    END_TX_SEM_GIVE(&pDrvCtrl->endObj);

    return (status);
}

/*****************************************************************************
*
* secEndMCastAddrAdd - add a multicast address for the device
*
* This routine adds a multicast address to whatever the driver is already
* listening for. It then resets the address filter.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS secEndMCastAddrAdd(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    UCHAR *pAddr                                            /* address to be added */
    )
{
    int retVal;

#ifdef  DEBUG_TRACE
    printf("secEnd%d MCastAddrAdd\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Add multicast address to a multicast address list. */
    retVal = etherMultiAdd(&pDrvCtrl->endObj.multiList, pAddr);

    if (retVal == ENETRESET)
    {
        /* Program multicast address. */
        retVal = DRV_MCAST_ADD(pDrvCtrl, pAddr);
    }

    return (retVal);
}

/*****************************************************************************
*
* secEndMCastAddrDel - delete a multicast address for the device
*
* This routine removes a multicast address from whatever the driver is
* listening for. It then resets the address filter.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS secEndMCastAddrDel(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    UCHAR *pAddr                                            /* address to be deleted */
    )
{
    int retVal;

#ifdef  DEBUG_TRACE
    printf("secEnd%d MCastAddrDel\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Delete multicast address from a multicast address list. */
    retVal = etherMultiDel(&pDrvCtrl->endObj.multiList, pAddr);

    while (retVal == ENETRESET)
    {
        /* Stop the device. */
        DRV_STOP(pDrvCtrl);

        /* Program multicast address. */
        retVal = DRV_MCAST_DEL(pDrvCtrl, pAddr);

        /* Restart the device. */
        DRV_START(pDrvCtrl);
    }

    return (retVal);
}

/*****************************************************************************
*
* secEndMCastAddrGet - get the multicast address list for the device
*
* This routine gets the multicast list of whatever the driver is already
* listening for.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS secEndMCastAddrGet(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    MULTI_TABLE *pTable                                     /* table into which to copy addresses */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d MCastAddrGet\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Retrieve a table of multicast addresses from a driver. */
    return (etherMultiGet(&pDrvCtrl->endObj.multiList, pTable));
}

/*******************************************************************************
*
* secEndPollSend - routine to send a packet in polled mode
*
* This routine is called by a user to try and send a packet on the device.
*
* RETURNS: OK upon success.  EAGAIN if device is busy.
*/

LOCAL STATUS secEndPollSend(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d PollSend\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    while (1)
    {
        if (pMblk == NULL)
        {
            printf("secEnd%d Error: NULL tansmit M_BLK\n", pDrvCtrl->unit);

            break;
        }

        /* Send data. */
        return DRV_POLL_SEND(pDrvCtrl, pMblk);
    }

    END_ERR_ADD(&pDrvCtrl->endObj, MIB2_OUT_ERRS, +1);

    return EAGAIN;
}

/*******************************************************************************
*
* secEndPollReceive - routine to receive a packet in polled mode
*
* This routine is called by a user to try and get a packet from the device.
*
* RETURNS: OK upon success.  EAGAIN is returned when no packet is available.
*/

LOCAL STATUS secEndPollReceive(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{
#ifdef  DEBUG_TRACE
    printf("secEnd%d PollReceive\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    while (1)
    {
        if (pMblk == NULL)
        {
            printf("secEnd%d Error: NULL receive M_BLK\n", pDrvCtrl->unit);

            break;
        }

        /* If not has an associated cluster, avoid operation. */
        if (!(pMblk->mBlkHdr.mFlags & M_EXT))
        {
            printf("secEnd%d Error: Invalid receive M_BLK\n", pDrvCtrl->unit);

            break;
        }

        /* Receive data if available. */
        return DRV_POLL_RECEIVE(pDrvCtrl, pMblk);
    }

    END_ERR_ADD(&pDrvCtrl->endObj, MIB2_IN_ERRS, +1);

    return EAGAIN;
}

/*******************************************************************************
*
* secEndInitParse - parse the init string
*
* Parse the input string. Fill in values in the driver control structure.
*
* The muxLib.o module automatically prepends the unit number to the user's
* initialization string from the BSP (configNet.h).
*
* RETURNS: OK or ERROR for invalid arguments.
*/

LOCAL STATUS secEndInitParse(
    DRV_CTRL *pDrvCtrl,                                     /* pointer to DRV_CTRL structure */
    char *initString                                        /* parameter string */
    )
{
    char *tok;
    char *holder = NULL;

#ifdef  DEBUG_TRACE
    printf("secEnd InitParse, %s\n", initString);
#endif  /* DEBUG_TRACE */

    tok = strtok_r(initString, ":", &holder);
    if (tok == NULL)
    {
        return ERROR;
    }

    pDrvCtrl->unit = 0 ; /* (int)strtoul(tok, NULL, 16);*/

    /* Sanity check the unit number. */
    if (pDrvCtrl->unit < 0)
    {
        printf("secEnd Error: Invalid unit number, %d\n", pDrvCtrl->unit);

        return ERROR;
    }

    return OK;
}

/*******************************************************************************
*
* secEndInitMem - initialize memory for the chip
*
* This routine is highly specific to the device.
*
* RETURNS: OK or ERROR.
*/
    
LOCAL STATUS secEndInitMem(
    DRV_CTRL *pDrvCtrl                                      /* pointer to DRV_CTRL structure */
    )
{
    M_CL_CONFIG mClBlkConfig;                               /* mBlk, clBlk pool configuration table. */
    CL_DESC clDescTbl[SEC_END_NUM_CL_TYPE];                 /* cluster pool configuration table. */

#ifdef  DEBUG_TRACE
    printf("secEnd%d InitMem\n", pDrvCtrl->unit);
#endif  /* DEBUG_TRACE */

    /* Allocate the netPool. */
    if ((pDrvCtrl->endObj.pNetPool = malloc(sizeof(NET_POOL))) == NULL)
    {
        return (ERROR);
    }

    /* Initialize mBlk/clBlk pool. */
    mClBlkConfig.mBlkNum    = DRV_NUM_MBLK;
    mClBlkConfig.clBlkNum   = DRV_NUM_CLUSTER ;/*DRV_NUM_MBLK;*/

    mClBlkConfig.memSize    = mClBlkConfig.mBlkNum * (M_BLK_SZ + sizeof(long)) +
                              mClBlkConfig.clBlkNum * (CL_BLK_SZ+ sizeof(long));
    mClBlkConfig.memArea    = (char *)memalign(MBLK_ALIGNMENT, mClBlkConfig.memSize);

    if (mClBlkConfig.memArea == NULL)
    {
        printf("secEnd%d Error: Failed to allocate mBlk/clBlk pool\n", pDrvCtrl->unit);

        return (ERROR);
    }

    /* Save the pointer to the mBlock/cBlk pool area. */
    pDrvCtrl->pMblkArea = (void *)mClBlkConfig.memArea;

    /* Initialize cluster pool. */
    clDescTbl[0].clSize     =  SIZE_ETH_MDMA ;  /*SIZE_FB - CL_OVERHEAD;*/
    clDescTbl[0].clNum      =   DRV_NUM_CLUSTER;
    clDescTbl[0].memSize    =   (clDescTbl[0].clNum *
                               (clDescTbl[0].clSize + 8))
      						  + sizeof(int);        /* +8 is for proper alignment */	/* SIZE_FB * DRV_NUM_CLUSTER;*/
/*    clDescTbl[0].memArea    = (char *)(DRV_CLUSTER_MEM_BASE );*/
    clDescTbl[0].memArea =    (char *) cacheDmaMalloc (clDescTbl[0].memSize);

    if (clDescTbl[0].memArea == NULL)
    {
		;
    	return (ERROR);
    }
   pDrvCtrl->pClArea = clDescTbl[0].memArea ;
#ifdef  DEBUG_TRACE
    printf("    mBlk/clBlk pool     : 0x%08X\n", (UINT32)mClBlkConfig.memArea);
    printf("    cluster pool        : 0x%08X\n", (UINT32)clDescTbl[0].memArea);
#endif  /* DEBUG_TRACE */

    /* Initialize the netPool. */
    if (netPoolInit(pDrvCtrl->endObj.pNetPool, &mClBlkConfig, &clDescTbl[0], SEC_END_NUM_CL_TYPE, NULL) == ERROR)
    {
        printf("secEnd%d Error: Failed to initialize netPool\n", pDrvCtrl->unit);

        return (ERROR);
    }

    /* Save cluster pool. */
 /*   if ((pDrvCtrl->pClPool = netClPoolIdGet(pDrvCtrl->endObj.pNetPool, DRV_SIZE_CLUSTER, FALSE)) == NULL)
    {
        printf("secEnd%d Error: Failed to get clPool\n", pDrvCtrl->unit);

        return (ERROR);
    }
*/
#ifdef  DEBUG_TRACE
    printf("    pNetPool->mBlkCnt   : %d\n", pDrvCtrl->endObj.pNetPool->mBlkCnt);
    printf("    pNetPool->mBlkFree  : %d\n", pDrvCtrl->endObj.pNetPool->mBlkFree);
    printf("    pNetPool->clLg2Max  : %d\n", pDrvCtrl->endObj.pNetPool->clLg2Max);
    printf("    pNetPool->clSizeMax : %d\n", pDrvCtrl->endObj.pNetPool->clSizeMax);
    printf("    pNetPool->clLg2Min  : %d\n", pDrvCtrl->endObj.pNetPool->clLg2Min);
    printf("    pNetPool->clSizeMin : %d\n", pDrvCtrl->endObj.pNetPool->clSizeMin);
/*  printf("    pClPool->clSize     : %d\n", pDrvCtrl->pClPool->clSize);
    printf("    pClPool->clLg2      : %d\n", pDrvCtrl->pClPool->clLg2);
    printf("    pClPool->clNum      : %d\n", pDrvCtrl->pClPool->clNum);
    printf("    pClPool->clNumFree  : %d\n", pDrvCtrl->pClPool->clNumFree);*/
#endif  /* DEBUG_TRACE */

    /* Change cluster size to real size. */
/*    pDrvCtrl->pClPool->clSize = DRV_SIZE_CLUSTER;*/

    return OK;
}


LOCAL unsigned char sysSecEnetAddr[][6] = {
#if 1
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x01},
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x02},
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x03},
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x04},
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x05},
    {0x00, 0x0D, 0x29, 0xed, 0x7f, 0x06}
#else
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x01},
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x02},
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x03},
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x04},
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x05},
    {0x08, 0x00, 0x02, 0x02, 0x02, 0x06}
#endif
};

STATUS sysSecEnetAddrGet(
    int unit,                                               /* unit number of device being used */
    UCHAR* addr                                             /* where to copy the ethernet address */
    )
{
	sysSecEnetAddrSet(unit);

	bcopy((char*)sysSecEnetAddr[unit], (char*)addr, 6);
    return (OK);
}



STATUS sysSecEnetAddrSet(
	int unit                                               /* unit number of device being used */
	)
{
	BOOT_PARAMS pBootParams ;
	unsigned int ipAdd;
	unsigned int SoltNo;
	unsigned char bordType;
	struct in_addr iaddr;
	unsigned int tempReg;

	SoltNo = BSP_BoardSolt();	
	if( ERROR !=SoltNo )
	{
		sysSecEnetAddr[unit][5]=(UCHAR)SoltNo;

	}


	bootStringToStruct(BOOT_LINE_ADRS,&pBootParams);

	
	ipAdd=inet_addr(pBootParams.ead);
	ipAdd=0x4343a8c0;
	ipAdd=((ipAdd&0x00FFFFFF)|SoltNo<<24);
	

	iaddr.s_addr = ipAdd;

	inet_ntoa_b (iaddr, pBootParams.ead);

	bordType=BSP_GetBoardTypeId();
	switch (bordType)
	{
		case 0:
			strcpy (pBootParams.bootFile, "vxWorks_SC");
			/* 交叉片，片选配置*/			
			*((volatile unsigned int *)(0xffffff70+4*6)) = 0x00003284;
			
			tempReg = *((volatile unsigned int *)(0xffffff60));
			tempReg |= 1 << 3;
			*((volatile unsigned int *)(0xffffff60))=tempReg;

			*((volatile unsigned int *)(0xffffff70+4*3)) = 0x10004185;

			break;
		case 1:
			strcpy (pBootParams.bootFile, "vxWorks_HD");
			break;
		case 2:
			strcpy (pBootParams.bootFile, "vxWorks_SD");
			break;
		case 3:
			strcpy (pBootParams.bootFile, "vxWorks_OP");
		
			*((volatile unsigned int *)(0xffffff70+4*4)) = 0x11003284;
			*((volatile unsigned int *)(0xffffff70+4*6)) = 0x11004286;
			/* 改写 EBI 使片选 3 工作在NAND FLASH 模式*/
			tempReg = *((volatile unsigned int *)(0xffffff60));
			tempReg |= 1 << 3;
			*((volatile unsigned int *)(0xffffff60))=tempReg;
			/* 改写片选3 工作时序*/
			*((volatile unsigned int *)(0xffffff70+4*3)) = 0x10004185;
			break;
		default:
			
			break;
			


	}

	*((volatile unsigned int *)(0xffffff70+4*2)) = 0x11003285;
	*((volatile unsigned int *)(0xffffff70+4*5)) = 0x00003284;
	bootStructToString(BOOT_LINE_ADRS,&pBootParams);

    return (OK);
}



