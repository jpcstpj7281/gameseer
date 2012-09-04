/* at91Eth.c - AT91RM9200 Ethernet controller driver  */




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


#include "config.h"
#include "drv/intrCtl/at91Intr.h"
#include "at91_ether.h"


#define DRV_DEBUG_RX        0x0001
#define DRV_DEBUG_TX        0x0002

#define END_CACHE_PHYS_TO_VIRT(x) x

#undef  DEBUG_TRACE


#define RX_WAIT_MAX                     (CPLL_FREQ * 1000)  /* Rx completion timeout */
#define TX_WAIT_MAX                     (CPLL_FREQ * 1000)  /* Tx completion timeout */
#define MII_WAIT_MAX                    (CPLL_FREQ * 1000)  /* max delay for the MII operation */

#ifndef NSDELAY
#define NSDELAY(nsec)                                           \
{                                                               \
    volatile int nx;                                            \
    volatile int loop = (int)(((CPLL_FREQ * nsec) / 1000) + 1); \
                                                                \
    for (nx=0; nx<loop; nx++);                                  \
}
#endif  /* NSDELAY */


/* External */

IMPORT STATUS   sysSecEnetAddrGet(int unit, UCHAR* address);


/* Forward Function Declarations */


/*LOCAL STATUS    at91EthAnRestart(ETH_DRV_CTRL *dev);*/
LOCAL void      at91EthRxHandler(ETH_DRV_CTRL *dev);
LOCAL void      at91EthTxHandler(ETH_DRV_CTRL *dev);

#ifdef  DEBUG_TRACE
LOCAL void      at91EthHexDump(UCHAR *p, ULONG l);
#endif  /* DEBUG_TRACE */


#include "at91_ether.c"
#if 0
LOCAL void at91EthMiiRead(ETH_DRV_CTRL* dev, unsigned char phy_addr, unsigned char address, unsigned short *value)
{
	unsigned int l;
	read_phy(dev->base_addr, phy_addr,address, &l);
	*value = (unsigned short) l;
}
LOCAL void at91EthMiiWrite(ETH_DRV_CTRL* dev, unsigned char phy_addr, unsigned char address, unsigned short value)
{
	unsigned int l=value;
	write_phy(dev->base_addr, phy_addr,address, l);
	
}
#endif
/*******************************************************************************
*
* at91EthInit - initialize S3C2510 Ethernet controller
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthInit(
    ETH_DRV_CTRL *dev 
    )
{

    at91ether_probe(dev);
    /* Initialize flags. */
    dev->bPolling   = FALSE;
    dev->bTxBlocked = FALSE;
    dev->bRxHandler = FALSE;
    dev->bTxHandler = FALSE;

    return OK;
}


#if 0
/*******************************************************************************
*
* at91EthAnRestart - restart auto negotiation
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthAnRestart(
    ETH_DRV_CTRL *dev                       
    )
{
    UINT16 phyAddr = dev->phyInfo.phyAddr;
    int timeout = MII_WAIT_MAX;
 
    /* Perserve selector. */
    dev->PHYREGS.phyAds &= MII_ADS_SEL_MASK;

    /* Set appropriate options. */
    dev->PHYREGS.phyAds |=
#ifdef  ETH_10BT
                                MII_TECH_10BASE_T |         /* 10T half-duplex capable */
#endif  /* ETH_10BT */
#ifdef  ETH_FULL_DUPLEX
                                MII_TECH_100BASE_TX_FD |    /* 100TX-FX full-duplex capable */
#ifdef  ETH_10BT
                                MII_TECH_10BASE_FD |        /* 10T full-duplex capable */
#endif  /* ETH_10BT */
#endif  /* ETH_FULL_DUPLEX */
                                MII_TECH_100BASE_TX;        /* 100TX-FX half-duplex capable */

    /* Initialize Auto Negotiation Advertisement Register. */
    at91EthMiiWrite(dev, phyAddr, MII_AN_ADS_REG, dev->PHYREGS.phyAds);

    /* Enable and Start Auto Negotiation. */
    dev->PHYREGS.phyCtrl |= MII_CR_AUTO_EN |           /* Auto-Negotiation Enable */
                                 MII_CR_RESTART;            /* Restart Auto Negotiation */

    /* Start auto negotiation. */
    at91EthMiiWrite(dev, phyAddr, MII_CTRL_REG, dev->PHYREGS.phyCtrl);

    /* Wait until start auto negotiation. */
    while (1)
    {
        at91EthMiiRead(dev, phyAddr, MII_CTRL_REG, &dev->PHYREGS.phyCtrl);
        if (!(dev->PHYREGS.phyCtrl & MII_CR_RESTART))
        {
            break;
        }
    }

    /* Wait until complete auto negotiation. */
    while (1)
    {
        at91EthMiiRead(dev, phyAddr, MII_STAT_REG, &dev->PHYREGS.phyStatus);
        if (dev->PHYREGS.phyStatus & MII_SR_AUTO_NEG)
        {
            break;
        }

        if (--timeout == 0)
        {
            printf("eth%d Error: MII auto negotiation timeout\n", dev->unit);

            return ERROR;
        }
    }

    return OK;
}


#endif


/*******************************************************************************
*
* at91EthFlagsSet - set device flags
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthFlagsSet(
    ETH_DRV_CTRL *dev  
    )
{

    long flags;

#ifdef  DEBUG_TRACE

    printf("eth%d FlagsSet, %08X\n", 0, (UINT32)dev->endObj.flags);
#endif  /* DEBUG_TRACE */

    flags = END_FLAGS_GET(&dev->endObj);

    if (flags & IFF_UP)
    {
        /* Config down. */
        END_FLAGS_CLR(&dev->endObj, IFF_UP | IFF_RUNNING);
    }
    dev->flags = flags;
    at91ether_set_rx_mode(dev);
  

    if (flags & IFF_UP)
    {
        /* Config up. */
        END_FLAGS_SET(&dev->endObj, IFF_UP | IFF_RUNNING);
    }

    return OK;
}

/*******************************************************************************
*
* at91EthLoopSet - set loop mode
*
* RETURNS: OK, or ERROR.
*/

void at91EthLoopSet(
    ETH_DRV_CTRL *dev,       
    int mode                      
    )
{

}

/*******************************************************************************
*
* at91EthMCastAdd - add multicast address
*
* RETURNS: OK, or ERROR.
*/
  
STATUS at91EthMCastAdd(
    ETH_DRV_CTRL *dev,     
    UCHAR *pAddr                
    )
{
	unsigned char mc_filter[2];
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	unsigned int bitnr;

	mc_filter[0] = mc_filter[1] = 0;

	bitnr = ether_crc(ETH_ALEN, pAddr) >> 26;
	mc_filter[bitnr >> 5] |= 1 << (bitnr & 31);

	regs->EMAC_HSH |= mc_filter[1];
	regs->EMAC_HSL |= mc_filter[0];



    return ERROR;
}

/*******************************************************************************
*
* at91EthMCastDel - remove multicast address
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthMCastDel(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    UCHAR *pAddr                                            /* pointer to the multicast address */
    )
{
	unsigned char mc_filter[2];
	unsigned int bitnr;
AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	mc_filter[0] = mc_filter[1] = 0;

	bitnr = ether_crc(ETH_ALEN, pAddr) >> 26;
	mc_filter[bitnr >> 5] |= 1 << (bitnr & 31);

	regs->EMAC_HSH &= ~mc_filter[1];
	regs->EMAC_HSL &= ~mc_filter[0];



    return ERROR;
}

/*******************************************************************************
*
* at91EthStart - start S3C2510 Ethernet controller
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthStart(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	lp->skb=NULL;
    lp->skb_physaddr=NULL;
	return at91ether_open(dev);
    return OK;
}

/*******************************************************************************
*
* at91EthStop - stop S3C2510 Ethernet controller
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthStop(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{
	return at91ether_close(dev);

    return OK;
}

/*******************************************************************************
*
* at91EthPlllStart - start polling mode
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthPollStart(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{

	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
#ifdef  DEBUG_TRACE
    
    printf("eth%d PollStart\n", 0);
#endif  /* DEBUG_TRACE */

    /* Disable interrupt. */
    intDisable(dev->irq);


    regs->EMAC_IDR = AT91C_EMAC_RCOM | AT91C_EMAC_TCOM ;
			
			
    dev->bPolling = TRUE;

    return OK;
}

/*******************************************************************************
*
* at91EthPollStop - stop polling mode
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthPollStop(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{
 /*   int unit = dev->unit;*/
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
#ifdef  DEBUG_TRACE
    
    printf("eth%d PollStop\n", 0);
#endif  /* DEBUG_TRACE */


    regs->EMAC_IER = AT91C_EMAC_RCOM | AT91C_EMAC_TCOM ;
    dev->bPolling = FALSE;

    /* Enable interrupt. */
    intEnable(dev->irq);

    return OK;
}



/*******************************************************************************
*
* at91EthRbdFree - free RBD
*
* RETURNS: N/A.
*/

void at91EthRbdFree(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    PETHRBD pRbd                                            /* pointer to the RBD to be freed */
    )
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
#ifdef  DEBUG_TRACE
    printf("eth%d RbdFree\n", dev->unit);
#endif  /* DEBUG_TRACE */
   
	pRbd->descriptors[lp->rxBuffIndex].addr &= ~EMAC_DESC_DONE;	/* reset ownership bit */

	if (lp->rxBuffIndex == MAX_RX_DESCR-1)				/* wrap after last buffer */
		lp->rxBuffIndex = 0;
	else
		lp->rxBuffIndex++;    
    

}
/*    *
* at91EthRbdCheck - check RBD
*
* RETURNS: length of frame received.
*/

ULONG at91EthRbdCheck(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    PETHRBD pRbd                                            /* pointer to the RBD to be checked */
    )
{
    int length = pRbd->descriptors[dev->priv->rxBuffIndex].size & 0x7ff;

    return (length);

}

/*******************************************************************************
*
* at91EthTbdGet - allocate TBD
*
* RETURNS: pointer to the TBD.
*/

unsigned char* at91EthTbdGet(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
        char *pBuf=0;
#ifdef  DEBUG_TRACE
    printf("eth%d TbdGet\n", dev->unit);
#endif  /* DEBUG_TRACE */

    /* Get the first available TBD. */
/*    pTbd = (PETHTBD)(dev->tbdBase + dev->tbdFree * SIZE_BD);*/

/*  if (dev->pClPool) */
    {
  
        if (!(regs->EMAC_TSR & AT91C_EMAC_BNQ))
        {
            return NULL;
        }

        /* Allocate cluster buffer. */
        pBuf = netClusterGet(dev->endObj.pNetPool, dev->endObj.pNetPool->clTbl[0]);

        if (!pBuf)
        {
#ifdef  DEBUG_TRACE
            printf("eth%d Error: Failed to allocate cluster buffer\n", dev->unit);
#endif  /* DEBUG_TRACE */

            return NULL;
        }

       /* pBuf =(pBuf + (SIZE_ETH_FB_HDR - 4));*/
    }
 

 

    return (pBuf);
}

/*******************************************************************************
*
* at91EthTbdFree - free TBD
*
* RETURNS: N/A.
*/

void at91EthTbdFree(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    unsigned char* pBuf                                             /* pointer to the TBD to be freed */
    )
{
		if( pBuf != NULL )
			{
		        netClFree(dev->endObj.pNetPool, (UCHAR *)(pBuf));
			}
}

/*******************************************************************************
*
* at91EthTbdStart - start transmit
*
* RETURNS: N/A.
*/

STATUS at91EthTbdStart(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    unsigned char* data ,                                   /* pointer to the TBD to be freed */
    ULONG length                                            /* length of data */
    )
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	struct at91_private *lp = (struct at91_private *) dev->priv;
	if ((regs->EMAC_TSR & AT91C_EMAC_BNQ)&&(lp->skb==NULL))
		{
    	/* Store packet information (to free when Tx completed) */
    	lp->skb = data;
    	lp->skb_length = length;
    	cacheFlush(DATA_CACHE,data, length); /* clean_dcache_range(data, length);*/
    	lp->stats.tx_bytes += length;

    	/* Set address of the data in the Transmit Address register */
    	regs->EMAC_TSR |= AT91C_EMAC_COMP;
    	regs->EMAC_TAR = (UINT32)data;
    	/* Set length of the packet in the Transmit Control register */
    	regs->EMAC_TCR = length;
        
        at91EthTbdFree(dev,lp->skb_physaddr);
        lp->skb_physaddr=NULL;
        return OK;
		}
	else if((regs->EMAC_TSR & AT91C_EMAC_BNQ)&&(lp->skb_physaddr==NULL))
		{
            
            /* Store packet information (to free when Tx completed) */
            lp->skb_physaddr = data;
            lp->skb_length = length;
            cacheFlush(DATA_CACHE,data, length); /* clean_dcache_range(data, length);*/
            lp->stats.tx_bytes += length;
            
            /* Set address of the data in the Transmit Address register */
            regs->EMAC_TSR |= AT91C_EMAC_COMP;
            regs->EMAC_TAR = (UINT32)data ;
            /* Set length of the packet in the Transmit Control register */
            regs->EMAC_TCR = length;
            
            at91EthTbdFree(dev,lp->skb);
            lp->skb=NULL;
            return OK; 
		}
    else
        {
        at91EthTbdFree(dev,data);
        }
	
    return ERROR;

}

/*******************************************************************************
*
* at91EthTbdCheck - check TBD
*
* RETURNS: OK, or ERROR.
*/

STATUS at91EthTbdCheck(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    unsigned char* pTbd                                            /* pointer to the TBD to be checked */
    )
{
 	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

    int timeout = TX_WAIT_MAX;
    int retry = 3;

#ifdef  DEBUG_TRACE
    printf("eth%d TbdCheck\n", dev->unit);
#endif  /* DEBUG_TRACE */

    /* Check if completed. */
    while ( !(regs->EMAC_TSR & AT91C_EMAC_BNQ))
    {
        if (--timeout == 0)
        {
            if (--retry == 0)
            {
                printf("eth%d Error: Tx timeout\n", dev->unit);

                return ERROR;
            }

            timeout = TX_WAIT_MAX;

         }
    }

    return ERROR;
}

/*******************************************************************************
*
* at91EthSend - send packet in interrupt mode
*
* RETURNS: OK, or END_ERR_BLOCK.
*/

STATUS at91EthSend(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{

    ULONG length;
	int oldLevel;
    unsigned char* pBuf=0;

	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
    if (!(regs->EMAC_TSR & AT91C_EMAC_BNQ)) return ERROR;
#ifdef  DEBUG_TRACE
    printf("eth%d Send, 0x%08X\n", 0, (UINT32)pMblk->mBlkHdr.mData);
#endif  /* DEBUG_TRACE */

    if (dev->bTxBlocked)
    {
        /* Retry later. */
        return END_ERR_BLOCK;
    }

    if (dev->bPolling)
    {
        return ERROR;
    }

    	
    length = pMblk->mBlkPktHdr.len;

    /* Check frame length. */
    if ((length <= SIZE_ETH_HDR) || (length > SIZE_ETH_MFLR))
    {
        /* Up-date statistics. */
        dev->MIB2TBL.ifOutErrors++;

        return ERROR;
    }
  
#if 1
pBuf = at91EthTbdGet(dev);
if (pBuf==NULL) return ERROR;
length = netMblkToBufCopy(pMblk, (char *)(pBuf + SIZE_ETH_WA), NULL);

#endif

    /* Bump the statistic counter. */

    END_ERR_ADD (&dev->endObj, MIB2_OUT_UCAST, +1);

    /* Free the Mblk. */
    netMblkClChainFree(pMblk);

#ifdef  DEBUG_TRACE
    at91EthHexDump((UCHAR *)(pBuf + SIZE_ETH_WA), length);
#endif  /* DEBUG_TRACE */

    /* Start transmit. */

   return at91EthTbdStart(dev, pBuf, length);
}

/*******************************************************************************
*
* at91EthPollReceive - receive packet in polled mode
*
* RETURNS: OK, or EAGAIN.
*/

STATUS at91EthPollReceive(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{
    	
	struct at91_private *lp = (struct at91_private *) dev->priv;
	PETHRBD pRbd = lp->dlist;
	int index = lp->rxBuffIndex;
	char* pBuf =(char*)( pRbd->descriptors[index].addr&0xfffffffc);


    /* Get the first available RBD. */
    /*pRbd = at91EthRbdGet(dev);*/
    
	
		
    /* If no RBD is available, retry it later. */
    if (pRbd == NULL)
    {
        return EAGAIN;
    }

    do
    {
        ULONG length =  pRbd->descriptors[index].size & 0x7ff; 

        if (length == 0)
        {
            break;
        }

        /* If buffer is not large enough, we do not copy the received buffer. */
        if ((ULONG)pMblk->mBlkHdr.mLen < length)
        {
            printf("eth%d Error: Too small Rx mBlk, %d\n", dev->unit, pMblk->mBlkHdr.mLen);

            break;
        }

#ifdef  DEBUG_TRACE
        at91EthHexDump((UCHAR *)(pBuf + SIZE_ETH_WA), length);
#endif  /* DEBUG_TRACE */

        /* Up-date statistics. */
        dev->MIB2TBL.ifInOctets += length;
        if (((UINT8 *)(pBuf + SIZE_ETH_WA))[0] & 0x01)
        {
            dev->MIB2TBL.ifInNUcastPkts += 1;
        }
        else
        {
            dev->MIB2TBL.ifInUcastPkts += 1;
        }

        /* Set up the mBlk properly. */
        pMblk->mBlkHdr.mFlags  |= M_PKTHDR;
        pMblk->mBlkHdr.mLen     = length;
        pMblk->mBlkPktHdr.len   = length;

        /* Copy data. */
        bcopy((char *)(pBuf + SIZE_ETH_WA), (char *)pMblk->mBlkHdr.mData, length);

        /* Free the used RBD. */
        at91EthRbdFree(dev, pRbd);

        return OK;

    } while (FALSE);

    /* Up-date statistics. */
    dev->MIB2TBL.ifInErrors++;

    /* Free the used RBD. */
    at91EthRbdFree(dev, pRbd);

    return EAGAIN;
}

/*******************************************************************************
*
* at91EthPollSend - send packet in polled mode
*
* RETURNS: OK, or EAGAIN.
*/

STATUS at91EthPollSend(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{

    ULONG length;
    unsigned char* pBuf = 0;
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	
    if (!(regs->EMAC_TSR & AT91C_EMAC_BNQ)) return ERROR;
    
#ifdef  DEBUG_TRACE
    
    printf("eth%d PollSend, 0x%08X\n", 0, (UINT32)pMblk->mBlkHdr.mData);
#endif  /* DEBUG_TRACE */

    length = pMblk->mBlkPktHdr.len;

    /* Check frame length. */
    if ((length <= SIZE_ETH_HDR) || (length > SIZE_ETH_MFLR))
    {

        /* Up-date statistics. */
        dev->MIB2TBL.ifOutErrors++;

        return ERROR;
    }
    pBuf = at91EthTbdGet(dev);
    do
    {
        /* Copy data but do not free the Mblk. */
        length = (ULONG)netMblkToBufCopy(pMblk, (char *)(pBuf + SIZE_ETH_WA), NULL);

#ifdef  DEBUG_TRACE
        at91EthHexDump((UCHAR *)(pBuf + SIZE_ETH_WA), length);
#endif  /* DEBUG_TRACE */

        /* Start transmit. */
        at91EthTbdStart(dev, pBuf, length);

        /* Check if completed. */
        if (at91EthTbdCheck(dev, pBuf) == OK)
        {
            /* Up-date statistics. */
            dev->MIB2TBL.ifOutOctets += (ULONG)length;
            if (((UINT8 *)(pBuf + SIZE_ETH_WA))[0] & 0x01)
            {
                dev->MIB2TBL.ifOutNUcastPkts += 1;
            }
            else
            {
                dev->MIB2TBL.ifOutUcastPkts += 1;
            }

            /* Free the used TBD. */
            at91EthTbdFree(dev, pBuf);

            return OK;
        }

    } while (FALSE);

    /* Up-date statistics. */
    dev->MIB2TBL.ifOutErrors++;

    /* Free the used TBD. */
    at91EthTbdFree(dev, pBuf);

    return EAGAIN;
}


/*******************************************************************************
*
* at91EthRbdProcess - porcess a RBD
*
* RETURNS : N/A
*/

void at91EthRbdProcess(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    PETHRBD pRbd                                            /* pointer to the RBD */
    )
{
    M_BLK_ID     pMblk = NULL;
    char        *pNewCluster = NULL; 
    int index = dev->priv->rxBuffIndex;
    CL_BLK_ID    pClBlk = NULL;
    char        *pData ;
    UINT32       len   ;

    while ( (pRbd->descriptors[index].addr & EMAC_DESC_DONE))
    {
#ifdef  DEBUG_TRACE
    printf(" RxHandler, index = %d, addr=%x \n", index,pRbd->descriptors[index].addr);
#endif  /* DEBUG_TRACE */
	pData  = (char*)(pRbd->descriptors[index].addr&0xfffffffc);
   	len  =  (pRbd->descriptors[index].size & 0x7ff);
#ifdef  DEBUG_TRACE
       /* at91EthHexDump((UCHAR *)(pData + SIZE_ETH_WA), len);*/
#endif  	
   	if (dev->endObj.pNetPool == NULL)
   	 {
  	  DEBUG_LOG (DRV_DEBUG_RX, "at91EndRecv: Illegal pNetPool on entry!\n",
             0,0,0,0,0,0);
  	 END_ERR_ADD (&dev->endObj, MIB2_IN_ERRS, +1);
  	  goto cleanRXD;
 	   }

    /* Add one to our unicast data. */
    END_ERR_ADD (&dev->endObj, MIB2_IN_UCAST, +1);

    if ((pMblk = mBlkGet (dev->endObj.pNetPool, M_DONTWAIT, MT_DATA))
        == NULL)
        {
        DEBUG_LOG (DRV_DEBUG_RX, "at91EndRecv: Out of M Blocks!\n",
                 0,0,0,0,0,0);
        END_ERR_ADD (&dev->endObj, MIB2_IN_ERRS, +1);
        goto cleanRXD;
        }

    pNewCluster = netClusterGet (dev->endObj.pNetPool,
                                 dev->endObj.pNetPool->clTbl[0]);

    if (pNewCluster == NULL)
        {
        DEBUG_LOG (DRV_DEBUG_RX, "sngks32cEndRecv: Cannot loan!\n",
                 0,0,0,0,0,0);

        dev->lastError.errCode = END_ERR_NO_BUF;
        muxError(&dev->endObj, &dev->lastError);

        goto cleanRXD;
        }
        
	memcpy(pNewCluster+2,pData,len);

    /* Grab a cluster block to marry to the cluster we received. */

    if ((pClBlk = netClBlkGet (dev->endObj.pNetPool, M_DONTWAIT)) == NULL)
        {
        DEBUG_LOG (DRV_DEBUG_RX, "at91EndRecv: Out of Cluster Blocks!\n",
                 0,0,0,0,0,0);

        dev->lastError.errCode = END_ERR_NO_BUF;
        muxError(&dev->endObj, &dev->lastError);

        goto cleanRXD;
        }

    
    END_ERR_ADD (&dev->endObj, MIB2_IN_UCAST, +1);

   

    /* Note: we rely on the hardware to pad 2 bytes so we don't need to copy to
     * a new buffer to solve alignment problems
     */

    /* Join the cluster to the MBlock */
    if (netClBlkJoin (pClBlk, pNewCluster, SIZE_ETH_MDMA, NULL, 0, 0, 0) == NULL)
        {
        DEBUG_LOG (DRV_DEBUG_RX, "at91EndRecv: netClBlkJoin failed\n",
                 0,0,0,0,0,0);

        dev->lastError.errCode = END_ERR_NO_BUF;
        muxError(&dev->endObj,&dev->lastError);

        goto cleanRXD;
        }                     
    
    if (netMblkClJoin (pMblk, pClBlk) == NULL)
        {
        DEBUG_LOG (DRV_DEBUG_RX, "at91EndRecv: netMblkClJoin failed\n",
                 0,0,0,0,0,0);

        dev->lastError.errCode = END_ERR_NO_BUF;
        muxError(&dev->endObj, &dev->lastError);

        goto cleanRXD;
        }

    
    /* The ip structure is 14 bytes from the beginning of the valid frame data
     * yet it must be aligned on a word boundary.  We have told the ethernet
     * controller to insert 2 bytes of garbage at the beginning of each frame
     * so now all we need to do is move our pointer to the frame data to the
     * real start of the frame causing the frame to be half-word aligned but
     * not word aligned.  By counting 14 bytes from the beginning of the frame
     * to the ip, we arrive on a word boundary.
     */
    pMblk->mBlkHdr.mData += SIZE_ETH_WA;


    pMblk->mBlkHdr.mData+=2;	
    pMblk->mBlkHdr.mFlags |= M_PKTHDR;
    pMblk->mBlkHdr.mLen   = len;
    pMblk->mBlkPktHdr.len = len;

    /* Call the upper layer's receive routine. */
    END_RCV_RTN_CALL(&dev->endObj, pMblk);

    /*   pRxD->rxFrameData.frameDataPtr = (UINT32)pNewCluster;*/

    /* Free the used RBD. */

    at91EthRbdFree(dev, pRbd);
    index = dev->priv->rxBuffIndex;

 }
	return;
cleanRXD:
    /* Free the used RBD. */
    at91EthRbdFree(dev, pRbd);

    if (pClBlk != NULL)
        {
        netClBlkFree (dev->endObj.pNetPool, pClBlk); 
        }

    if (pNewCluster != NULL)
        {
        netClFree (dev->endObj.pNetPool, pNewCluster);
        pNewCluster = NULL;
        }

    if (pMblk != NULL)
        {
        netMblkFree (dev->endObj.pNetPool, pMblk);
        }

    END_ERR_ADD (&dev->endObj, MIB2_IN_ERRS, +1);

}

/*******************************************************************************
*
* at91EthTbdProcess - porcess a TBD
*
* RETURNS : N/A
*/

void at91EthTbdProcess(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    unsigned char* pBuf                                            /* pointer to the TBD */
    )
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
    at91EthTbdFree(dev, lp->skb);
	lp->skb=NULL;

}

/*******************************************************************************
*
* at91EthRxHandler - Rx interrupt handler
*
* RETURNS : N/A
*/

void at91EthRxHandler(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{
    struct at91_private *lp = (struct at91_private *) dev->priv;

    PETHRBD pRbd;



    dev->bRxHandler = FALSE;

    pRbd = lp->dlist;	

/*    while (pRbd->descriptors[lp->rxBuffIndex].addr & EMAC_DESC_DONE)*/
    {
        /* Get the first available RBD. */
        /*pRbd = at91EthRbdGet(dev);*/
	
/*        if (pRbd == NULL)
        {
            break;
        }
*/
        at91EthRbdProcess(dev, pRbd);

    } 

 
}

/*******************************************************************************
*
* at91EthTxHandler - Tx interrupt handler
*
* RETURNS : N/A
*/

void at91EthTxHandler(
    ETH_DRV_CTRL *dev                                  /* pointer to driver structure */
    )
{

    dev->bTxHandler = FALSE;
	
    /*at91EthTbdProcess(dev, 0);*/

    /* Restart Tx if it was blocked. */
    if (dev->bTxBlocked)
    {
#ifdef  DEBUG_TRACE
        printf("eth%d Restart Tx\n", dev->unit);
#endif  /* DEBUG_TRACE */

        muxTxRestart(&dev->endObj);

        dev->bTxBlocked = FALSE;
    }
}

/*******************************************************************************
*
* at91EthShow - display driver statstics.
*
* RETURNS : N/A
*/

STATUS at91EthShow(int unit)
{


    return OK;
}

/*******************************************************************************
*
* at91EthMiiShow - display MII registers.
*
* RETURNS : N/A
*/

STATUS at91EthMiiShow(int unit)
{
#if 0
    ETH_DRV_CTRL *dev = (ETH_DRV_CTRL *)endFindByName(ETH_DEV_NAME, unit);
    UINT8 phyAddr;

    if (!dev)
    {
        return -1;
    }

    phyAddr = dev->phyInfo.phyAddr;

    at91EthMiiRead(dev, phyAddr, MII_CTRL_REG,      &dev->PHYREGS.phyCtrl);
    at91EthMiiRead(dev, phyAddr, MII_STAT_REG,      &dev->PHYREGS.phyStatus);
    at91EthMiiRead(dev, phyAddr, MII_PHY_ID1_REG,   &dev->PHYREGS.phyId1);
    at91EthMiiRead(dev, phyAddr, MII_PHY_ID2_REG,   &dev->PHYREGS.phyId2);
    at91EthMiiRead(dev, phyAddr, MII_AN_ADS_REG,    &dev->PHYREGS.phyAds);
    at91EthMiiRead(dev, phyAddr, MII_AN_PRTN_REG,   &dev->PHYREGS.phyPrtn);
    at91EthMiiRead(dev, phyAddr, MII_AN_EXP_REG,    &dev->PHYREGS.phyExp);
    at91EthMiiRead(dev, phyAddr, MII_AN_NEXT_REG,   &dev->PHYREGS.phyNext);
    at91EthMiiRead(dev, phyAddr, MII_LPA,   &dev->l80225Status);

    printf("Standard MII register\n");
    printf("    MII_CTRL_REG:       0x%04X\n", dev->PHYREGS.phyCtrl);
    printf("    MII_STAT_REG:       0x%04X\n", dev->PHYREGS.phyStatus);
    printf("    MII_PHY_ID1_REG:    0x%04X\n", dev->PHYREGS.phyId1);
    printf("    MII_PHY_ID2_REG:    0x%04X\n", dev->PHYREGS.phyId2);
    printf("    MII_AN_ADS_REG:     0x%04X\n", dev->PHYREGS.phyAds);
    printf("    MII_AN_PRTN_REG:    0x%04X\n", dev->PHYREGS.phyPrtn);
    printf("    MII_AN_EXP_REG:     0x%04X\n", dev->PHYREGS.phyExp);
    printf("    MII_AN_NEXT_REG:    0x%04X\n", dev->PHYREGS.phyNext);
    printf("PHY specific register\n");
    printf("    L80225_STAT_REG:    0x%04X\n", dev->l80225Status);
#endif
    return OK;
}

#ifdef  DEBUG_TRACE
/*******************************************************************************
*
* at91EthHexDump - dump buffer.
*
* RETURNS : N/A
*/

void at91EthHexDump(UCHAR *p, ULONG l)
{
    ULONG i;

    while (l)
    {
        printf("%08X:  ", (UINT32)p);
        for (i=0; i<16; i++)
        {
            printf("%02X ", *p++);

            if (--l == 0)
            {
                break;
            }
        }
        printf("\n");
    }
}
#endif  /* DEBUG_TRACE */






/*******************************************************************************
*
* at91EthSend - send packet in interrupt mode
*
* RETURNS: OK, or END_ERR_BLOCK.
*/

STATUS at91EthSend2(
    ETH_DRV_CTRL *dev,                                 /* pointer to driver structure */
    M_BLK_ID pMblk                                          /* pointer to the mBlk/cluster pair */
    )
{

    ULONG length;
    unsigned char* pBuf=0;

	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
    if (!(regs->EMAC_TSR & AT91C_EMAC_BNQ)) return ERROR;

    if (dev->bTxBlocked)
    {
        /* Retry later. */
        return END_ERR_BLOCK;
    }

    if (dev->bPolling)
    {
        return ERROR;
    }

    	
    length = pMblk->mBlkPktHdr.len;

    /* Check frame length. */
    if ((length <= SIZE_ETH_HDR) || (length > SIZE_ETH_MFLR))
    {
        /* Up-date statistics. */
        dev->MIB2TBL.ifOutErrors++;

        return ERROR;
    }
 


    /* Bump the statistic counter. */

    END_ERR_ADD (&dev->endObj, MIB2_OUT_UCAST, +1);

    /* Free the Mblk. */
    netMblkClChainFree(pMblk);

    return OK;
}



#ifdef  INCLUDE_SEC_END
#include "end/secEnd.c"
#endif  /* INCLUDE_SEC_END */



















